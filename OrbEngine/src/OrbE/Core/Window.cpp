#include "OrbPCH.h"
#include "OrbE/Core/Window.h"

#ifdef ORBE_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace ORB {

	Scope<Window> Window::Create(const WindowProps& props)
	{
	#ifdef ORBE_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
	#else
		ORBE_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}

}