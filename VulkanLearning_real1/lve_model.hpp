#pragma once

#include "lve_device.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <memory>
#include <vector>

namespace lve
{
	class LveModel
	{

	public:

		struct Vertex
		{
			glm::vec3 position;
			glm::vec3 color;
			glm::vec3 normal{};
			glm::vec2 uv{};

			static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
			static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();

			bool operator ==(const Vertex& other) const { return position == other.position && color == other.color 
				&& normal == other.normal && uv == other.uv; }
		};

		struct Builder
		{
			std::vector<Vertex> vertices{};
			std::vector<uint32_t> indices{};

			void loadModel(const std::string& filepath);
		};

		LveModel(LveDevice & device, const LveModel::Builder &builder);
		~LveModel();

		LveModel(const LveModel&) = delete;
		LveModel& operator=(const LveModel&) = delete;
		
		VkImage textureImage;
		VkDeviceMemory textureImageMemory;
		VkImageCreateInfo imageInfo{};
		VkImageView textureImageView;
		VkSampler textureSampler;
		VkDescriptorSetLayout descriptorSetLayout;
		VkDescriptorPool descriptorPool;

		std::vector<VkDescriptorSet> descriptorSets;
		std::vector<VkBuffer> uniformBuffers;

		static std::unique_ptr<LveModel> createModelFromFile(LveDevice& device, const std::string &filepath);

		void bind(VkCommandBuffer);
		void draw(VkCommandBuffer);

	private:
		void createVertexBuffers(const std::vector<Vertex> &vertices);
		void createIndexBuffers(const std::vector<uint32_t>& indices);
		void createTextureImage();
		void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage,
			VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
		void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
		VkImageView createImageView(VkImage image, VkFormat format);
		void createTextureImageView();
		void createTextureSampler();
		void createDescriptorSetLayout();
		void createDescriptorPool();
		void createDescriptorSets();

		LveDevice &lveDevice;

		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;
		uint32_t vertexCount;
		
		bool hasIndexBuffer = false;
		VkBuffer indexBuffer;
		VkDeviceMemory indexBufferMemory;
		uint32_t indexCount;
	};
}