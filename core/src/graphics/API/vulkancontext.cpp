#include "vulkancontext.hpp"
#include <algorithm>

namespace heartCore { namespace graphics {
namespace API {

	bool VulkanContext::createVkInstance() {
		vk::ApplicationInfo appInfo{};
		appInfo.pApplicationName = "Vulkan API";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Heart";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_1;

		uint32_t glfwExtCount = 0;
		const char** glfwExts = glfwGetRequiredInstanceExtensions(&glfwExtCount);
		if (!glfwExts) {
			LOG_FATAL("GLFW: Vulkan is not supported");
			return false;
		}
		std::vector<const char*> extensions(glfwExts, glfwExts + glfwExtCount);

		std::vector<const char*> layers;

		const char* validation = "VK_LAYER_KHRONOS_validation";
		for (auto& l : m_vkContext.enumerateInstanceLayerProperties()) {
			if (std::strcmp(l.layerName, validation) == 0) {
				layers.push_back(validation);
				break;
			}
		}

		vk::InstanceCreateInfo info{};
		info.pApplicationInfo = &appInfo;
		info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		info.ppEnabledExtensionNames = extensions.data();
		info.enabledLayerCount = static_cast<uint32_t>(layers.size());
		info.ppEnabledLayerNames = layers.data();

		m_vkInstance = std::make_unique<vk::raii::Instance>(m_vkContext, info);
		return true;
	}

	bool VulkanContext::createVkSurface(GLFWwindow* window) {
		m_window = window;
		VkSurfaceKHR rawSurface = VK_NULL_HANDLE;
		if (glfwCreateWindowSurface(static_cast<VkInstance>(**m_vkInstance),
			window, nullptr, &rawSurface) != VK_SUCCESS) {
			LOG_FATAL("Failed to create window surface");
			return false;
		}
		m_vkSurface = std::make_unique<vk::raii::SurfaceKHR>(*m_vkInstance, rawSurface);
		return true;
	}

	bool VulkanContext::pickVkPhysicalDevice() {
		vk::raii::PhysicalDevices devices(*m_vkInstance);
		if (devices.empty()) {
			LOG_FATAL("No Vulkan-capable GPU found");
			return false;
		}

		for (auto& dev : devices) {
			// нужна поддержка swapchain
			bool hasSwapchain = false;
			for (auto& ext : dev.enumerateDeviceExtensionProperties()) {
				if (std::strcmp(ext.extensionName, VK_KHR_SWAPCHAIN_EXTENSION_NAME) == 0) {
					hasSwapchain = true;
					break;
				}
			}
			if (!hasSwapchain) continue;

			auto families = dev.getQueueFamilyProperties();
			bool foundGraphics = false, foundPresent = false;
			for (uint32_t i = 0; i < families.size(); i++) {
				if (!foundGraphics && (families[i].queueFlags & vk::QueueFlagBits::eGraphics)) {
					m_graphicsFamily = i;
					foundGraphics = true;
				}
				if (!foundPresent && dev.getSurfaceSupportKHR(i, **m_vkSurface)) {
					m_presentFamily = i;
					foundPresent = true;
				}
			}

			if (foundGraphics && foundPresent) {
				m_vkPhysicalDevice = std::make_unique<vk::raii::PhysicalDevice>(std::move(dev));
				return true;
			}
		}

		LOG_FATAL("No suitable GPU found");
		return false;
	}

	bool VulkanContext::createVkDevice() {
		std::set<uint32_t> uniqueFamilies = { m_graphicsFamily, m_presentFamily };
		float priority = 1.0f;

		std::vector<vk::DeviceQueueCreateInfo> queueInfos;
		for (uint32_t family : uniqueFamilies) {
			vk::DeviceQueueCreateInfo q{};
			q.queueFamilyIndex = family;
			q.queueCount = 1;
			q.pQueuePriorities = &priority;
			queueInfos.push_back(q);
		}

		const char* deviceExts[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
		vk::PhysicalDeviceFeatures features{};

		vk::DeviceCreateInfo info{};
		info.queueCreateInfoCount = static_cast<uint32_t>(queueInfos.size());
		info.pQueueCreateInfos = queueInfos.data();
		info.enabledExtensionCount = 1;
		info.ppEnabledExtensionNames = deviceExts;
		info.pEnabledFeatures = &features;

		m_vkDevice = std::make_unique<vk::raii::Device>(*m_vkPhysicalDevice, info);
		return true;
	}

	bool VulkanContext::createVkSwapchain() {
		if (!m_vkPhysicalDevice || !m_vkDevice || !m_vkSurface) {
			LOG_FATAL("Cannot create swapchain before Vulkan device and surface");
			return false;
		}

		const vk::SurfaceCapabilitiesKHR capabilities =
			m_vkPhysicalDevice->getSurfaceCapabilitiesKHR(**m_vkSurface);
		const std::vector<vk::SurfaceFormatKHR> formats =
			m_vkPhysicalDevice->getSurfaceFormatsKHR(**m_vkSurface);
		const std::vector<vk::PresentModeKHR> presentModes =
			m_vkPhysicalDevice->getSurfacePresentModesKHR(**m_vkSurface);

		if (formats.empty() || presentModes.empty()) {
			LOG_FATAL("Surface does not provide swapchain formats or present modes");
			return false;
		}

		vk::SurfaceFormatKHR surfaceFormat = formats.front();
		for (const auto& format : formats) {
			if (format.format == vk::Format::eB8G8R8A8Srgb &&
				format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
				surfaceFormat = format;
				break;
			}
		}

		vk::PresentModeKHR presentMode = vk::PresentModeKHR::eFifo;
		for (const auto mode : presentModes) {
			if (mode == vk::PresentModeKHR::eMailbox) {
				presentMode = mode;
				break;
			}
		}

		vk::Extent2D extent = capabilities.currentExtent;
		if (extent.width == std::numeric_limits<std::uint32_t>::max()) {
			int width = 0;
			int height = 0;
			glfwGetFramebufferSize(m_window, &width, &height);
			extent.width = std::clamp(static_cast<std::uint32_t>(width),
				capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
			extent.height = std::clamp(static_cast<std::uint32_t>(height),
				capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
		}

		std::uint32_t imageCount = capabilities.minImageCount + 1;
		if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount)
			imageCount = capabilities.maxImageCount;

		vk::SwapchainCreateInfoKHR info{};
		info.surface = **m_vkSurface;
		info.minImageCount = imageCount;
		info.imageFormat = surfaceFormat.format;
		info.imageColorSpace = surfaceFormat.colorSpace;
		info.imageExtent = extent;
		info.imageArrayLayers = 1;
		info.imageUsage = vk::ImageUsageFlagBits::eColorAttachment;

		const std::uint32_t queueFamilies[] = { m_graphicsFamily, m_presentFamily };
		if (m_graphicsFamily != m_presentFamily) {
			info.imageSharingMode = vk::SharingMode::eConcurrent;
			info.queueFamilyIndexCount = 2;
			info.pQueueFamilyIndices = queueFamilies;
		} else {
			info.imageSharingMode = vk::SharingMode::eExclusive;
		}
		info.preTransform = capabilities.currentTransform;
		info.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
		info.presentMode = presentMode;
		info.clipped = VK_TRUE;
		if (m_vkSwapchain)
			info.oldSwapchain = **m_vkSwapchain;

		vk::raii::SwapchainKHR newSwapchain(*m_vkDevice, info);
		std::vector<vk::Image> newImages = newSwapchain.getImages();
		std::vector<vk::raii::ImageView> newImageViews;
		newImageViews.reserve(newImages.size());

		for (const vk::Image image : newImages) {
			vk::ImageViewCreateInfo viewInfo{};
			viewInfo.image = image;
			viewInfo.viewType = vk::ImageViewType::e2D;
			viewInfo.format = surfaceFormat.format;
			viewInfo.components = vk::ComponentMapping{};
			viewInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
			viewInfo.subresourceRange.baseMipLevel = 0;
			viewInfo.subresourceRange.levelCount = 1;
			viewInfo.subresourceRange.baseArrayLayer = 0;
			viewInfo.subresourceRange.layerCount = 1;
			newImageViews.emplace_back(*m_vkDevice, viewInfo);
		}

		m_vkSwapchain = std::make_unique<vk::raii::SwapchainKHR>(std::move(newSwapchain));
		m_swapchainImages = std::move(newImages);
		m_swapchainImageViews = std::move(newImageViews);
		m_swapchainImageFormat = surfaceFormat.format;
		m_swapchainExtent = extent;
		return true;
	}

	bool VulkanContext::recreateVkSwapchain() {
		if (!m_vkDevice)
			return false;
		m_vkDevice->waitIdle();
		return createVkSwapchain();
	}

	bool VulkanContext::acquireNextImage(std::uint32_t& imageIndex) {
		if (!m_vkSwapchain)
			return false;

		try {
			auto result = m_vkSwapchain->acquireNextImage(
				std::numeric_limits<std::uint64_t>::max(), {}, {});
			if (result.result == vk::Result::eErrorOutOfDateKHR)
				return recreateVkSwapchain() && acquireNextImage(imageIndex);
			if (result.result != vk::Result::eSuccess && result.result != vk::Result::eSuboptimalKHR)
				return false;
			imageIndex = result.value;
			return true;
		} catch (const vk::SystemError& error) {
			LOG_ERROR(error.what());
			return false;
		}
	}

} } }