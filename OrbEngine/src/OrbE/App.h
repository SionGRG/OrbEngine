#pragma once

#include "Core.h"

namespace ORB {

	class ORBE_API App
	{
	public:
		App();
		virtual ~App();

		void Run();
	};

	// To be defined in CLIENT
	App* CreateApplication();


}