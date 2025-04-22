#include "first_app.hpp"

#include "keyboard_movement_controller.hpp"
#include "simple_render_system.hpp"
#include "lve_camera.hpp"
#include "lve_buffer.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm.hpp>
#include <gtc/constants.hpp>

#include <iostream>
#include <stdexcept>
#include <chrono>
#include <array>

namespace lve
{
    struct GlobalUbo
    {
        glm::mat4 projectionView{ 1.f };
        glm::vec3 lightDirection = glm::normalize(glm::vec3{ 1.f, -3.f, -1.f });
    };


	FirstApp::FirstApp(){loadGameObjects();}

	FirstApp::~FirstApp() {}


	void FirstApp::run()
	{

        std::vector<std::unique_ptr<LveBuffer>> uboBuffers(LveSwapChain::MAX_FRAMES_IN_FLIGHT);
        for (int i = 0; i < uboBuffers.size(); i++)
        {
            uboBuffers[i] = std::make_unique<LveBuffer>(
                lveDevice,
                sizeof(GlobalUbo),
                1,
                VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, 
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
            uboBuffers[i]->map();
        }

		SimpleRenderSystem simpleRenderSystem{ lveDevice, lveRenderer.getSwapChainRenderPass() };
        LveCamera camera{};

        auto viewerObject = LveGameObject::createGameObject();

        // https://www.glfw.org/docs/3.3/input_guide.html#raw_mouse_motion <- important
        glfwSetInputMode(lveWindow.getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        if (glfwRawMouseMotionSupported())
        {
            glfwSetInputMode(lveWindow.getGLFWwindow(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        }     

        KeyboardMovementController cameraController{};

        double mouseX = 0.f;
        double mouseY = 0.f;

        auto currentTime = std::chrono::high_resolution_clock::now();
		while (!lveWindow.shouldClose())
		{
			glfwPollEvents();

            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            //std::cout << "Framerate: " << 1 / frameTime << '\n';
            currentTime = newTime;
            
            cameraController.moveInPlaneXZ(lveWindow.getGLFWwindow(), frameTime, viewerObject, mouseX, mouseY);
            glfwGetCursorPos(lveWindow.getGLFWwindow(), &mouseX, &mouseY);
            camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

            float aspect = lveRenderer.getAspectRatio();
            camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 10.f);

			if (auto commandBuffer = lveRenderer.beginFrame())
			{
                int frameIndex = lveRenderer.getFrameIndex();
                FrameInfo frameInfo{
                    frameIndex,
                    frameTime,
                    commandBuffer,
                    camera
                };
                //update               
                GlobalUbo ubo{};
                ubo.projectionView = camera.getProjection() * camera.getView();
                uboBuffers[frameIndex]->writeToBuffer(&ubo);
                uboBuffers[frameIndex]->flush();    

                //render
				lveRenderer.beginSwapChainRenderPass(commandBuffer);
				simpleRenderSystem.renderGameObjects(frameInfo, gameObjects);
				lveRenderer.endSwapChainRenderPass(commandBuffer);
				lveRenderer.endFrame();
			}
		}

		vkDeviceWaitIdle(lveDevice.device());
	}

	void FirstApp::loadGameObjects()
	{
        std::shared_ptr<LveModel> lveModel = LveModel::createModelFromFile(lveDevice, "models/AOI.obj");
        auto gameObj = LveGameObject::createGameObject();
        gameObj.model = lveModel;
        gameObj.transform.translation = { .0f, .5f, 2.5f };
        gameObj.transform.scale = { .5f, -.5f, .5f };
        gameObjects.push_back(std::move(gameObj));

        lveModel = LveModel::createModelFromFile(lveDevice, "models/smooth_vase.obj");
        auto sVase = LveGameObject::createGameObject();
        sVase.model = lveModel;
        sVase.transform.translation = { -.5f, .0f, 2.5f };
        sVase.transform.scale = { .5f, .5f, .5f };
        gameObjects.push_back(std::move(sVase));

        lveModel = LveModel::createModelFromFile(lveDevice, "models/flat_vase.obj");
        auto vase = LveGameObject::createGameObject();
        vase.model = lveModel;
        vase.transform.translation = { .5f, .0f, 2.5f };
        vase.transform.scale = { .5f, .5f, .5f };
        gameObjects.push_back(std::move(vase));
	}

}