#include "Application.h"


void Application::initWindow() {
	glfwInit(); // Initializing GLFW library

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Don't create OpenGL context
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Disabling resize for now

	window = glfwCreateWindow(WIDTH, HEIGHT, "Infinity Space", nullptr, nullptr);
}

void Application::setupDebugMessenger() {
	if (!enableValidationLayers) {
		return;
	}
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData) {

	std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
	return VK_FALSE;
}

void Application::initVulkan() {
	

	// Create instance & physical device
	this->createInstance();
	setupDebugMessenger();
}

void Application::mainLoop() {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

}

void Application::garbageManager() {
	
	vkDestroyInstance(this->instance, nullptr); // Destroying Vulkan instance


	// Last things to be destroyed
	glfwDestroyWindow(window);
	glfwTerminate();
}

///////////////////////////////////
//  Instance & physical device  ///
///////////////////////////////////

// Validation Layers
bool Application::checkValidationLayerSupport() {
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : validationLayers) {
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}

		if (!layerFound) {
			return false;
		}
	}

	return true;
}

// Getting required extensions
std::vector<const char*> Application::getRequiredExtensions() {
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (enableValidationLayers) {
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return extensions;
}

// Checking for support of required extensions
VkResult Application::checkRequiredExtensions(VkInstanceCreateInfo& instance_info) {

	uint32_t extensionCount = 0; // extensions needed by glfw to interact with the window system
	const char** glfwExtensions;

	glfwExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);

	instance_info.enabledExtensionCount = extensionCount;
	instance_info.ppEnabledExtensionNames = glfwExtensions;
	instance_info.enabledLayerCount = 0; // temporary
	
	// Result to see if all required extensions are there
	uint32_t required_extensions_number_support = 0;
	
	// This is extra to check for optional extension support but is entirely optional
	uint32_t optionalExtensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &optionalExtensionCount, nullptr);
	std::vector<VkExtensionProperties> extensions(optionalExtensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &optionalExtensionCount, extensions.data());

	for (const auto& extension : extensions)
	{
		std::cout << "\t" << extension.extensionName << std::endl;
		for (size_t i = 0; i < extensionCount - 1; i++)
		{
			if (std::strcmp(extension.extensionName, glfwExtensions[i]) == 0) {
				required_extensions_number_support++;
			}
		}
	}
	
	// I'll edit later as I find out if Vulkan can run without extensions
	if (extensionCount == 0) {
		std::cout << "\nNO EXTENSIONS REQUIRED" << std::endl;
	}

	if (required_extensions_number_support == extensionCount - 1  || extensionCount == 0) {
		return VK_SUCCESS;
	}
	return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void Application::createInstance() {
	// App info
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Infinity Space";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.apiVersion = VK_API_VERSION_1_0;

	// Instance Create Info
	VkInstanceCreateInfo instanceCreateInfo{};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pApplicationInfo = &appInfo;

	auto extensions = getRequiredExtensions();
	instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	instanceCreateInfo.ppEnabledExtensionNames = extensions.data();

	if (checkRequiredExtensions(instanceCreateInfo) != VK_SUCCESS) {
		throw std::runtime_error("No required extension supported!");
	}
	else {
		std::cout << "\nAll required extensions are supported";
	}

	// Finally, create the instance
	if (vkCreateInstance(&instanceCreateInfo, nullptr, &instance) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create instance");
	}
}




void Application::run() {
	this->initWindow();
	this->initVulkan();
	this->mainLoop();
	this->garbageManager();
}