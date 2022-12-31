#include "Application.h"


void Application::initVulkan() {
	glfwInit();
	
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Infinity Space", nullptr, nullptr);

	// Create instance & physical device
}

void Application::mainLoop() {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

}

void Application::garbageManager() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

///////////////////////////////////
//  Instance & physical device  ///
///////////////////////////////////

void createInstance() {
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

}


void Application::run() {
	this->initVulkan();
	this->mainLoop();
	this->garbageManager();
}