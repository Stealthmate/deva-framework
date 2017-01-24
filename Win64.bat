@echo off
py gen.py
mkdir Win64
cd Win64
cmake -DDEVA_BUILD_SPLIT:BOOL=FALSE -G "Visual Studio 14 Win64" ..
cd ..
