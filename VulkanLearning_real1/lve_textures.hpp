#pragma once

#include "lve_device.hpp"
#include "lve_descriptors.hpp"
#include "lve_model.hpp"

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
		void createTextureImage();
		void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage,
			VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
		void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
		VkImageView createImageView(VkImage image, VkFormat format);
		void createTextureImageView();
		void createTextureSampler();

		LveDevice& lveDevice;

	};
}