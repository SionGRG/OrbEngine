#pragma once

#include <memory>

#include "OrbE/Core/PlatformDetection.h"

// DLL support
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
	#error De Orb Engine only supports Windows!
#endif // End of DLL support

#ifdef ORBE_DEBUG
	#if defined(ORBE_PLATFORM_WINDOWS)
		#define ORBE_DEBUGBREAK() __debugbreak()
	#elif defined(ORBE_PLATFORM_LINUX)
		#include <signal.h>
		#define ORBE_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define ORBE_ENABLE_ASSERTS
#else
	#define ORBE_DEBUGBREAK()
#endif // ORBE_DEBUG

// TODO: Make this macro able to take in no arguments except condition
#ifdef ORBE_ENABLE_ASSERTS
	#define ORBE_ASSERT(x, ...) { if(!(x)) { ORBE_ERROR("Assertion Failed: {0}", __VA_ARGS__); ORBE_DEBUGBREAK(); } }
	#define ORBE_CORE_ASSERT(x, ...) { if(!(x)) { ORBE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); ORBE_DEBUGBREAK(); } }
#else
	#define ORBE_ASSERT(x, ...)
	#define ORBE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define ORBE_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace ORB {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}