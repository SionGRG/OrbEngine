#include "OrbPCH.h"
#include "OrbE/Scene/Scene.h"

#include "OrbE/Scene/Entity.h"
#include "OrbE/Scene/Components.h"
#include "OrbE/Renderer/Renderer2D.h"

namespace ORB {

	static void DoMath(const m4& transform)
	{
	}

	static void OnTransformConstruct(entt::registry& registtry, entt::entity entity)
	{
	}

	Scene::Scene()
	{
#if ENTT_EXAMPLE_CODE
		entt::entity entity = m_Registry.create();

		m_Registry.emplace<TransformComponent>(entity, m4(1.0f));


		m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>();

		//m_Registry.
		// if (m_Registry.all_of<TransformComponent>(entity))
		// 	TransformComponent& tranform = m_Registry.get<TransformComponent>(entity);


		auto view = m_Registry.view<TransformComponent>();
		for (auto entity1 : view)
			TransformComponent& transform = view.get<TransformComponent>(entity1);


		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
		for (auto entity2 : group)
		{
			auto[transform, mesh] = group.get<TransformComponent, MeshComponent>(entity2);

			// Renderer::Submit(mesh, transform);
		}
#endif // ENTT_EXAMPLE_CODE
	}
	
	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(std::string_view name)
	{
		Entity entity =  { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		// Render 2D
		Camera* mainCamera = nullptr;
		m4* cameraTransform = nullptr;
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
				
				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = &transform.Transform;
					break;
				}
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, *cameraTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawQuad(transform, sprite.Color);
			}

			Renderer2D::EndScene();
		}

	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		// Resize non-FixedAspectRatio cameras
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewportSize(width, height);
		}
	}
}