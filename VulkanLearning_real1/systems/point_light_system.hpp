#pragma once

#include "C:\Users\tomyo\source\repos\VulkanLearning_real1\VulkanLearning_real1\lve_camera.hpp"
#include "C:\Users\tomyo\source\repos\VulkanLearning_real1\VulkanLearning_real1\lve_pipeline.hpp"
#include "C:\Users\tomyo\source\repos\VulkanLearning_real1\VulkanLearning_real1\lve_device.hpp"
#include "C:\Users\tomyo\source\repos\VulkanLearning_real1\VulkanLearning_real1\lve_model.hpp"
#include "C:\Users\tomyo\source\repos\VulkanLearning_real1\VulkanLearning_real1\lve_game_object.hpp"
#include "C:\Users\tomyo\source\repos\VulkanLearning_real1\VulkanLearning_real1\lve_frame_info.hpp"

#include <memory>
#include <vector>

namespace lve
{
	class PointLightSystem
	{
	public:

		PointLightSystem(LveDevice& device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
		~PointLightSystem();

		PointLightSystem(const PointLightSystem&) = delete;
		PointLightSystem& operator=(const PointLightSystem&) = delete;

		void update(FrameInfo& frameInfo, GlobalUbo &ubo);
		void render(FrameInfo &frameInfo);
	private:
		void createPipeLineLayout(VkDescriptorSetLayout globalSetLayout);
		void createPipeline(VkRenderPass renderPass);

		LveDevice& lveDevice;
		std::unique_ptr<LvePipeline> lvePipeline;
		VkPipelineLayout pipelineLayout;
	};
}