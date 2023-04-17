#pragma once

namespace ORB
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define ORBE_MOUSE_BUTTON_0      ::ORB::Mouse::Button0
#define ORBE_MOUSE_BUTTON_1      ::ORB::Mouse::Button1
#define ORBE_MOUSE_BUTTON_2      ::ORB::Mouse::Button2
#define ORBE_MOUSE_BUTTON_3      ::ORB::Mouse::Button3
#define ORBE_MOUSE_BUTTON_4      ::ORB::Mouse::Button4
#define ORBE_MOUSE_BUTTON_5      ::ORB::Mouse::Button5
#define ORBE_MOUSE_BUTTON_6      ::ORB::Mouse::Button6
#define ORBE_MOUSE_BUTTON_7      ::ORB::Mouse::Button7
#define ORBE_MOUSE_BUTTON_LAST   ::ORB::Mouse::ButtonLast
#define ORBE_MOUSE_BUTTON_LEFT   ::ORB::Mouse::ButtonLeft
#define ORBE_MOUSE_BUTTON_RIGHT  ::ORB::Mouse::ButtonRight
#define ORBE_MOUSE_BUTTON_MIDDLE ::ORB::Mouse::ButtonMiddle