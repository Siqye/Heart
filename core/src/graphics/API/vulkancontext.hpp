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
#include <cstdint>
#include <limits>

namespace heartCore { namespace graphics {
namespace API {

	struct VulkanContext {
		vk::raii::Context m_vkContext;
		
		std::unique_ptr<vk::raii::Instance> m_vkInstance;
		std::unique_ptr<vk::raii::DebugUtilsMessengerEXT> m_vkDebugMessenger;
		std::unique_ptr<vk::raii::SurfaceKHR> m_vkSurface;
		std::unique_ptr<vk::raii::PhysicalDevice> m_vkPhysicalDevice;
		std::unique_ptr<vk::raii::Device> m_vkDevice;
		std::unique_ptr<vk::raii::SwapchainKHR> m_vkSwapchain;
		std::vector<vk::Image> m_swapchainImages;
		std::vector<vk::raii::ImageView> m_swapchainImageViews;
		GLFWwindow* m_window = nullptr;

		vk::Format m_swapchainImageFormat = vk::Format::eUndefined;
		vk::Extent2D m_swapchainExtent{};
		std::uint32_t m_graphicsFamily = 0;
		std::uint32_t m_presentFamily = 0;
		
		bool createVkInstance();
		bool createVkSurface(GLFWwindow* window);
		bool pickVkPhysicalDevice();
		bool createVkDevice();
		bool createVkSwapchain();
		bool recreateVkSwapchain();
		bool acquireNextImage(std::uint32_t& imageIndex);

		const std::vector<vk::raii::ImageView>& getSwapchainImageViews() const { return m_swapchainImageViews; }
		vk::Format getSwapchainImageFormat() const { return m_swapchainImageFormat; }
		vk::Extent2D getSwapchainExtent() const { return m_swapchainExtent; }
	};

} } }