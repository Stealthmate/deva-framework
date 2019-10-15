#ifndef DEVA_FRAMEWORK_WINDOW_WIN_IMPL_KEYCODE_MAPPING_INL
#define DEVA_FRAMEWORK_WINDOW_WIN_IMPL_KEYCODE_MAPPING_INL

#include "../Input.hpp"

#include <map>
#include <windows.h>

const UINT IMPL_VK_0 = 0x30;
const UINT IMPL_VK_1 = 0x31;
const UINT IMPL_VK_2 = 0x32;
const UINT IMPL_VK_3 = 0x33;
const UINT IMPL_VK_4 = 0x34;
const UINT IMPL_VK_5 = 0x35;
const UINT IMPL_VK_6 = 0x36;
const UINT IMPL_VK_7 = 0x37;
const UINT IMPL_VK_8 = 0x38;
const UINT IMPL_VK_9 = 0x39;

const UINT IMPL_VK_A = 0x41;
const UINT IMPL_VK_B = 0x42;
const UINT IMPL_VK_C = 0x43;
const UINT IMPL_VK_D = 0x44;
const UINT IMPL_VK_E = 0x45;
const UINT IMPL_VK_F = 0x46;
const UINT IMPL_VK_G = 0x47;
const UINT IMPL_VK_H = 0x48;
const UINT IMPL_VK_I = 0x49;
const UINT IMPL_VK_J = 0x4A;
const UINT IMPL_VK_K = 0x4B;
const UINT IMPL_VK_L = 0x4C;
const UINT IMPL_VK_M = 0x4D;
const UINT IMPL_VK_N = 0x4E;
const UINT IMPL_VK_O = 0x4F;
const UINT IMPL_VK_P = 0x50;
const UINT IMPL_VK_Q = 0x51;
const UINT IMPL_VK_R = 0x52;
const UINT IMPL_VK_S = 0x53;
const UINT IMPL_VK_T = 0x54;
const UINT IMPL_VK_U = 0x55;
const UINT IMPL_VK_V = 0x56;
const UINT IMPL_VK_W = 0x57;
const UINT IMPL_VK_X = 0x58;
const UINT IMPL_VK_Y = 0x59;
const UINT IMPL_VK_Z = 0x5A;

namespace DevaFramework
{

	typedef UINT WinKey;
	typedef DevaFramework::Key DevaKey;

	std::map<WinKey, DevaKey> SUPPORTED_KEYS =
	{
		{ VK_ESCAPE, DevaKey::KEY_ESCAPE },
		{ VK_SPACE, DevaKey::KEY_SPACE },
		{ VK_OEM_7, DevaKey::KEY_APOSTROPHE },
		{ VK_OEM_COMMA, DevaKey::KEY_COMMA },
		{ VK_OEM_MINUS, DevaKey::KEY_MINUS },
		{ VK_OEM_PERIOD, DevaKey::KEY_PERIOD },
		{ VK_OEM_5, DevaKey::KEY_SLASH },
		{ IMPL_VK_0, DevaKey::KEY_0 },
		{ IMPL_VK_1, DevaKey::KEY_1 },
		{ IMPL_VK_2, DevaKey::KEY_2 },
		{ IMPL_VK_3, DevaKey::KEY_3 },
		{ IMPL_VK_4, DevaKey::KEY_4 },
		{ IMPL_VK_5, DevaKey::KEY_5 },
		{ IMPL_VK_6, DevaKey::KEY_6 },
		{ IMPL_VK_7, DevaKey::KEY_7 },
		{ IMPL_VK_8, DevaKey::KEY_8 },
		{ IMPL_VK_9, DevaKey::KEY_9 },
		{ VK_OEM_PLUS, DevaKey::KEY_EQUAL },
		{ VK_OEM_1, DevaKey::KEY_SEMICOLON },
		{ IMPL_VK_A, DevaKey::KEY_A },
		{ IMPL_VK_B, DevaKey::KEY_B },
		{ IMPL_VK_C, DevaKey::KEY_C },
		{ IMPL_VK_D, DevaKey::KEY_D },
		{ IMPL_VK_E, DevaKey::KEY_E },
		{ IMPL_VK_F, DevaKey::KEY_F },
		{ IMPL_VK_G, DevaKey::KEY_G },
		{ IMPL_VK_H, DevaKey::KEY_H },
		{ IMPL_VK_I, DevaKey::KEY_I },
		{ IMPL_VK_J, DevaKey::KEY_J },
		{ IMPL_VK_K, DevaKey::KEY_K },
		{ IMPL_VK_L, DevaKey::KEY_L },
		{ IMPL_VK_M, DevaKey::KEY_M },
		{ IMPL_VK_N, DevaKey::KEY_N },
		{ IMPL_VK_O, DevaKey::KEY_O },
		{ IMPL_VK_P, DevaKey::KEY_P },
		{ IMPL_VK_Q, DevaKey::KEY_Q },
		{ IMPL_VK_R, DevaKey::KEY_R },
		{ IMPL_VK_S, DevaKey::KEY_S },
		{ IMPL_VK_T, DevaKey::KEY_T },
		{ IMPL_VK_U, DevaKey::KEY_U },
		{ IMPL_VK_V, DevaKey::KEY_V },
		{ IMPL_VK_W, DevaKey::KEY_W },
		{ IMPL_VK_X, DevaKey::KEY_X },
		{ IMPL_VK_Y, DevaKey::KEY_Y },
		{ IMPL_VK_Z, DevaKey::KEY_Z },

		/*
		KEY_LEFT_BRACKET = 91,
		KEY_BACKSLASH = 92,
		KEY_RIGHT_BRACKET = 93,
		KEY_GRAVE_ACCENT = 96,
		KEY_WORLD_1 = 161,
		KEY_WORLD_2 = 162,

		KEY_ESCAPE = 256,
		KEY_ENTER = 257,
		KEY_TAB = 258,
		KEY_BACKSPACE = 259,
		KEY_INSERT = 260,
		KEY_DELETE = 261,
		KEY_RIGHT = 262,
		KEY_LEFT = 263,
		KEY_DOWN = 264,
		KEY_UP = 265,
		KEY_PAGE_UP = 266,
		KEY_PAGE_DOWN = 267,
		KEY_HOME = 268,
		KEY_END = 269,
		KEY_CAPS_LOCK = 280,
		KEY_SCROLL_LOCK = 281,
		KEY_NUM_LOCK = 282,
		KEY_PRINT_SCREEN = 283,
		KEY_PAUSE = 284,
		KEY_F1 = 290,
		KEY_F2 = 291,
		KEY_F3 = 292,
		KEY_F4 = 293,
		KEY_F5 = 294,
		KEY_F6 = 295,
		KEY_F7 = 296,
		KEY_F8 = 297,
		KEY_F9 = 298,
		KEY_F10 = 299,
		KEY_F11 = 300,
		KEY_F12 = 301,
		KEY_F13 = 302,
		KEY_F14 = 303,
		KEY_F15 = 304,
		KEY_F16 = 305,
		KEY_F17 = 306,
		KEY_F18 = 307,
		KEY_F19 = 308,
		KEY_F20 = 309,
		KEY_F21 = 310,
		KEY_F22 = 311,
		KEY_F23 = 312,
		KEY_F24 = 313,
		KEY_F25 = 314,
		KEY_KP_0 = 320,
		KEY_KP_1 = 321,
		KEY_KP_2 = 322,
		KEY_KP_3 = 323,
		KEY_KP_4 = 324,
		KEY_KP_5 = 325,
		KEY_KP_6 = 326,
		KEY_KP_7 = 327,
		KEY_KP_8 = 328,
		KEY_KP_9 = 329,
		KEY_KP_DECIMAL = 330,
		KEY_KP_DIVIDE = 331,
		KEY_KP_MULTIPLY = 332,
		KEY_KP_SUBTRACT = 333,
		KEY_KP_ADD = 334,
		KEY_KP_ENTER = 335,
		KEY_KP_EQUAL = 336,
		KEY_LEFT_SHIFT = 340,
		KEY_LEFT_CONTROL = 341,
		KEY_LEFT_ALT = 342,
		KEY_LEFT_SUPER = 343,
		KEY_RIGHT_SHIFT = 344,
		KEY_RIGHT_CONTROL = 345,
		KEY_RIGHT_ALT = 346,
		KEY_RIGHT_SUPER = 347,
		KEY_MENU = 348,
		KEY_LAST = */
	};

	DevaKey getDevaKey(WinKey winkey)
	{
		auto i = SUPPORTED_KEYS.find(winkey);
		if (i == SUPPORTED_KEYS.end()) return Key::KEY_UNKNOWN;
		return i->second;
	}
}

#endif //DEVA_FRAMEWORK_WINDOW_WIN_IMPL_KEYCODE_MAPPING_INL