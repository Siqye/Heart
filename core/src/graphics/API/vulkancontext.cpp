#include "vulkancontext.hpp"

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
		m_vkGraphicsQueue = std::make_unique<vk::raii::Queue>(*m_vkDevice, m_graphicsFamily, 0);
		m_vkPresentQueue = std::make_unique<vk::raii::Queue>(*m_vkDevice, m_presentFamily, 0);
		return true;
	}

} } }