#pragma once
#include "definitions.h"
class Application
{
public:
	void run();

private:
	void initVulkan();
	void mainLoop();
	void garbageManager();

	GLFWwindow* window;
	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;

	// Step 1 - Create instance and pick physical device
	VkInstance instance;
};

