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

	void VulkanContext::cleanup() {
		if (m_vkDevice) m_vkDevice->waitIdle();

		m_inFlight.clear();
		m_imageAvailable.clear();
		m_renderFinished.clear();
		m_vkCommandBuffers.clear();
		m_vkCommandPool.reset();
		m_swapImages.clear();
		m_vkSwapchain.reset();

		m_vkPresentQueue.reset();
		m_vkGraphicsQueue.reset();
		m_vkDevice.reset();
		m_vkPhysicalDevice.reset();
		m_vkSurface.reset();
		m_vkDebugMessenger.reset();
		m_vkInstance.reset();
	}

	bool VulkanContext::createSwapchain(GLFWwindow* window) {
		auto& pd = *m_vkPhysicalDevice;
		vk::SurfaceKHR surface = **m_vkSurface;

		auto caps = pd.getSurfaceCapabilitiesKHR(surface);
		auto formats = pd.getSurfaceFormatsKHR(surface);
		auto modes = pd.getSurfacePresentModesKHR(surface);
		if (formats.empty() || modes.empty()) {
			LOG_FATAL("Swapchain is not supported by the surface");
			return false;
		}

		// формат
		vk::SurfaceFormatKHR format = formats[0];
		for (auto& f : formats) {
			if (f.format == vk::Format::eB8G8R8A8Srgb &&
				f.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
				format = f;
				break;
			}
		}

		// present mode: mailbox, иначе FIFO (гарантирован)
		vk::PresentModeKHR mode = vk::PresentModeKHR::eFifo;
		for (auto m : modes) {
			if (m == vk::PresentModeKHR::eMailbox) { mode = m; break; }
		}

		// размер
		vk::Extent2D extent = caps.currentExtent;
		if (extent.width == std::numeric_limits<uint32_t>::max()) {
			int w = 0, h = 0;
			glfwGetFramebufferSize(window, &w, &h);
			extent.width = std::clamp<uint32_t>(w, caps.minImageExtent.width, caps.maxImageExtent.width);
			extent.height = std::clamp<uint32_t>(h, caps.minImageExtent.height, caps.maxImageExtent.height);
		}

		uint32_t imageCount = caps.minImageCount + 1;
		if (caps.maxImageCount > 0) imageCount = std::min(imageCount, caps.maxImageCount);

		if (!(caps.supportedUsageFlags & vk::ImageUsageFlagBits::eTransferDst)) {
			LOG_FATAL("Surface does not support TRANSFER_DST usage");
			return false;
		}

		uint32_t families[] = { m_graphicsFamily, m_presentFamily };

		vk::SwapchainCreateInfoKHR info{};
		info.surface = surface;
		info.minImageCount = imageCount;
		info.imageFormat = format.format;
		info.imageColorSpace = format.colorSpace;
		info.imageExtent = extent;
		info.imageArrayLayers = 1;
		info.imageUsage = vk::ImageUsageFlagBits::eColorAttachment | vk::ImageUsageFlagBits::eTransferDst;
		if (m_graphicsFamily != m_presentFamily) {
			info.imageSharingMode = vk::SharingMode::eConcurrent;
			info.queueFamilyIndexCount = 2;
			info.pQueueFamilyIndices = families;
		}
		else {
			info.imageSharingMode = vk::SharingMode::eExclusive;
		}
		info.preTransform = caps.currentTransform;
		info.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
		info.presentMode = mode;
		info.clipped = VK_TRUE;

		m_vkSwapchain = std::make_unique<vk::raii::SwapchainKHR>(*m_vkDevice, info);
		m_swapFormat = format.format;
		m_swapExtent = extent;

		m_swapImages.clear();
		for (VkImage img : m_vkSwapchain->getImages())
			m_swapImages.push_back(vk::Image(img));

		// renderFinished — по одному семафору на swapchain image
		m_renderFinished.clear();
		for (size_t i = 0; i < m_swapImages.size(); i++)
			m_renderFinished.emplace_back(*m_vkDevice, vk::SemaphoreCreateInfo{});

		return true;
	}

	bool VulkanContext::createSwapBuffer(GLFWwindow* window) {
		try {
			if (!createSwapchain(window)) return false;

			vk::CommandPoolCreateInfo poolInfo{};
			poolInfo.flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
			poolInfo.queueFamilyIndex = m_graphicsFamily;
			m_vkCommandPool = std::make_unique<vk::raii::CommandPool>(*m_vkDevice, poolInfo);

			vk::CommandBufferAllocateInfo allocInfo{};
			allocInfo.commandPool = **m_vkCommandPool;
			allocInfo.level = vk::CommandBufferLevel::ePrimary;
			allocInfo.commandBufferCount = MAX_FRAMES_IN_FLIGHT;
			vk::raii::CommandBuffers buffers(*m_vkDevice, allocInfo);
			for (auto& b : buffers) m_vkCommandBuffers.push_back(std::move(b));

			vk::FenceCreateInfo fenceInfo{};
			fenceInfo.flags = vk::FenceCreateFlagBits::eSignaled;
			for (uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
				m_imageAvailable.emplace_back(*m_vkDevice, vk::SemaphoreCreateInfo{});
				m_inFlight.emplace_back(*m_vkDevice, fenceInfo);
			}
			return true;
		}
		catch (const std::exception& e) {
			LOG_FATAL(e.what());
			return false;
		}
	}

	bool VulkanContext::recreateSwapchain(GLFWwindow* window) {
		int w = 0, h = 0;
		glfwGetFramebufferSize(window, &w, &h);
		if (w == 0 || h == 0) return true;   // окно свернуто — ждем

		m_vkDevice->waitIdle();
		m_renderFinished.clear();
		m_vkSwapchain.reset();
		return createSwapchain(window);
	}

	void VulkanContext::recordCommands(vk::raii::CommandBuffer& cmd, vk::Image image) {
		cmd.reset();

		vk::CommandBufferBeginInfo begin{};
		begin.flags = vk::CommandBufferUsageFlagBits::eOneTimeSubmit;
		cmd.begin(begin);

		vk::ImageSubresourceRange range{};
		range.aspectMask = vk::ImageAspectFlagBits::eColor;
		range.baseMipLevel = 0;
		range.levelCount = 1;
		range.baseArrayLayer = 0;
		range.layerCount = 1;

		// UNDEFINED -> TRANSFER_DST
		vk::ImageMemoryBarrier toTransfer{};
		toTransfer.srcAccessMask = {};
		toTransfer.dstAccessMask = vk::AccessFlagBits::eTransferWrite;
		toTransfer.oldLayout = vk::ImageLayout::eUndefined;
		toTransfer.newLayout = vk::ImageLayout::eTransferDstOptimal;
		toTransfer.srcQueueFamilyIndex = vk::QueueFamilyIgnored;
		toTransfer.dstQueueFamilyIndex = vk::QueueFamilyIgnored;
		toTransfer.image = image;
		toTransfer.subresourceRange = range;
		cmd.pipelineBarrier(vk::PipelineStageFlagBits::eTopOfPipe,
			vk::PipelineStageFlagBits::eTransfer, {}, {}, {}, toTransfer);

		// очистка цветом
		vk::ClearColorValue color(std::array<float, 4>{ 0.1f, 0.1f, 0.15f, 1.0f });
		cmd.clearColorImage(image, vk::ImageLayout::eTransferDstOptimal, color, range);

		// TRANSFER_DST -> PRESENT_SRC
		vk::ImageMemoryBarrier toPresent = toTransfer;
		toPresent.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
		toPresent.dstAccessMask = {};
		toPresent.oldLayout = vk::ImageLayout::eTransferDstOptimal;
		toPresent.newLayout = vk::ImageLayout::ePresentSrcKHR;
		cmd.pipelineBarrier(vk::PipelineStageFlagBits::eTransfer,
			vk::PipelineStageFlagBits::eBottomOfPipe, {}, {}, {}, toPresent);

		cmd.end();
	}

	bool VulkanContext::swapBuffer(GLFWwindow* window) {
		if (!m_vkSwapchain) return false;

		try {
			auto& device = *m_vkDevice;
			uint32_t frame = m_currentFrame;

			// ждем, пока кадр с этим индексом закончит выполняться на GPU
			(void)device.waitForFences({ *m_inFlight[frame] }, VK_TRUE, UINT64_MAX);

			// получаем следующий image
			uint32_t imageIndex = 0;
			try {
				auto [res, idx] = m_vkSwapchain->acquireNextImage(UINT64_MAX, *m_imageAvailable[frame], nullptr);
				imageIndex = idx;
			}
			catch (const vk::OutOfDateKHRError&) {
				return recreateSwapchain(window);
			}

			device.resetFences({ *m_inFlight[frame] });

			recordCommands(m_vkCommandBuffers[frame], m_swapImages[imageIndex]);

			vk::PipelineStageFlags waitStage = vk::PipelineStageFlagBits::eTransfer;
			vk::Semaphore waitSem = *m_imageAvailable[frame];
			vk::Semaphore signalSem = *m_renderFinished[imageIndex];
			vk::CommandBuffer cmd = *m_vkCommandBuffers[frame];

			vk::SubmitInfo submit{};
			submit.waitSemaphoreCount = 1;
			submit.pWaitSemaphores = &waitSem;
			submit.pWaitDstStageMask = &waitStage;
			submit.commandBufferCount = 1;
			submit.pCommandBuffers = &cmd;
			submit.signalSemaphoreCount = 1;
			submit.pSignalSemaphores = &signalSem;
			m_vkGraphicsQueue->submit(submit, *m_inFlight[frame]);

			// показываем
			vk::SwapchainKHR swapchain = **m_vkSwapchain;
			vk::PresentInfoKHR present{};
			present.waitSemaphoreCount = 1;
			present.pWaitSemaphores = &signalSem;
			present.swapchainCount = 1;
			present.pSwapchains = &swapchain;
			present.pImageIndices = &imageIndex;

			try {
				vk::Result r = m_vkPresentQueue->presentKHR(present);
				if (r == vk::Result::eSuboptimalKHR) recreateSwapchain(window);
			}
			catch (const vk::OutOfDateKHRError&) {
				recreateSwapchain(window);
			}

			m_currentFrame = (m_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
			return true;
		}
		catch (const std::exception& e) {
			LOG_ERROR(e.what());
			return false;
		}
	}

} } }