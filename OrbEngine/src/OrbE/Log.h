#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace ORB {

	class ORBE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core Log macros
#define ORBE_CORE_TRACE(...)	::ORB::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ORBE_CORE_INFO(...)		::ORB::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ORBE_CORE_WARN(...)		::ORB::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ORBE_CORE_ERROR(...)	::ORB::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ORBE_CORE_FATAL(...)	::ORB::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log macros
#define ORBE_TRACE(...)			::ORB::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ORBE_INFO(...)			::ORB::Log::GetClientLogger()->info(__VA_ARGS__)
#define ORBE_WARN(...)			::ORB::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ORBE_ERROR(...)			::ORB::Log::GetClientLogger()->error(__VA_ARGS__)
#define ORBE_FATAL(...)			::ORB::Log::GetClientLogger()->fatal(__VA_ARGS__)
