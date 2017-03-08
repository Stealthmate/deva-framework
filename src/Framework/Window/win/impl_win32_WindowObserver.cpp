#include "../WindowObserver.hpp"

#ifdef DEVA_OS_WIN32

#include "impl_win32_EventInfo.hpp"
#include "impl_keycode_mapping.inl"

using namespace DevaFramework;


namespace
{
	typedef UINT VK;
	typedef UINT ScanCode;
	Key mapDevaKey(VK vkcode, ScanCode scanCode, UINT flags)
	{

		VK virtualKey = vkcode;

		if (virtualKey == 255)
		{
			// discard "fake keys" which are part of an escaped sequence
			return Key::KEY_UNKNOWN;
		}
		else if (virtualKey == VK_SHIFT)
		{
			// correct left-hand / right-hand SHIFT
			virtualKey = MapVirtualKey(scanCode, MAPVK_VSC_TO_VK_EX);
		}
		else if (virtualKey == VK_NUMLOCK)
		{
			// correct PAUSE/BREAK and NUM LOCK silliness, and set the extended bit
			scanCode = (MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC) | 0x100);
		}

		// e0 and e1 are escape sequences used for certain special keys, such as PRINT and PAUSE/BREAK.
		// see http://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html
		const bool isE0 = ((flags & RI_KEY_E0) != 0);
		const bool isE1 = ((flags & RI_KEY_E1) != 0);

		if (isE1)
		{
			// for escaped sequences, turn the virtual key into the correct scan code using MapVirtualKey.
			// however, MapVirtualKey is unable to map VK_PAUSE (this is a known bug), hence we map that by hand.
			if (virtualKey == VK_PAUSE)
				scanCode = 0x45;
			else
				scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);
		}

		switch (virtualKey)
		{
			// right-hand CONTROL and ALT have their e0 bit set
		case VK_CONTROL:
			if (isE0)
				virtualKey = VK_RCONTROL;
			else
				virtualKey = VK_LCONTROL;
			break;

		case VK_MENU:
			if (isE0)
				virtualKey = VK_RMENU;
			else
				virtualKey = VK_LMENU;
			break;

			// NUMPAD ENTER has its e0 bit set
		case VK_RETURN:
			if (isE0)
				virtualKey = VK_SEPARATOR;
			break;

			// the standard INSERT, DELETE, HOME, END, PRIOR and NEXT keys will always have their e0 bit set, but the
			// corresponding keys on the NUMPAD will not.
		case VK_INSERT:
			if (!isE0)
				virtualKey = VK_NUMPAD0;
			break;

		case VK_DELETE:
			if (!isE0)
				virtualKey = VK_DECIMAL;
			break;

		case VK_HOME:
			if (!isE0)
				virtualKey = VK_NUMPAD7;
			break;

		case VK_END:
			if (!isE0)
				virtualKey = VK_NUMPAD1;
			break;

		case VK_PRIOR:
			if (!isE0)
				virtualKey = VK_NUMPAD9;
			break;

		case VK_NEXT:
			if (!isE0)
				virtualKey = VK_NUMPAD3;
			break;

			// the standard arrow keys will always have their e0 bit set, but the
			// corresponding keys on the NUMPAD will not.
		case VK_LEFT:
			if (!isE0)
				virtualKey = VK_NUMPAD4;
			break;

		case VK_RIGHT:
			if (!isE0)
				virtualKey = VK_NUMPAD6;
			break;

		case VK_UP:
			if (!isE0)
				virtualKey = VK_NUMPAD8;
			break;

		case VK_DOWN:
			if (!isE0)
				virtualKey = VK_NUMPAD2;
			break;

			// NUMPAD 5 doesn't have its e0 bit set
		case VK_CLEAR:
			if (!isE0)
				virtualKey = VK_NUMPAD5;
			break;
		}

		return getDevaKey(virtualKey);
	}

	std::pair<MouseButton, bool> mapDevaMouseButton(USHORT mb_state)
	{
		if (mb_state & RI_MOUSE_BUTTON_1_DOWN) return{ MouseButton::MOUSE_BUTTON_1, true };
		else if (mb_state & RI_MOUSE_BUTTON_1_UP) return{ MouseButton::MOUSE_BUTTON_1, false };

		if (mb_state & RI_MOUSE_BUTTON_2_DOWN) return{ MouseButton::MOUSE_BUTTON_2, true };
		else if (mb_state & RI_MOUSE_BUTTON_2_UP) return{ MouseButton::MOUSE_BUTTON_2, false };

		if (mb_state & RI_MOUSE_BUTTON_3_DOWN) return{ MouseButton::MOUSE_BUTTON_3, true };
		else if (mb_state & RI_MOUSE_BUTTON_3_UP) return{ MouseButton::MOUSE_BUTTON_3, false };

		if (mb_state & RI_MOUSE_BUTTON_4_DOWN) return{ MouseButton::MOUSE_BUTTON_4, true };
		else if (mb_state & RI_MOUSE_BUTTON_4_UP) return{ MouseButton::MOUSE_BUTTON_4, false };

		if (mb_state & RI_MOUSE_BUTTON_5_DOWN) return{ MouseButton::MOUSE_BUTTON_5, true };
		else if (mb_state & RI_MOUSE_BUTTON_5_UP) return{ MouseButton::MOUSE_BUTTON_5, false };

		throw DevaException("What the fuck invalid mouse button?");
	}
}

void WindowObserver::fire(const WindowEventInfo &eventInfo)
{
	//TODO: Implement OS-specific input parsing


	RAWINPUT * input = eventInfo.inputData;
	switch (input->header.dwType)
	{
	case RIM_TYPEKEYBOARD:
	{
		RAWKEYBOARD rawKB = input->data.keyboard;
		const bool release = ((rawKB.Flags & RI_KEY_BREAK) != 0);
		DevaKey key = mapDevaKey(rawKB.VKey, rawKB.MakeCode, rawKB.Flags);
		for (auto &lstnr : this->windowListeners)
		{
			if (release) lstnr->onKeyUp(key);
			else lstnr->onKeyDown(key);
		}
	}break;
	case RIM_TYPEMOUSE:
	{
		USHORT flags = input->data.mouse.usFlags;
		USHORT button_state = input->data.mouse.usButtonFlags;
		SHORT wheel_data = reinterpret_cast<SHORT &>(input->data.mouse.usButtonData);
		ULONG raw_buttons = input->data.mouse.ulRawButtons;
		LONG motion_x = input->data.mouse.lLastX;
		LONG motion_y = input->data.mouse.lLastY;
		ULONG device_info = input->data.mouse.ulExtraInformation;

		for (auto &lstnr : this->windowListeners)
		{
			if(motion_x != 0 || motion_y != 0) lstnr->onMouseMove(static_cast<signed int>(motion_x), static_cast<signed int>(motion_y));

			if (button_state == RI_MOUSE_WHEEL)
			{
				lstnr->onMouseWheelMove(static_cast<signed int>(wheel_data));
			}

			else if (button_state != 0)
			{
				auto button_event = mapDevaMouseButton(button_state);
				if (button_event.second) lstnr->onMouseButtonDown(button_event.first);
				else lstnr->onMouseButtonUp(button_event.first);
			}

		}

	}break;
	}

}


#endif //DEVA_OS_WIN32