#include "OrbPCH.h"
#include "OrbE/Scene/Scene.h"

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
		// if (m_Registry.has<TransformComponent>(entity))
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

	entt::entity Scene::CreateEntity()
	{
		return m_Registry.create();
	}

	void Scene::OnUpdate(Timestep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawQuad(transform, sprite.Color);
		}

	}
}