#pragma once

#include "lve_camera.hpp"

#include <vulkan/vulkan.h>

namespace lve
{
	struct FrameInfo
	{
		int frameIndex;
		float frameTIme;
		VkCommandBuffer commandBuffer;
		LveCamera& camera;
	};
}