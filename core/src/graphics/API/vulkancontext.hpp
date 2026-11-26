#pragma once
#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_raii.hpp>
#include <glfw3.h>
#include "../../logger/logger.hpp"
#include <memory>
#include <vector>
#include <set>
#include <cstring>
#include <algorithm>
#include <array>
#include <limits>

namespace heartCore { namespace graphics {
namespace API {

	struct VulkanContext {
	private:
		uint32_t MAX_FRAMES_IN_FLIGHT = 999999;
	public:

		vk::raii::Context m_vkContext;
		std::unique_ptr<vk::raii::Instance> m_vkInstance;
		std::unique_ptr<vk::raii::DebugUtilsMessengerEXT> m_vkDebugMessenger;
		std::unique_ptr<vk::raii::SurfaceKHR> m_vkSurface;
		std::unique_ptr<vk::raii::PhysicalDevice> m_vkPhysicalDevice;
		std::unique_ptr<vk::raii::Device> m_vkDevice;
		std::unique_ptr<vk::raii::Queue> m_vkGraphicsQueue;
		std::unique_ptr<vk::raii::Queue> m_vkPresentQueue;

		std::uint32_t m_graphicsFamily = 0;
		std::uint32_t m_presentFamily = 0;

		// swap buffer
		std::unique_ptr<vk::raii::SwapchainKHR> m_vkSwapchain;
		std::vector<vk::Image> m_swapImages;
		vk::Format m_swapFormat = vk::Format::eUndefined;
		vk::Extent2D m_swapExtent{};

		std::unique_ptr<vk::raii::CommandPool> m_vkCommandPool;
		std::vector<vk::raii::CommandBuffer> m_vkCommandBuffers;
		std::vector<vk::raii::Semaphore> m_imageAvailable;
		std::vector<vk::raii::Semaphore> m_renderFinished;
		std::vector<vk::raii::Fence> m_inFlight;      
		std::uint32_t m_currentFrame = 0;
		
		bool createVkInstance();
		bool createVkSurface(GLFWwindow* window);
		bool pickVkPhysicalDevice();
		bool createVkDevice();

		bool createVkInstance();
		bool createVkSurface(GLFWwindow* window);
		bool pickVkPhysicalDevice();
		bool createVkDevice();

		bool createSwapBuffer(GLFWwindow* window);   // swapchain + command buffers + sync
		bool swapBuffer(GLFWwindow* window);         // acquire -> record -> submit -> present

		void cleanup();
	private:
		bool createSwapchain(GLFWwindow* window);
		bool recreateSwapchain(GLFWwindow* window);
		void recordCommands(vk::raii::CommandBuffer& cmd, vk::Image image);
	};

} } }