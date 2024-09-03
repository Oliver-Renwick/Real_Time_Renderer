#include "Vulkan_base.h"

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData) {

	std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

	return VK_FALSE;
}

namespace RE
{
	Vulkan_Base::Vulkan_Base()
	{
		initVulkan();
	}

	Vulkan_Base::~Vulkan_Base()
	{
		if (enableValidationLayer)
		{
			DestroyDebugUtilsMessengerEXT(m_Instance, debugMessenger, nullptr);
		}

		vkDestroyInstance(m_Instance, nullptr);
	}

	void Vulkan_Base::initVulkan()
	{
		if (enableValidationLayer && !CheckValidationSupport())
		{
			throw std::runtime_error("Validation layer is requested, but not available.");
		}
		//Instance Creation
		VkApplicationInfo appInfo = {};

		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pNext = nullptr;
		appInfo.pEngineName = "Real_Time_Renderer_Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
		appInfo.pApplicationName = "Real_Time_Application";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);

		VkInstanceCreateInfo InstanceCI = {};
		
		InstanceCI.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		InstanceCI.pApplicationInfo = &appInfo;

		//glfw Extension
		std::vector<const char*> extensions = GetRequiredExtension();
		InstanceCI.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		InstanceCI.ppEnabledExtensionNames = extensions.data();

		//EnableLayers
		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
		if (enableValidationLayer)
		{
			InstanceCI.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			InstanceCI.ppEnabledLayerNames = validationLayers.data();

			debugCreateInfo = PopulateDebugUtilsMessenger();

			InstanceCI.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
		}
		else
		{
			InstanceCI.enabledLayerCount = 0;
			InstanceCI.pNext = nullptr;
		}


		if (vkCreateInstance(&InstanceCI, nullptr, &m_Instance) != VK_SUCCESS)
		{
			throw std::runtime_error("Cannot create the Vulkan Instance!!");
		}
		else
		{
			std::cout << "Successfully created vulkan Instance" << std::endl;
		}

		//Validation Layer

		VkDebugUtilsMessengerCreateInfoEXT DebugInfo = PopulateDebugUtilsMessenger();

		if (CreateDebugUtilsMessengerEXT(m_Instance, &DebugInfo, nullptr, &debugMessenger) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to set up debug messenger!");
		}

	}

	VkDebugUtilsMessengerCreateInfoEXT Vulkan_Base::PopulateDebugUtilsMessenger()
	{
		VkDebugUtilsMessengerCreateInfoEXT DebugMessageCI{};
		DebugMessageCI.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		DebugMessageCI.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		DebugMessageCI.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		DebugMessageCI.pfnUserCallback = debugCallback;

		return DebugMessageCI;
	}

	std::vector<const char*> Vulkan_Base::GetRequiredExtension()
	{
		uint32_t glfw_extensionCount = 0;

		const char** glfw_Extension = nullptr;

		glfw_Extension = glfwGetRequiredInstanceExtensions(&glfw_extensionCount);

		std::vector<const char*> extension(glfw_Extension, glfw_Extension + glfw_extensionCount);

		if (enableValidationLayer)
		{
			extension.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		return extension;
	}

	bool Vulkan_Base::CheckValidationSupport()
	{
		uint32_t layer_Count = 0;

		vkEnumerateInstanceLayerProperties(&layer_Count, nullptr);

		std::vector<VkLayerProperties> availableLayers(layer_Count);

		vkEnumerateInstanceLayerProperties(&layer_Count, availableLayers.data());

		for (const char* layerName : validationLayers)
		{
			bool layerfound = false;

			for (const auto& layerproperty : availableLayers)
			{
				if (std::strcmp(layerName, layerproperty.layerName) == 0)
				{
					layerfound = true;
					break;
				}
			}
			if (layerfound)
			{
				return true;
			}
		}
		return false;
	}

	VkResult Vulkan_Base::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void Vulkan_Base::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (func != nullptr) {
			func(instance, debugMessenger, pAllocator);
		}
	}
}