#pragma once

namespace ORB {

	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space               = 32,
		Apostrophe          = 39, /* ' */
		Comma               = 44, /* , */
		Minus               = 45, /* - */
		Period              = 46, /* . */
		Slash               = 47, /* / */

		D0                  = 48, /* 0 */
		D1                  = 49, /* 1 */
		D2                  = 50, /* 2 */
		D3                  = 51, /* 3 */
		D4                  = 52, /* 4 */
		D5                  = 53, /* 5 */
		D6                  = 54, /* 6 */
		D7                  = 55, /* 7 */
		D8                  = 56, /* 8 */
		D9                  = 57, /* 9 */

		Semicolon           = 59, /* ; */
		Equal               = 61, /* = */

		A                   = 65,
		B                   = 66,
		C                   = 67,
		D                   = 68,
		E                   = 69,
		F                   = 70,
		G                   = 71,
		H                   = 72,
		I                   = 73,
		J                   = 74,
		K                   = 75,
		L                   = 76,
		M                   = 77,
		N                   = 78,
		O                   = 79,
		P                   = 80,
		Q                   = 81,
		R                   = 82,
		S                   = 83,
		T                   = 84,
		U                   = 85,
		V                   = 86,
		W                   = 87,
		X                   = 88,
		Y                   = 89,
		Z                   = 90,

		LeftBracket         = 91,  /* [ */
		Backslash           = 92,  /* \ */
		RightBracket        = 93,  /* ] */
		GraveAccent         = 96,  /* ` */

		World1              = 161, /* non-US #1 */
		World2              = 162, /* non-US #2 */

		/* Function keys */
		Escape              = 256,
		Enter               = 257,
		Tab                 = 258,
		Backspace           = 259,
		Insert              = 260,
		Delete              = 261,
		Right               = 262,
		Left                = 263,
		Down                = 264,
		Up                  = 265,
		PageUp              = 266,
		PageDown            = 267,
		Home                = 268,
		End                 = 269,
		CapsLock            = 280,
		ScrollLock          = 281,
		NumLock             = 282,
		PrintScreen         = 283,
		Pause               = 284,
		F1                  = 290,
		F2                  = 291,
		F3                  = 292,
		F4                  = 293,
		F5                  = 294,
		F6                  = 295,
		F7                  = 296,
		F8                  = 297,
		F9                  = 298,
		F10                 = 299,
		F11                 = 300,
		F12                 = 301,
		F13                 = 302,
		F14                 = 303,
		F15                 = 304,
		F16                 = 305,
		F17                 = 306,
		F18                 = 307,
		F19                 = 308,
		F20                 = 309,
		F21                 = 310,
		F22                 = 311,
		F23                 = 312,
		F24                 = 313,
		F25                 = 314,

		/* Keypad */
		KP0                 = 320,
		KP1                 = 321,
		KP2                 = 322,
		KP3                 = 323,
		KP4                 = 324,
		KP5                 = 325,
		KP6                 = 326,
		KP7                 = 327,
		KP8                 = 328,
		KP9                 = 329,
		KPDecimal           = 330,
		KPDivide            = 331,
		KPMultiply          = 332,
		KPSubtract          = 333,
		KPAdd               = 334,
		KPEnter             = 335,
		KPEqual             = 336,

		/* Modifier keys */
		LeftShift           = 340,
		LeftControl         = 341,
		LeftAlt             = 342,
		LeftSuper           = 343,
		RightShift          = 344,
		RightControl        = 345,
		RightAlt            = 346,
		RightSuper          = 347,
		Menu                = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}
/* Printable keys */
#define ORBE_KEY_SPACE           ::ORB::Key::Space
#define ORBE_KEY_APOSTROPHE      ::ORB::Key::Apostrophe    /* ' */
#define ORBE_KEY_COMMA           ::ORB::Key::Comma         /* , */
#define ORBE_KEY_MINUS           ::ORB::Key::Minus         /* - */
#define ORBE_KEY_PERIOD          ::ORB::Key::Period        /* . */
#define ORBE_KEY_SLASH           ::ORB::Key::Slash         /* / */
#define ORBE_KEY_0               ::ORB::Key::D0
#define ORBE_KEY_1               ::ORB::Key::D1
#define ORBE_KEY_2               ::ORB::Key::D2
#define ORBE_KEY_3               ::ORB::Key::D3
#define ORBE_KEY_4               ::ORB::Key::D4
#define ORBE_KEY_5               ::ORB::Key::D5
#define ORBE_KEY_6               ::ORB::Key::D6
#define ORBE_KEY_7               ::ORB::Key::D7
#define ORBE_KEY_8               ::ORB::Key::D8
#define ORBE_KEY_9               ::ORB::Key::D9
#define ORBE_KEY_SEMICOLON       ::ORB::Key::Semicolon     /* ; */
#define ORBE_KEY_EQUAL           ::ORB::Key::Equal         /* = */
#define ORBE_KEY_A               ::ORB::Key::A
#define ORBE_KEY_B               ::ORB::Key::B
#define ORBE_KEY_C               ::ORB::Key::C
#define ORBE_KEY_D               ::ORB::Key::D
#define ORBE_KEY_E               ::ORB::Key::E
#define ORBE_KEY_F               ::ORB::Key::F
#define ORBE_KEY_G               ::ORB::Key::G
#define ORBE_KEY_H               ::ORB::Key::H
#define ORBE_KEY_I               ::ORB::Key::I
#define ORBE_KEY_J               ::ORB::Key::J
#define ORBE_KEY_K               ::ORB::Key::K
#define ORBE_KEY_L               ::ORB::Key::L
#define ORBE_KEY_M               ::ORB::Key::M
#define ORBE_KEY_N               ::ORB::Key::N
#define ORBE_KEY_O               ::ORB::Key::O
#define ORBE_KEY_P               ::ORB::Key::P
#define ORBE_KEY_Q               ::ORB::Key::Q
#define ORBE_KEY_R               ::ORB::Key::R
#define ORBE_KEY_S               ::ORB::Key::S
#define ORBE_KEY_T               ::ORB::Key::T
#define ORBE_KEY_U               ::ORB::Key::U
#define ORBE_KEY_V               ::ORB::Key::V
#define ORBE_KEY_W               ::ORB::Key::W
#define ORBE_KEY_X               ::ORB::Key::X
#define ORBE_KEY_Y               ::ORB::Key::Y
#define ORBE_KEY_Z               ::ORB::Key::Z
#define ORBE_KEY_LEFT_BRACKET    ::ORB::Key::LeftBracket   /* [ */
#define ORBE_KEY_BACKSLASH       ::ORB::Key::Backslash     /* \ */
#define ORBE_KEY_RIGHT_BRACKET   ::ORB::Key::RightBracket  /* ] */
#define ORBE_KEY_GRAVE_ACCENT    ::ORB::Key::GraveAccent   /* ` */
#define ORBE_KEY_WORLD_1         ::ORB::Key::World1        /* non-US #1 */
#define ORBE_KEY_WORLD_2         ::ORB::Key::World2        /* non-US #2 */

/* Function keys */
#define ORBE_KEY_ESCAPE          ::ORB::Key::Escape
#define ORBE_KEY_ENTER           ::ORB::Key::Enter
#define ORBE_KEY_TAB             ::ORB::Key::Tab
#define ORBE_KEY_BACKSPACE       ::ORB::Key::Backspace
#define ORBE_KEY_INSERT          ::ORB::Key::Insert
#define ORBE_KEY_DELETE          ::ORB::Key::Delete
#define ORBE_KEY_RIGHT           ::ORB::Key::Right
#define ORBE_KEY_LEFT            ::ORB::Key::Left
#define ORBE_KEY_DOWN            ::ORB::Key::Down
#define ORBE_KEY_UP              ::ORB::Key::Up
#define ORBE_KEY_PAGE_UP         ::ORB::Key::PageUp
#define ORBE_KEY_PAGE_DOWN       ::ORB::Key::PageDown
#define ORBE_KEY_HOME            ::ORB::Key::Home
#define ORBE_KEY_END             ::ORB::Key::End
#define ORBE_KEY_CAPS_LOCK       ::ORB::Key::CapsLock
#define ORBE_KEY_SCROLL_LOCK     ::ORB::Key::ScrollLock
#define ORBE_KEY_NUM_LOCK        ::ORB::Key::NumLock
#define ORBE_KEY_PRINT_SCREEN    ::ORB::Key::PrintScreen
#define ORBE_KEY_PAUSE           ::ORB::Key::Pause
#define ORBE_KEY_F1              ::ORB::Key::F1
#define ORBE_KEY_F2              ::ORB::Key::F2
#define ORBE_KEY_F3              ::ORB::Key::F3
#define ORBE_KEY_F4              ::ORB::Key::F4
#define ORBE_KEY_F5              ::ORB::Key::F5
#define ORBE_KEY_F6              ::ORB::Key::F6
#define ORBE_KEY_F7              ::ORB::Key::F7
#define ORBE_KEY_F8              ::ORB::Key::F8
#define ORBE_KEY_F9              ::ORB::Key::F9
#define ORBE_KEY_F10             ::ORB::Key::F10
#define ORBE_KEY_F11             ::ORB::Key::F11
#define ORBE_KEY_F12             ::ORB::Key::F12
#define ORBE_KEY_F13             ::ORB::Key::F13
#define ORBE_KEY_F14             ::ORB::Key::F14
#define ORBE_KEY_F15             ::ORB::Key::F15
#define ORBE_KEY_F16             ::ORB::Key::F16
#define ORBE_KEY_F17             ::ORB::Key::F17
#define ORBE_KEY_F18             ::ORB::Key::F18
#define ORBE_KEY_F19             ::ORB::Key::F19
#define ORBE_KEY_F20             ::ORB::Key::F20
#define ORBE_KEY_F21             ::ORB::Key::F21
#define ORBE_KEY_F22             ::ORB::Key::F22
#define ORBE_KEY_F23             ::ORB::Key::F23
#define ORBE_KEY_F24             ::ORB::Key::F24
#define ORBE_KEY_F25             ::ORB::Key::F25

/* Keypad */
#define ORBE_KEY_KP_0            ::ORB::Key::KP0
#define ORBE_KEY_KP_1            ::ORB::Key::KP1
#define ORBE_KEY_KP_2            ::ORB::Key::KP2
#define ORBE_KEY_KP_3            ::ORB::Key::KP3
#define ORBE_KEY_KP_4            ::ORB::Key::KP4
#define ORBE_KEY_KP_5            ::ORB::Key::KP5
#define ORBE_KEY_KP_6            ::ORB::Key::KP6
#define ORBE_KEY_KP_7            ::ORB::Key::KP7
#define ORBE_KEY_KP_8            ::ORB::Key::KP8
#define ORBE_KEY_KP_9            ::ORB::Key::KP9
#define ORBE_KEY_KP_DECIMAL      ::ORB::Key::KPDecimal
#define ORBE_KEY_KP_DIVIDE       ::ORB::Key::KPDivide
#define ORBE_KEY_KP_MULTIPLY     ::ORB::Key::KPMultiply
#define ORBE_KEY_KP_SUBTRACT     ::ORB::Key::KPSubtract
#define ORBE_KEY_KP_ADD          ::ORB::Key::KPAdd
#define ORBE_KEY_KP_ENTER        ::ORB::Key::KPEnter
#define ORBE_KEY_KP_EQUAL        ::ORB::Key::KPEqual

/* Modifier keys */
#define ORBE_KEY_LEFT_SHIFT      ::ORB::Key::LeftShift
#define ORBE_KEY_LEFT_CONTROL    ::ORB::Key::LeftControl
#define ORBE_KEY_LEFT_ALT        ::ORB::Key::LeftAlt
#define ORBE_KEY_LEFT_SUPER      ::ORB::Key::LeftSuper
#define ORBE_KEY_RIGHT_SHIFT     ::ORB::Key::RightShift
#define ORBE_KEY_RIGHT_CONTROL   ::ORB::Key::RightControl
#define ORBE_KEY_RIGHT_ALT       ::ORB::Key::RightAlt
#define ORBE_KEY_RIGHT_SUPER     ::ORB::Key::RightSuper
#define ORBE_KEY_MENU            ::ORB::Key::Menu
