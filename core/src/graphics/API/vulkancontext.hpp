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

namespace heartCore { namespace graphics {
namespace API {

	struct VulkanContext {
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
		
		bool createVkInstance();
		bool createVkSurface(GLFWwindow* window);
		bool pickVkPhysicalDevice();
		bool createVkDevice();
	};

} } }