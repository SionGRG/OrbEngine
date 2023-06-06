#pragma once

#include "OrbE/Math/Math.h"

namespace ORB {

	class Camera
	{
	public:
		Camera() = default;
		Camera(const m4& projection)
			: m_Projection(projection) {}

		virtual ~Camera() = default;

		const m4& GetProjection() const { return m_Projection; }
		
	protected:
		m4 m_Projection = m4(1.0f);
	};
}
