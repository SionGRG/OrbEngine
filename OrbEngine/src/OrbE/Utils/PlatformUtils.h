#pragma once

#include <string>

namespace ORB {

	class FileDialogs
	{
	public:
		// These return enpty strings when cancelled
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};

	class Time
	{
	public:
		static float GetTime();
	};
}
