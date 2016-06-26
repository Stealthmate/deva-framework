#include "../WindowObserver.hpp"
#include "impl_win32_EventInfo.hpp"
#include "impl_keycode_mapping.inl"


using namespace DevaFramework;

#ifdef DEVA_OS_WIN32


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
				virtualKey =  VK_NUMPAD0;
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
}

#include "../../DevaLogger.hpp"

void WindowObserver::fire_InputEvent(const InputEventInfo &eventInfo)
{
	//TODO: Implement OS-specific input parsing


	RAWINPUT * input = eventInfo.inputData;
	switch (input->header.dwType)
	{
	case RIM_TYPEKEYBOARD:
	{
		RAWKEYBOARD rawKB = input->data.keyboard;

		UINT virtualKey = rawKB.VKey;
		UINT scanCode = rawKB.MakeCode;
		UINT flags = rawKB.Flags;

		// a key can either produce a "make" or "break" scancode. this is used to differentiate between down-presses and releases
		// see http://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html
		const bool release = ((flags & RI_KEY_BREAK) != 0);

		// getting a human-readable string
		/*const bool isE0 = ((flags & RI_KEY_E0) != 0);
		UINT key = (scanCode << 16) | (isE0 << 24);
		char buffer[512] = {};
		GetKeyNameText((LONG)key, buffer, 512);*/

		Key key = mapDevaKey(virtualKey, scanCode, flags);
		DevaLogger::log << "Pressed " << key << "\n";
		for (auto &lstnr : this->inputListeners)
		{
			if (release) lstnr->onKeyUp(key);
			else lstnr->onKeyDown(key);
		}
	}
	}

}


#endif //DEVA_OS_WIN32