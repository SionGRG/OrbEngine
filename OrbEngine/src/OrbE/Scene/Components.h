#pragma once

#include "OrbE/Utils/BasicMaths.h"

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
