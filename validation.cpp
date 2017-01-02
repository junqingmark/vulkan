#include <vulkan.h>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	VkApplicationInfo appInfo;
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pNext = NULL;
	appInfo.pApplicationName = "vulkan Instance samples";
	appInfo.applicationVersion = 1;
	appInfo.pEngineName = "vulkan Instance samples";
	appInfo.engineVersion = 1;
	appInfo.apiVersion = VK_API_VERSION_1_0;

	//initialize vulkan instance structure
	VkInstanceCreateInfo instInfo;
	instInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instInfo.pNext = NULL;
	instInfo.flags = 0;
	instInfo.pApplicationInfo = &appInfo;
	instInfo.enabledLayerCount = 0;
	instInfo.ppEnabledLayerNames = NULL;
	instInfo.enabledExtensionCount = 0;
	instInfo.ppEnabledLayerNames = NULL;

	VkInstance instance;
	VkResult result;

	result = vkCreateInstance(&instInfo, NULL, &instance);
	if (result == VK_ERROR_INCOMPATIBLE_DRIVER)
	{
		cout << "Fail to find a compatible ICD" << endl;
		return -1;
	}
	else if (result)
	{
		cout << "unknown error!" << endl;
		return -1;
	}
	else
	{
		cout << "success in create vulkan instance!" << endl;
	}

	uint32_t gpu_count = 1;
	result = vkEnumeratePhysicalDevices(instance, &gpu_count, NULL);
	vector<VkPhysicalDevice> gpus;
	gpus.resize(gpu_count);
	result = vkEnumeratePhysicalDevices(instance, &gpu_count, gpus.data());

	if (!result && gpu_count >= 1)
	{
		VkPhysicalDeviceProperties physicPropertites;
		vkGetPhysicalDeviceProperties(gpus[0], &physicPropertites);
		if (physicPropertites.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		{
			cout << "The GPU is a discrete type!" << endl;
			cout << "The vendor is " << physicPropertites.vendorID << endl;
			cout << "The device name is " << physicPropertites.deviceName << endl;
		}
	}
	else
	{
		cout << "Fail to get physical devices" << endl;
	}

	vkDestroyInstance(instance, NULL);
	return 0;

}


