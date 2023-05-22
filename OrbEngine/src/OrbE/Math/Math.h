#pragma once

#include <glm/glm.hpp>


namespace ORB {
//==============================================================================
// ORB Math and Math types definitions
//==============================================================================

	typedef glm::vec2 v2;
	typedef glm::vec3 v3;
	typedef glm::vec4 v4;

	typedef glm::mat3 m3;
	typedef glm::mat4 m4;

	namespace Math {

		bool DecomposeTransform(const m4& transform, v3& outTranslation, v3& outRotation, v3& outScale);

	}
}
