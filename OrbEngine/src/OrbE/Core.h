#pragma once

#ifdef ORBE_PLATFORM_WINDOWS
	#ifdef ORBE_BUILD_DLL
		#define ORBE_API __declspec(dllexport)
	#else
		#define ORBE_API __declspec(dllimport)
	#endif 
#else
	#error Orb Engine Only support windows!
#endif // ORBE_PLATFORM_WINDOWS

#ifdef ORBE_DEBUG
	#define ORBE_ENABLE_ASSERTS
#endif // ORBE_DEBUG

#ifdef ORBE_ENABLE_ASSERTS
	#define ORBE_ASSERT(x, ...) { if(!(x)) { ORBE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define ORBE_CORE_ASSERT(x, ...) { if(!(x)) { ORBE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ORBE_ASSERT(x, ...)
	#define ORBE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define ORBE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)