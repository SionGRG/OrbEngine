#pragma once

#include "OrbE/Core/Base.h"
#include "OrbE/Core/Log.h"

#ifdef ORBE_ENABLE_ASSERTS
	namespace ORB::Assert
	{
		// Returns the simple file name rather than full path
		constexpr const char* CurrentFileName(const char* path)
		{
			const char* file = path;
			while (*path)
			{
				if (*path == '/' || *path == '\\')
					file = ++path;
				else
					path++;
			}
			return file;
		}
	}

	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define ORBE_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { ORBE##type##ERROR(msg, __VA_ARGS__); ORBE_DEBUGBREAK(); } }
	#define ORBE_INTERNAL_ASSERT_WITH_MSG(type, check, ...) ORBE_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define ORBE_INTERNAL_ASSERT_NO_MSG(type, check) ORBE_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", ORBE_STRINGIFY_MACRO(check), ::ORB::Assert::CurrentFileName(__FILE__), __LINE__)

	#define ORBE_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define ORBE_INTERNAL_ASSERT_GET_MACRO(...) ORBE_EXPAND_MACRO( ORBE_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, ORBE_INTERNAL_ASSERT_WITH_MSG, ORBE_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define ORBE_ASSERT(...) ORBE_EXPAND_MACRO( ORBE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define ORBE_CORE_ASSERT(...) ORBE_EXPAND_MACRO( ORBE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define ORBE_ASSERT(...)
	#define ORBE_CORE_ASSERT(...)
#endif
