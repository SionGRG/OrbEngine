#pragma once

#ifdef ORBE_PLATFORM_WINDOWS
	#ifdef ORBE_BUILD_DLL
		#define ORBE_API __declspec(dllexport)
	#else
		#define ORBE_API __declspec(dllexport)
	#endif 
#else
	#error Orb Engine Only support windows!
#endif // ORBE_PLATFORM_WINDOWS

#define BIT(x) (1 << x)