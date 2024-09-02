#include <iostream>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

int main()
{
	//Window Check-UP

	const int height = 800;
	const int width = 800;

	const char* title = "Real_Time_Renderer";
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	//Vulkan Check-Up
	VkInstance m_Instance;

	VkApplicationInfo app_Info = {};
	app_Info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_Info.pNext = nullptr;
	app_Info.pEngineName = "Real_Time_Engine";
	app_Info.pApplicationName = "Real_Time_Renderer";
	app_Info.engineVersion = 1;
	app_Info.applicationVersion = 1;

	VkInstanceCreateInfo Instance_CI{};

	Instance_CI.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	Instance_CI.pNext = nullptr;

	Instance_CI.enabledLayerCount = 0;
	Instance_CI.ppEnabledLayerNames = nullptr;

	Instance_CI.enabledExtensionCount = 0;
	Instance_CI.ppEnabledExtensionNames = nullptr;

	Instance_CI.pApplicationInfo = &app_Info;

	if (vkCreateInstance(&Instance_CI, nullptr, &m_Instance) != VK_SUCCESS)
	{
		throw std::runtime_error("Can't able to create the Instance");
	}
	else
	{
		std::cout << "YEAHHHHHHHHH BABBBBYYYYYYYYYYY!!!!!!!!!" << std::endl;
	}
}