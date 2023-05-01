#pragma once

#include "OrbE/Utils/BasicMaths.h"

namespace ORB {

	class Camera
	{
	public:
		Camera(const m4& projection)
			:m_Projection(projection) {}

		const m4& GetProjection() const { return m_Projection; }
		
	private:
		m4 m_Projection;
	};
}