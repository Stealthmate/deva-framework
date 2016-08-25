PFN_vkDestroyInstance                               vkDestroyInstance;

PFN_vkEnumeratePhysicalDevices                      vkEnumeratePhysicalDevices;
PFN_vkGetPhysicalDeviceFeatures                     vkGetPhysicalDeviceFeatures;
PFN_vkGetPhysicalDeviceProperties                   vkGetPhysicalDeviceProperties;
PFN_vkGetPhysicalDeviceQueueFamilyProperties        vkGetPhysicalDeviceQueueFamilyProperties;
PFN_vkGetPhysicalDeviceSurfaceSupportKHR            vkGetPhysicalDeviceSurfaceSupportKHR;

PFN_vkCreateDevice                                  vkCreateDevice;
PFN_vkDestroyDevice                                 vkDestroyDevice;

PFN_vkGetDeviceProcAddr                             vkGetDeviceProcAddr;
#ifdef VK_USE_PLATFORM_WIN32_KHR		                   

PFN_vkCreateWin32SurfaceKHR                         vkCreateWin32SurfaceKHR;
PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR  vkGetPhysicalDeviceWin32PresentationSupportKHR;

#endif

PFN_vkDestroySurfaceKHR                             vkDestroySurfaceKHR;

PFN_vkAcquireNextImageKHR                           vkAcquireNextImageKHR;
