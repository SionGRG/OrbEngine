#pragma once

#include <memory>

#ifdef ORBE_PLATFORM_WINDOWS
	#if ORBE_DYNAMIC_LINK
		#ifdef ORBE_BUILD_DLL
			#define ORBE_API __declspec(dllexport)
		#else
			#define ORBE_API __declspec(dllimport)
		#endif
	#else
		#define ORBE_API
	#endif //ORBE_DYNAMIC_LINK
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

namespace ORB {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}