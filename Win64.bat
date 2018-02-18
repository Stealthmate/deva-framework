@echo off
py gen.py
mkdir Win64
cd Win64
cmake -DVK_LIB_PATH_D:STRING="C:\VulkanSDK\1.0.65.1\build\loader\Debug" -DVK_LIB_PATH:STRING="C:\VulkanSDK\1.0.65.1\build\loader\Release" -DDEVA_BUILD_SPLIT:BOOL=FALSE -G "Visual Studio 15 Win64" ..
cd ..
