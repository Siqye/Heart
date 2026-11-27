#pragma once
#include "vulkancontext.hpp"
#include "../../maths/maths.hpp"
#include "../../utils/file_reader.hpp"
#include <array>
#include <memory>
#include <vector>

namespace heartCore { namespace graphics {
	namespace API {

	class VulkanShader
	{
	public:
		static constexpr std::uint32_t MAX_TEXTURES = 32;

		struct CameraData {
			float projection[16];
			float view[16];
		};

		VulkanShader(VulkanContext& context, const char* vertexSpvPath, const char* fragmentSpvPath);
		~VulkanShader() = default;

		VulkanShader(const VulkanShader&) = delete;
		VulkanShader& operator=(const VulkanShader&) = delete;

		bool isValid() const { return m_valid; }

		std::array<vk::PipelineShaderStageCreateInfo, 2> getStages() const;
		vk::DescriptorSetLayout getDescriptorSetLayout() const { return *m_descriptorSetLayout; }
		vk::PipelineLayout getPipelineLayout() const { return *m_pipelineLayout; }

		void bind(const vk::raii::CommandBuffer& cmd) const;

		void setProjection(const maths::mat4& matrix);
		void setView(const maths::mat4& matrix);
		void setModel(const vk::raii::CommandBuffer& cmd, const maths::mat4& matrix) const;
		void setTexture(std::uint32_t index, vk::ImageView view, vk::Sampler sampler);

	private:
		std::unique_ptr<vk::raii::ShaderModule> createModule(const char* path);
		bool createLayouts();
		bool createUniformBuffer();
		bool createDescriptorSet();
		void flushCamera();

		VulkanContext& m_context;

		std::unique_ptr<vk::raii::ShaderModule> m_vertexModule;
		std::unique_ptr<vk::raii::ShaderModule> m_fragmentModule;
		std::unique_ptr<vk::raii::DescriptorSetLayout> m_descriptorSetLayout;
		std::unique_ptr<vk::raii::PipelineLayout> m_pipelineLayout;
		std::unique_ptr<vk::raii::DescriptorPool> m_descriptorPool;
		std::unique_ptr<vk::raii::DescriptorSet> m_descriptorSet;
		std::unique_ptr<vk::raii::Buffer> m_uniformBuffer;
		std::unique_ptr<vk::raii::DeviceMemory> m_uniformMemory;
		void* m_uniformMapped = nullptr;

		CameraData m_camera{};
		bool m_valid = false;
	};
	}
} }
