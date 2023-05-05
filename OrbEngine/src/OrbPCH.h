#pragma once

#include "OrbE/Core/PlatformDetection.h"

#ifdef ORBE_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		// See https://github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
		#define NOMINMAX
	#endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <chrono>

// Data structures
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <tuple>

// De Orb Class
#include "OrbE/Core/Base.h"
#include "OrbE/Core/Log.h"
#include "OrbE/O_Debug/Instrumentor.h"

#ifdef ORBE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // ORBE_PLATFORM_WINDOWS

