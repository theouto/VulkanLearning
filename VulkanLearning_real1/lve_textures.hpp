#pragma once

#include "lve_device.hpp"
#include "lve_descriptors.hpp"
#include "lve_model.hpp"
#include "lve_buffer.hpp"

namespace lve
{
	class LveTextures
	{
	public:

		VkImage textureImage;
		VkDeviceMemory textureImageMemory;
		VkImageCreateInfo imageInfo{};
		VkImageView textureImageView;
		VkSampler textureSampler;

	private:
		void createTextureImage(LveDevice& device);
		void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage,
			VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	};
}