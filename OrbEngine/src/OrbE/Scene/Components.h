#pragma once

#include "OrbE/Utils/BasicMaths.h"
#include <glm/gtc/matrix_transform.hpp>

#include "OrbE/Scene/SceneCamera.h"
#include "OrbE/Scene/ScriptableEntity.h"

namespace ORB {

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(std::string_view tag)
			:Tag(tag) {}
	};

	struct TransformComponent
	{
		v3 Translation = { 0.0f, 0.0f, 0.0f };
		v3 Rotation = { 0.0f, 0.0f, 0.0f };
		v3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const v3& translation)
			: Translation(translation) {}

		m4 GetTransform() const
		{
			m4 rotation = glm::rotate(m4(1.0f), Rotation.x, {1, 0, 0})
				        * glm::rotate(m4(1.0f), Rotation.y, {0, 1, 0})
				        * glm::rotate(m4(1.0f), Rotation.z, {0, 0, 1});

			return glm::translate(m4(1.0f), Translation)
				* rotation
				* glm::scale(m4(1.0f), Scale);
		}
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

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true; // TODO: Think about moving to scene
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity*(*InstantiateScript)();
		void(*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };

		}
	};
}
