#pragma once

#include <string>
#include <optional>

namespace ORB {

	class FileDialogs
	{
	public:
		// These return enpty strings when cancelled
		static std::optional<std::string> OpenFile(const char* filter);
		static std::optional<std::string> SaveFile(const char* filter);
	};

}
