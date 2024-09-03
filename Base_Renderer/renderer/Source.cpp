#define Height  800
#define Width  800


#include "window.h"
#include "Vulkan_base/Vulkan_base.h"

int main()
{
	//Window initialization
	RE::Window win{Height,Width,"Real-Time Renderer"};
	RE::Vulkan_Base vulkan_ren;

	//RunLoop
	while (!glfwWindowShouldClose(win.getWindow()))
	{
		glfwPollEvents();


	}


}