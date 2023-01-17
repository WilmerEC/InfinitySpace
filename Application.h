#pragma once
#include "definitions.h"
class Application
{
public:
	void run();

private:
	void initWindow(); // Initializing window with GLFW
	void initVulkan();
	void mainLoop(); // Rendering loop
	void garbageManager(); // Garbage Collector
	void createInstance(); // Create Vulkan Instance
	VkResult checkRequiredExtensions(VkInstanceCreateInfo& instance_info);
	GLFWwindow* window;
	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;

	// Step 1 - Create instance and pick physical device
	VkInstance instance;
};

