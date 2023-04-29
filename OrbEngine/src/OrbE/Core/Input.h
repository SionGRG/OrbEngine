#pragma once

#include "OrbE/Core/Base.h"
#include "OrbE/Core/KeyCodes.h"
#include "OrbE/Core/MouseCodes.h"

namespace ORB {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode buttoncode);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
		
	};
}