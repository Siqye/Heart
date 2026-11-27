#include "vulkanshader.hpp"
#include <cstring>

namespace heartCore { namespace graphics {
	namespace API {

	VulkanShader::VulkanShader(VulkanContext& context, const char* vertexSpvPath, const char* fragmentSpvPath)
		: m_context(context)
	{
		if (!m_context.m_vkDevice || !m_context.m_vkPhysicalDevice) {
			LOG_ERROR("VulkanShader: device is not created");
			return;
		}

		float identity[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
		std::memcpy(m_camera.projection, identity, sizeof(identity));
		std::memcpy(m_camera.view, identity, sizeof(identity));

		m_vertexModule = createModule(vertexSpvPath);
		m_fragmentModule = createModule(fragmentSpvPath);
		if (!m_vertexModule || !m_fragmentModule) return;

		m_valid = createLayouts() && createUniformBuffer() && createDescriptorSet();
		if (m_valid) flushCamera();
	}

	std::unique_ptr<vk::raii::ShaderModule> VulkanShader::createModule(const char* path)
	{
		std::vector<char> code = readFileBinary(path);
		if (code.empty() || code.size() % 4 != 0) {
			LOG_ERROR(std::string("VulkanShader: failed to read SPIR-V: ") + path);
			return nullptr;
		}

		// vector<char> выровнен под uint32_t, но копируем для безопасности
		std::vector<std::uint32_t> words(code.size() / 4);
		std::memcpy(words.data(), code.data(), code.size());

		vk::ShaderModuleCreateInfo info{
			.codeSize = code.size(),
			.pCode = words.data()
		};
		try {
			return std::make_unique<vk::raii::ShaderModule>(*m_context.m_vkDevice, info);
		}
		catch (const std::exception& e) {
			LOG_ERROR(std::string("VulkanShader: failed to create shader module (") + path + "): " + e.what());
			return nullptr;
		}
	}

	bool VulkanShader::createLayouts()
	{
		try {
			std::array<vk::DescriptorSetLayoutBinding, 2> bindings{
				vk::DescriptorSetLayoutBinding{
					.binding = 0,
					.descriptorType = vk::DescriptorType::eUniformBuffer,
					.descriptorCount = 1,
					.stageFlags = vk::ShaderStageFlagBits::eVertex
				},
				vk::DescriptorSetLayoutBinding{
					.binding = 1,
					.descriptorType = vk::DescriptorType::eCombinedImageSampler,
					.descriptorCount = MAX_TEXTURES,
					.stageFlags = vk::ShaderStageFlagBits::eFragment
				}
			};
			vk::DescriptorSetLayoutCreateInfo layoutInfo{
				.bindingCount = static_cast<std::uint32_t>(bindings.size()),
				.pBindings = bindings.data()
			};
			m_descriptorSetLayout = std::make_unique<vk::raii::DescriptorSetLayout>(*m_context.m_vkDevice, layoutInfo);

			vk::PushConstantRange pushRange{
				.stageFlags = vk::ShaderStageFlagBits::eVertex,
				.offset = 0,
				.size = sizeof(float) * 16
			};
			vk::DescriptorSetLayout setLayout = **m_descriptorSetLayout;
			vk::PipelineLayoutCreateInfo pipelineInfo{
				.setLayoutCount = 1,
				.pSetLayouts = &setLayout,
				.pushConstantRangeCount = 1,
				.pPushConstantRanges = &pushRange
			};
			m_pipelineLayout = std::make_unique<vk::raii::PipelineLayout>(*m_context.m_vkDevice, pipelineInfo);
			return true;
		}
		catch (const std::exception& e) {
			LOG_ERROR(std::string("VulkanShader: failed to create layouts: ") + e.what());
			return false;
		}
	}

	bool VulkanShader::createUniformBuffer()
	{
		try {
			vk::BufferCreateInfo bufferInfo{
				.size = sizeof(CameraData),
				.usage = vk::BufferUsageFlagBits::eUniformBuffer,
				.sharingMode = vk::SharingMode::eExclusive
			};
			m_uniformBuffer = std::make_unique<vk::raii::Buffer>(*m_context.m_vkDevice, bufferInfo);

			vk::MemoryRequirements req = m_uniformBuffer->getMemoryRequirements();
			vk::PhysicalDeviceMemoryProperties props = m_context.m_vkPhysicalDevice->getMemoryProperties();
			vk::MemoryPropertyFlags wanted = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;

			std::uint32_t typeIndex = UINT32_MAX;
			for (std::uint32_t i = 0; i < props.memoryTypeCount; ++i) {
				if ((req.memoryTypeBits & (1u << i)) && (props.memoryTypes[i].propertyFlags & wanted) == wanted) {
					typeIndex = i;
					break;
				}
			}
			if (typeIndex == UINT32_MAX) {
				LOG_ERROR("VulkanShader: no suitable memory type for uniform buffer");
				return false;
			}

			vk::MemoryAllocateInfo allocInfo{
				.allocationSize = req.size,
				.memoryTypeIndex = typeIndex
			};
			m_uniformMemory = std::make_unique<vk::raii::DeviceMemory>(*m_context.m_vkDevice, allocInfo);
			m_uniformBuffer->bindMemory(**m_uniformMemory, 0);
			m_uniformMapped = m_uniformMemory->mapMemory(0, sizeof(CameraData));
			return true;
		}
		catch (const std::exception& e) {
			LOG_ERROR(std::string("VulkanShader: failed to create uniform buffer: ") + e.what());
			return false;
		}
	}

	bool VulkanShader::createDescriptorSet()
	{
		try {
			std::array<vk::DescriptorPoolSize, 2> sizes{
				vk::DescriptorPoolSize{ .type = vk::DescriptorType::eUniformBuffer, .descriptorCount = 1 },
				vk::DescriptorPoolSize{ .type = vk::DescriptorType::eCombinedImageSampler, .descriptorCount = MAX_TEXTURES }
			};
			vk::DescriptorPoolCreateInfo poolInfo{
				.flags = vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet,
				.maxSets = 1,
				.poolSizeCount = static_cast<std::uint32_t>(sizes.size()),
				.pPoolSizes = sizes.data()
			};
			m_descriptorPool = std::make_unique<vk::raii::DescriptorPool>(*m_context.m_vkDevice, poolInfo);

			vk::DescriptorSetLayout setLayout = **m_descriptorSetLayout;
			vk::DescriptorSetAllocateInfo allocInfo{
				.descriptorPool = **m_descriptorPool,
				.descriptorSetCount = 1,
				.pSetLayouts = &setLayout
			};
			vk::raii::DescriptorSets sets(*m_context.m_vkDevice, allocInfo);
			m_descriptorSet = std::make_unique<vk::raii::DescriptorSet>(std::move(sets.front()));

			vk::DescriptorBufferInfo bufferInfo{
				.buffer = **m_uniformBuffer,
				.offset = 0,
				.range = sizeof(CameraData)
			};
			vk::WriteDescriptorSet write{
				.dstSet = **m_descriptorSet,
				.dstBinding = 0,
				.dstArrayElement = 0,
				.descriptorCount = 1,
				.descriptorType = vk::DescriptorType::eUniformBuffer,
				.pBufferInfo = &bufferInfo
			};
			m_context.m_vkDevice->updateDescriptorSets(write, {});
			return true;
		}
		catch (const std::exception& e) {
			LOG_ERROR(std::string("VulkanShader: failed to create descriptor set: ") + e.what());
			return false;
		}
	}

	std::array<vk::PipelineShaderStageCreateInfo, 2> VulkanShader::getStages() const
	{
		return {
			vk::PipelineShaderStageCreateInfo{
				.stage = vk::ShaderStageFlagBits::eVertex,
				.module = **m_vertexModule,
				.pName = "main"
			},
			vk::PipelineShaderStageCreateInfo{
				.stage = vk::ShaderStageFlagBits::eFragment,
				.module = **m_fragmentModule,
				.pName = "main"
			}
		};
	}

	void VulkanShader::bind(const vk::raii::CommandBuffer& cmd) const
	{
		cmd.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, *m_pipelineLayout, 0, { **m_descriptorSet }, {});
	}

	void VulkanShader::flushCamera()
	{
		if (m_uniformMapped) std::memcpy(m_uniformMapped, &m_camera, sizeof(CameraData));
	}

	void VulkanShader::setProjection(const maths::mat4& matrix)
	{
		std::memcpy(m_camera.projection, matrix.elements, sizeof(float) * 16);
		flushCamera();
	}

	void VulkanShader::setView(const maths::mat4& matrix)
	{
		std::memcpy(m_camera.view, matrix.elements, sizeof(float) * 16);
		flushCamera();
	}

	void VulkanShader::setModel(const vk::raii::CommandBuffer& cmd, const maths::mat4& matrix) const
	{
		cmd.pushConstants<float>(*m_pipelineLayout, vk::ShaderStageFlagBits::eVertex, 0,
			vk::ArrayProxy<const float>(16, matrix.elements));
	}

	void VulkanShader::setTexture(std::uint32_t index, vk::ImageView view, vk::Sampler sampler)
	{
		if (index >= MAX_TEXTURES || !m_descriptorSet) return;
		vk::DescriptorImageInfo imageInfo{
			.sampler = sampler,
			.imageView = view,
			.imageLayout = vk::ImageLayout::eShaderReadOnlyOptimal
		};
		vk::WriteDescriptorSet write{
			.dstSet = **m_descriptorSet,
			.dstBinding = 1,
			.dstArrayElement = index,
			.descriptorCount = 1,
			.descriptorType = vk::DescriptorType::eCombinedImageSampler,
			.pImageInfo = &imageInfo
		};
		m_context.m_vkDevice->updateDescriptorSets(write, {});
	}

	}
} }
