#include "OrbPCH.h"
#include "OrbE/Core/Input.h"

#ifdef ORBE_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsInput.h"
#endif

namespace ORB {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
	#ifdef ORBE_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
	#else
		ORBE_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}

}