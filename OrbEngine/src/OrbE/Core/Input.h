#pragma once

#include "OrbE/Core/KeyCodes.h"
#include "OrbE/Core/MouseCodes.h"
#include "OrbE/Utils/BasicMaths.h"

namespace ORB {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode buttoncode);
		static v2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
		
	};
}