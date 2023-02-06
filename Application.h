#pragma once
#include "definitions.h"
class Application
{
public:
	void run();

private:
	// Functions
	void initWindow(); // Initializing window with GLFW
	void initVulkan();
	void mainLoop(); // Rendering loop
	void garbageManager(); // Garbage Collector
	void createInstance(); // Create Vulkan Instance
	VkResult checkRequiredExtensions(VkInstanceCreateInfo& instance_info);
	bool checkValidationLayerSupport();
	std::vector<const char*> getRequiredExtensions();
	void setupDebugMessenger();
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);

	// Member fields
	GLFWwindow* window;
	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;
	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
	// Validation Layers
	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif // DEBUG


};

