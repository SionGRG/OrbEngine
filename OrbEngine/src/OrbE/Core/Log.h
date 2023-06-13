#pragma once

#include "OrbE/Core/Base.h"

/* TODO: causing an error with the Editor camera, look for a fix 
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
*/

// This ignores all warnings raise inside the spdlog External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace ORB {

	class Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

/* TODO: Uncomment after finding the fix
template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
}
*/

// Core Log macros
#define ORBE_CORE_TRACE(...)        ::ORB::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ORBE_CORE_INFO(...)         ::ORB::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ORBE_CORE_WARN(...)         ::ORB::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ORBE_CORE_ERROR(...)        ::ORB::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ORBE_CORE_CRITICAL(...)     ::ORB::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client Log macros
#define ORBE_TRACE(...)             ::ORB::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ORBE_INFO(...)              ::ORB::Log::GetClientLogger()->info(__VA_ARGS__)
#define ORBE_WARN(...)              ::ORB::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ORBE_ERROR(...)             ::ORB::Log::GetClientLogger()->error(__VA_ARGS__)
#define ORBE_CRITICAL(...)          ::ORB::Log::GetClientLogger()->critical(__VA_ARGS__)
