#pragma once

namespace std {
	template<class _CharT, class _Traits>
	class basic_ostream;
}

namespace Hazel {

	using uint8_t = unsigned char;

	enum class KeyAction : uint8_t
	{
		Release = 0,
		Press = 1,
		Repeat = 2
	};

	enum class KeyModifier : uint8_t 
	{
		Shift	 = BIT(0),
		Control  = BIT(1),
		Alt		 = BIT(2),
		Super	 = BIT(3),
		CapsLock = BIT(4),
		NumLock  = BIT(5),
		Ctrl = Control,
	};

	using uint16_t = unsigned short;
	enum class KeyCode : uint16_t
	{
		None = 0,
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	};

	template <class _CharT, class _Traits>
    inline std::basic_ostream<_CharT, _Traits>& operator<<(
        std::basic_ostream<_CharT, _Traits>& _Os, KeyCode key) {
        return _Os << (uint16_t)key;
    }
}

// From glfw3.h
#define HZ_KEY_SPACE           ::Hazel::KeyCode::Space
#define HZ_KEY_APOSTROPHE      ::Hazel::KeyCode::Apostrophe    /* ' */
#define HZ_KEY_COMMA           ::Hazel::KeyCode::Comma         /* , */
#define HZ_KEY_MINUS           ::Hazel::KeyCode::Minus         /* - */
#define HZ_KEY_PERIOD          ::Hazel::KeyCode::Period        /* . */
#define HZ_KEY_SLASH           ::Hazel::KeyCode::Slash         /* / */
#define HZ_KEY_0               ::Hazel::KeyCode::D0
#define HZ_KEY_1               ::Hazel::KeyCode::D1
#define HZ_KEY_2               ::Hazel::KeyCode::D2
#define HZ_KEY_3               ::Hazel::KeyCode::D3
#define HZ_KEY_4               ::Hazel::KeyCode::D4
#define HZ_KEY_5               ::Hazel::KeyCode::D5
#define HZ_KEY_6               ::Hazel::KeyCode::D6
#define HZ_KEY_7               ::Hazel::KeyCode::D7
#define HZ_KEY_8               ::Hazel::KeyCode::D8
#define HZ_KEY_9               ::Hazel::KeyCode::D9
#define HZ_KEY_SEMICOLON       ::Hazel::KeyCode::Semicolon     /* ; */
#define HZ_KEY_EQUAL           ::Hazel::KeyCode::Equal         /* = */
#define HZ_KEY_A               ::Hazel::KeyCode::A
#define HZ_KEY_B               ::Hazel::KeyCode::B
#define HZ_KEY_C               ::Hazel::KeyCode::C
#define HZ_KEY_D               ::Hazel::KeyCode::D
#define HZ_KEY_E               ::Hazel::KeyCode::E
#define HZ_KEY_F               ::Hazel::KeyCode::F
#define HZ_KEY_G               ::Hazel::KeyCode::G
#define HZ_KEY_H               ::Hazel::KeyCode::H
#define HZ_KEY_I               ::Hazel::KeyCode::I
#define HZ_KEY_J               ::Hazel::KeyCode::J
#define HZ_KEY_K               ::Hazel::KeyCode::K
#define HZ_KEY_L               ::Hazel::KeyCode::L
#define HZ_KEY_M               ::Hazel::KeyCode::M
#define HZ_KEY_N               ::Hazel::KeyCode::N
#define HZ_KEY_O               ::Hazel::KeyCode::O
#define HZ_KEY_P               ::Hazel::KeyCode::P
#define HZ_KEY_Q               ::Hazel::KeyCode::Q
#define HZ_KEY_R               ::Hazel::KeyCode::R
#define HZ_KEY_S               ::Hazel::KeyCode::S
#define HZ_KEY_T               ::Hazel::KeyCode::T
#define HZ_KEY_U               ::Hazel::KeyCode::U
#define HZ_KEY_V               ::Hazel::KeyCode::V
#define HZ_KEY_W               ::Hazel::KeyCode::W
#define HZ_KEY_X               ::Hazel::KeyCode::X
#define HZ_KEY_Y               ::Hazel::KeyCode::Y
#define HZ_KEY_Z               ::Hazel::KeyCode::Z
#define HZ_KEY_LEFT_BRACKET    ::Hazel::KeyCode::LeftBracket   /* [ */
#define HZ_KEY_BACKSLASH       ::Hazel::KeyCode::Backslash     /* \ */
#define HZ_KEY_RIGHT_BRACKET   ::Hazel::KeyCode::RightBracket  /* ] */
#define HZ_KEY_GRAVE_ACCENT    ::Hazel::KeyCode::GraveAccent   /* ` */
#define HZ_KEY_WORLD_1         ::Hazel::KeyCode::World1        /* non-US #1 */
#define HZ_KEY_WORLD_2         ::Hazel::KeyCode::World2        /* non-US #2 */

/* Function keys */
#define HZ_KEY_ESCAPE          ::Hazel::KeyCode::Escape
#define HZ_KEY_ENTER           ::Hazel::KeyCode::Enter
#define HZ_KEY_TAB             ::Hazel::KeyCode::Tab
#define HZ_KEY_BACKSPACE       ::Hazel::KeyCode::Backspace
#define HZ_KEY_INSERT          ::Hazel::KeyCode::Insert
#define HZ_KEY_DELETE          ::Hazel::KeyCode::Delete
#define HZ_KEY_RIGHT           ::Hazel::KeyCode::Right
#define HZ_KEY_LEFT            ::Hazel::KeyCode::Left
#define HZ_KEY_DOWN            ::Hazel::KeyCode::Down
#define HZ_KEY_UP              ::Hazel::KeyCode::Up
#define HZ_KEY_PAGE_UP         ::Hazel::KeyCode::PageUp
#define HZ_KEY_PAGE_DOWN       ::Hazel::KeyCode::PageDown
#define HZ_KEY_HOME            ::Hazel::KeyCode::Home
#define HZ_KEY_END             ::Hazel::KeyCode::End
#define HZ_KEY_CAPS_LOCK       ::Hazel::KeyCode::CapsLock
#define HZ_KEY_SCROLL_LOCK     ::Hazel::KeyCode::ScrollLock
#define HZ_KEY_NUM_LOCK        ::Hazel::KeyCode::NumLock
#define HZ_KEY_PRINT_SCREEN    ::Hazel::KeyCode::PrintScreen
#define HZ_KEY_PAUSE           ::Hazel::KeyCode::Pause
#define HZ_KEY_F1              ::Hazel::KeyCode::F1
#define HZ_KEY_F2              ::Hazel::KeyCode::F2
#define HZ_KEY_F3              ::Hazel::KeyCode::F3
#define HZ_KEY_F4              ::Hazel::KeyCode::F4
#define HZ_KEY_F5              ::Hazel::KeyCode::F5
#define HZ_KEY_F6              ::Hazel::KeyCode::F6
#define HZ_KEY_F7              ::Hazel::KeyCode::F7
#define HZ_KEY_F8              ::Hazel::KeyCode::F8
#define HZ_KEY_F9              ::Hazel::KeyCode::F9
#define HZ_KEY_F10             ::Hazel::KeyCode::F10
#define HZ_KEY_F11             ::Hazel::KeyCode::F11
#define HZ_KEY_F12             ::Hazel::KeyCode::F12
#define HZ_KEY_F13             ::Hazel::KeyCode::F13
#define HZ_KEY_F14             ::Hazel::KeyCode::F14
#define HZ_KEY_F15             ::Hazel::KeyCode::F15
#define HZ_KEY_F16             ::Hazel::KeyCode::F16
#define HZ_KEY_F17             ::Hazel::KeyCode::F17
#define HZ_KEY_F18             ::Hazel::KeyCode::F18
#define HZ_KEY_F19             ::Hazel::KeyCode::F19
#define HZ_KEY_F20             ::Hazel::KeyCode::F20
#define HZ_KEY_F21             ::Hazel::KeyCode::F21
#define HZ_KEY_F22             ::Hazel::KeyCode::F22
#define HZ_KEY_F23             ::Hazel::KeyCode::F23
#define HZ_KEY_F24             ::Hazel::KeyCode::F24
#define HZ_KEY_F25             ::Hazel::KeyCode::F25

/* Keypad */
#define HZ_KEY_KP_0            ::Hazel::KeyCode::KP0
#define HZ_KEY_KP_1            ::Hazel::KeyCode::KP1
#define HZ_KEY_KP_2            ::Hazel::KeyCode::KP2
#define HZ_KEY_KP_3            ::Hazel::KeyCode::KP3
#define HZ_KEY_KP_4            ::Hazel::KeyCode::KP4
#define HZ_KEY_KP_5            ::Hazel::KeyCode::KP5
#define HZ_KEY_KP_6            ::Hazel::KeyCode::KP6
#define HZ_KEY_KP_7            ::Hazel::KeyCode::KP7
#define HZ_KEY_KP_8            ::Hazel::KeyCode::KP8
#define HZ_KEY_KP_9            ::Hazel::KeyCode::KP9
#define HZ_KEY_KP_DECIMAL      ::Hazel::KeyCode::KPDecimal
#define HZ_KEY_KP_DIVIDE       ::Hazel::KeyCode::KPDivide
#define HZ_KEY_KP_MULTIPLY     ::Hazel::KeyCode::KPMultiply
#define HZ_KEY_KP_SUBTRACT     ::Hazel::KeyCode::KPSubtract
#define HZ_KEY_KP_ADD          ::Hazel::KeyCode::KPAdd
#define HZ_KEY_KP_ENTER        ::Hazel::KeyCode::KPEnter
#define HZ_KEY_KP_EQUAL        ::Hazel::KeyCode::KPEqual

#define HZ_KEY_LEFT_SHIFT      ::Hazel::KeyCode::LeftShift
#define HZ_KEY_LEFT_CONTROL    ::Hazel::KeyCode::LeftControl
#define HZ_KEY_LEFT_ALT        ::Hazel::KeyCode::LeftAlt
#define HZ_KEY_LEFT_SUPER      ::Hazel::KeyCode::LeftSuper
#define HZ_KEY_RIGHT_SHIFT     ::Hazel::KeyCode::RightShift
#define HZ_KEY_RIGHT_CONTROL   ::Hazel::KeyCode::RightControl
#define HZ_KEY_RIGHT_ALT       ::Hazel::KeyCode::RightAlt
#define HZ_KEY_RIGHT_SUPER     ::Hazel::KeyCode::RightSuper
#define HZ_KEY_MENU            ::Hazel::KeyCode::Menu
