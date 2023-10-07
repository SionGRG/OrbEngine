#include "OrbPCH.h"
#include "OrbE/Scripting/ScriptGlue.h"
#include "OrbE/Scripting/ScriptEngine.h"

#include "OrbE/Math/Math.h"
#include "OrbE/Core/KeyCodes.h"
#include "OrbE/Core/Input.h"

#include "OrbE/Scene/Scene.h"
#include "OrbE/Scene/Entity.h"

#include "mono/metadata/object.h"
#include "mono/metadata/reflection.h"

#include "box2d/b2_body.h"

namespace ORB {

	static std::unordered_map<MonoType*, std::function<bool(Entity)>> s_EntityHasComponentFuncs;

#define ORBE_ADD_INTERNAL_CALL(Name) mono_add_internal_call("ORB.InternalCalls::" #Name, Name) 
	static void NativeLog(MonoString* string, int parameter)
	{
		char* cStr = mono_string_to_utf8(string);
		std::string str(cStr);
		mono_free(cStr);
		std::cout << str << ", " << parameter << std::endl;
	}

	static void NativeLog_Vector(v3* parameter, v3* outResult)
	{
		ORBE_CORE_WARN("Value: {0}", *parameter);

		*outResult = glm::normalize(*parameter);
	}

	static float NativeLog_VectorDot(v3* parameter)
	{
		ORBE_CORE_WARN("Value: {0}", *parameter);

		return glm::dot(*parameter, *parameter);
	}

	static bool Entity_HasComponent(UUID entityID, MonoReflectionType* componentType)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		ORBE_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		ORBE_CORE_ASSERT(entity);

		MonoType* managedType = mono_reflection_type_get_type(componentType);
		ORBE_CORE_ASSERT(s_EntityHasComponentFuncs.find(managedType) != s_EntityHasComponentFuncs.end())
		return s_EntityHasComponentFuncs.at(managedType)(entity);
	}

	static void TransformComponent_GetTranslation(UUID entityID, v3* outTranslation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		ORBE_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		ORBE_CORE_ASSERT(entity);
		
		*outTranslation  = entity.GetComponent<TransformComponent>().Translation;
	}

	static void TransformComponent_SetTranslation(UUID entityID, v3* translation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		ORBE_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		ORBE_CORE_ASSERT(entity);

		entity.GetComponent<TransformComponent>().Translation = *translation;
	}

	static void Rigidbody2DComponent_ApplyLinearImpulse(UUID entityID, v2* impulse, v2* point, bool wake)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		ORBE_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		ORBE_CORE_ASSERT(entity);

		auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
		b2Body* body = (b2Body*)rb2d.RuntimeBody;
		body->ApplyLinearImpulse(b2Vec2(impulse->x, impulse->y), b2Vec2(point->x, point->y), wake);
	}

	static void Rigidbody2DComponent_ApplyLinearImpulseToCenter(UUID entityID, v2* impulse, bool wake)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		ORBE_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		ORBE_CORE_ASSERT(entity);

		auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
		b2Body* body = (b2Body*)rb2d.RuntimeBody;
		body->ApplyLinearImpulseToCenter(b2Vec2(impulse->x, impulse->y), wake);
	}

	static bool Input_IsKeyDown(KeyCode keycode)
	{
		return Input::IsKeyPressed(keycode);
	}

	template<typename... Component>
	static void RegisterComponent()
	{
		([]()
		{
			std::string_view typeName = typeid(Component).name();
			size_t pos = typeName.find_last_of(':');
			std::string_view structName = typeName.substr(pos + 1);
			std::string managedTypename = fmt::format("ORB.{}", structName);

			MonoType* managedType = mono_reflection_type_from_name(managedTypename.data(), ScriptEngine::GetCoreAssemblyImage());
			if (!managedType)
			{
				ORBE_CORE_ERROR("Could not find component type {}", managedTypename);
				return;
			}
			s_EntityHasComponentFuncs[managedType] = [](Entity entity) { return entity.HasComponent<Component>(); };
		}(), ...);
	}

	template<typename... Component>
	static void RegisterComponent(ComponentGroup<Component...>)
	{
		RegisterComponent<Component...>();
	}

	void ScriptGlue::RegisterComponents()
	{
		RegisterComponent(AllComponents{});
		
	}

	void ScriptGlue::RegisterFunctions()
	{
		ORBE_ADD_INTERNAL_CALL(NativeLog);
		ORBE_ADD_INTERNAL_CALL(NativeLog_Vector);
		ORBE_ADD_INTERNAL_CALL(NativeLog_VectorDot);

		ORBE_ADD_INTERNAL_CALL(Entity_HasComponent);

		ORBE_ADD_INTERNAL_CALL(TransformComponent_GetTranslation);
		ORBE_ADD_INTERNAL_CALL(TransformComponent_SetTranslation);

		ORBE_ADD_INTERNAL_CALL(Rigidbody2DComponent_ApplyLinearImpulse);
		ORBE_ADD_INTERNAL_CALL(Rigidbody2DComponent_ApplyLinearImpulseToCenter);
		
		ORBE_ADD_INTERNAL_CALL(Input_IsKeyDown);

	}
}
