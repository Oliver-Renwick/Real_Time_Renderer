#pragma once
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <vector>

#ifdef _DEBUG
const bool enableValidationLayer = true;

#else

const bool enableValidationLayer = false;

#endif

namespace RE
{
	class Vulkan_Base
	{
	public:
		Vulkan_Base();
		~Vulkan_Base();

	private:
		void initVulkan();

		bool CheckValidationSupport();

		std::vector<const char*> GetRequiredExtension();

		VkDebugUtilsMessengerCreateInfoEXT PopulateDebugUtilsMessenger();

		void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	private:
		VkInstance m_Instance = VK_NULL_HANDLE;
		VkDebugUtilsMessengerEXT debugMessenger;

		std::vector<const char*> validationLayers = {
			"VK_LAYER_KHRONOS_validation"
		};
	};
}