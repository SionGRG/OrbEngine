#pragma once

#include "OrbE/Utils/BasicMaths.h"

namespace ORB {

		struct TransformComponent
		{
			m4 Transform{ 1.0f };

			TransformComponent() = default;
			TransformComponent(const TransformComponent&) = default;
			TransformComponent(const m4& transform)
				: Transform(transform) {}

			operator m4& () { return Transform; }
			operator const m4& () const { return Transform; }
		};

		struct MeshComponent 
		{
			bool data;
			MeshComponent() = default;
		};

		struct SpriteRendererComponent
		{
			v4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

			SpriteRendererComponent() = default;
			SpriteRendererComponent(const SpriteRendererComponent&) = default;
			SpriteRendererComponent(const v4& color)
				: Color(color) {}
		};
}