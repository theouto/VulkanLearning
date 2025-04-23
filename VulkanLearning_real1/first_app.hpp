#pragma once

#include "lve_window.hpp"
#include "lve_device.hpp"
#include "lve_model.hpp"
#include "lve_game_object.hpp"
#include "lve_renderer.hpp"
#include "lve_descriptors.hpp"

#include <memory>
#include <vector>

namespace lve
{
	class FirstApp
	{
	public:
		static constexpr int WIDTH = 1600;
		static constexpr int HEIGHT = 900;


		FirstApp();
		~FirstApp();

		FirstApp(const FirstApp&) = delete;
		FirstApp& operator=(const FirstApp&) = delete;

		void run();

	private:
		void loadGameObjects();

		LveWindow lveWindow{ WIDTH, HEIGHT, "WINNING" };
		LveDevice lveDevice{ lveWindow };
		LveRenderer lveRenderer{ lveWindow, lveDevice };

		std::unique_ptr<LveDescriptorPool> globalPool{};
		LveGameObject::Map gameObjects;
	};
}