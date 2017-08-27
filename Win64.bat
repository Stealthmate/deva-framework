@echo off
py gen.py
mkdir Win64
cd Win64
cmake -DDEVA_BUILD_SPLIT:BOOL=FALSE -G "Visual Studio 15 Win64" ..
cd ..
