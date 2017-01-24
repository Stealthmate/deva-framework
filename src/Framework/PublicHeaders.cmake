set(
	DEVA_FRAMEWORK_PUBLIC_HEADERS
	${CURDIR}/Exceptions/DevaException.cpp
	${CURDIR}/Exceptions/DevaException.hpp
	${CURDIR}/Exceptions/DevaExternalFailureException.cpp
	${CURDIR}/Exceptions/DevaExternalFailureException.hpp
	${CURDIR}/Exceptions/DevaFailureException.cpp
	${CURDIR}/Exceptions/DevaFailureException.hpp
	${CURDIR}/Exceptions/DevaInitializationFailureException.hpp
	${CURDIR}/Exceptions/DevaProgrammerErrorException.cpp
	${CURDIR}/Exceptions/DevaProgrammerErrorException.hpp
	${CURDIR}/Graphics/Config.hpp
	${CURDIR}/Graphics/Font.hpp
	${CURDIR}/Graphics/Image.cpp
	${CURDIR}/Graphics/Image.hpp
	${CURDIR}/Graphics/ImageReaders.cpp
	${CURDIR}/Graphics/ImageReaders.hpp
	${CURDIR}/Graphics/Init.cpp
	${CURDIR}/Graphics/Init.hpp
	${CURDIR}/Graphics/Master.hpp
	${CURDIR}/Graphics/OpenGL.hpp
	${CURDIR}/Graphics/Vulkan.hpp
	${CURDIR}/Graphics/OpenGL/Common.cpp
	${CURDIR}/Graphics/OpenGL/Common.hpp
	${CURDIR}/Graphics/OpenGL/Config.hpp
	${CURDIR}/Graphics/OpenGL/glConfig.hpp
	${CURDIR}/Graphics/OpenGL/glFunctions.hpp
	${CURDIR}/Graphics/OpenGL/glTypes.hpp
	${CURDIR}/Graphics/OpenGL/Model.cpp
	${CURDIR}/Graphics/OpenGL/Model.hpp
	${CURDIR}/Graphics/OpenGL/Shader.cpp
	${CURDIR}/Graphics/OpenGL/Shader.hpp
	${CURDIR}/Graphics/OpenGL/ShaderProgram.cpp
	${CURDIR}/Graphics/OpenGL/ShaderProgram.hpp
	${CURDIR}/Graphics/OpenGL/ShaderVariable.hpp
	${CURDIR}/Graphics/OpenGL/ShaderVariableDataType.cpp
	${CURDIR}/Graphics/OpenGL/ShaderVariableDataType.hpp
	${CURDIR}/Graphics/OpenGL/ShaderVariableDataType_int.cpp
	${CURDIR}/Graphics/OpenGL/ShaderVariableDataType_int.hpp
	${CURDIR}/Graphics/OpenGL/ShaderVariableFactory.hpp
	${CURDIR}/Graphics/OpenGL/VertexBufferObject.cpp
	${CURDIR}/Graphics/OpenGL/VertexBufferObject.hpp
	${CURDIR}/Graphics/Vulkan/Common.cpp
	${CURDIR}/Graphics/Vulkan/Common.hpp
	${CURDIR}/Graphics/Vulkan/Config.cpp
	${CURDIR}/Graphics/Vulkan/Config.hpp
	${CURDIR}/Graphics/Vulkan/ImplDefaultVulkanDeviceFunctionSet.cpp
	${CURDIR}/Graphics/Vulkan/ImplDefaultVulkanDeviceFunctionSet.hpp
	${CURDIR}/Graphics/Vulkan/ImplDefaultVulkanInstanceFunctionSet.cpp
	${CURDIR}/Graphics/Vulkan/ImplDefaultVulkanInstanceFunctionSet.hpp
	${CURDIR}/Graphics/Vulkan/InstanceFunctionSet.cpp
	${CURDIR}/Graphics/Vulkan/InstanceFunctionSet.hpp
	${CURDIR}/Graphics/Vulkan/Surface.cpp
	${CURDIR}/Graphics/Vulkan/Surface.hpp
	${CURDIR}/Graphics/Vulkan/VulkanAPI.hpp
	${CURDIR}/Graphics/Vulkan/VulkanDeleter.hpp
	${CURDIR}/Graphics/Vulkan/VulkanDevice.cpp
	${CURDIR}/Graphics/Vulkan/VulkanDevice.hpp
	${CURDIR}/Graphics/Vulkan/VulkanDeviceFunctionSet.cpp
	${CURDIR}/Graphics/Vulkan/VulkanDeviceFunctionSet.hpp
	${CURDIR}/Graphics/Vulkan/VulkanException.hpp
	${CURDIR}/Graphics/Vulkan/VulkanInstance.cpp
	${CURDIR}/Graphics/Vulkan/VulkanInstance.hpp
	${CURDIR}/Graphics/Vulkan/VulkanLogicalDevice.hpp
	${CURDIR}/Graphics/Vulkan/VulkanPhysicalDevice.cpp
	${CURDIR}/Graphics/Vulkan/VulkanPhysicalDevice.hpp
	${CURDIR}/Graphics/Vulkan/VulkanPipeline.hpp
	${CURDIR}/Graphics/Vulkan/VulkanShader.hpp
	${CURDIR}/Graphics/Vulkan/VulkanSurface.hpp
	${CURDIR}/Graphics/Vulkan/win32_LoadVulkan.cpp
	${CURDIR}/Math/BaseMatrix.hpp
	${CURDIR}/Math/BaseVector.hpp
	${CURDIR}/Math/Config.hpp
	${CURDIR}/Math/EulerAngles.hpp
	${CURDIR}/Math/Init.cpp
	${CURDIR}/Math/Init.hpp
	${CURDIR}/Math/Master.hpp
	${CURDIR}/Math/Matrix.cpp
	${CURDIR}/Math/Matrix.hpp
	${CURDIR}/Math/MatrixFactory.cpp
	${CURDIR}/Math/MatrixFactory.hpp
	${CURDIR}/Math/Quaternion.cpp
	${CURDIR}/Math/Quaternion.hpp
	${CURDIR}/Math/Vector.hpp
	${CURDIR}/Memory/Allocator.cpp
	${CURDIR}/Memory/Allocator.hpp
	${CURDIR}/Memory/Config.hpp
	${CURDIR}/Memory/LinearAllocator.cpp
	${CURDIR}/Memory/LinearAllocator.hpp
	${CURDIR}/Memory/PoolAllocator.cpp
	${CURDIR}/Memory/PoolAllocator.hpp
	${CURDIR}/Util/BinaryFileStreamWrapper.cpp
	${CURDIR}/Util/BinaryFileStreamWrapper.hpp
	${CURDIR}/Util/BinaryReader.hpp
	${CURDIR}/Util/BinaryWriter.hpp
	${CURDIR}/Util/ByteBuffer.cpp
	${CURDIR}/Util/ByteBuffer.hpp
	${CURDIR}/Util/Common.cpp
	${CURDIR}/Util/Common.hpp
	${CURDIR}/Util/Config.hpp
	${CURDIR}/Util/CStructDeleter.cpp
	${CURDIR}/Util/CStructDeleter.hpp
	${CURDIR}/Util/Init.cpp
	${CURDIR}/Util/Init.hpp
	${CURDIR}/Util/Master.hpp
	${CURDIR}/Window/Config.hpp
	${CURDIR}/Window/ImplWindow.cpp
	${CURDIR}/Window/Init.cpp
	${CURDIR}/Window/Init.hpp
	${CURDIR}/Window/Input.hpp
	${CURDIR}/Window/Keyboard.hpp
	${CURDIR}/Window/Keymap.hpp
	${CURDIR}/Window/Master.hpp
	${CURDIR}/Window/Window.cpp
	${CURDIR}/Window/Window.hpp
	${CURDIR}/Window/WindowEventInfo.hpp
	${CURDIR}/Window/WindowEventListener.cpp
	${CURDIR}/Window/WindowEventListener.hpp
	${CURDIR}/Window/WindowObserver.cpp
	${CURDIR}/Window/WindowObserver.hpp
	${CURDIR}/Window/win/impl_win32_Window.cpp
	${CURDIR}/Window/win/impl_win32_WindowObserver.cpp
	${CURDIR}/Window/win/RawInputParser.hpp
	${CURDIR}/Window/win/win32_ImplInputDevice.hpp
	${CURDIR}/Window/win/win_RawInputKeyboard.hpp
	${CURDIR}/BasicFunctor.hpp
	${CURDIR}/Config.hpp
	${CURDIR}/Deva.cpp
	${CURDIR}/Deva.hpp
	${CURDIR}/DevaLogger.cpp
	${CURDIR}/DevaLogger.hpp
	${CURDIR}/Exceptions.hpp
	${CURDIR}/Init.cpp
	${CURDIR}/Init.hpp
	${CURDIR}/Logger.cpp
	${CURDIR}/Logger.hpp
	${CURDIR}/Master.hpp
	${CURDIR}/NumberFormatter.cpp
	${CURDIR}/NumberFormatter.hpp
	${CURDIR}/Platform.hpp
)