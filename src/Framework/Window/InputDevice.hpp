#ifndef DEVA_FRAMEWORK_WINDOW_INPUT_INPUT_DEVICE_HPP
#define DEVA_FRAMEWORK_WINDOW_INPUT_INPUT_DEVICE_HPP

#include "Config.hpp"

namespace DevaFramework
{

	class ImplInputDevice;

	struct InputDevice
	{
		typedef uint32_t DeviceHandle;

		enum DeviceType : int
		{
			KEYBOARD = 0
		};

		static InputDevice createDevice(const ImplInputDevice &impldev);

		const DeviceHandle handle;
		const DeviceType type;

		InputDevice() = delete;
		InputDevice(const InputDevice &idev) = delete;
		InputDevice& operator=(const InputDevice &&idev) = delete;

		DEVA_FRAMEWORK_API InputDevice(InputDevice &&idev);
		DEVA_FRAMEWORK_API InputDevice& operator=(InputDevice &&idev);
		DEVA_FRAMEWORK_API ~InputDevice();

	private:
		InputDevice(DeviceType type, DeviceHandle handle);
	};

	DEVA_FRAMEWORK_API bool operator==(const InputDevice &idev1, const InputDevice &idev2);
	DEVA_FRAMEWORK_API bool operator!=(const InputDevice &idev1, const InputDevice &idev2);
}

#endif //DEVA_FRAMEWORK_WINDOW_INPUT_INPUT_DEVICE_HPP