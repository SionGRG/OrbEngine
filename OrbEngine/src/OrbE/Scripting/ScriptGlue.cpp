#include "OrbPCH.h"
#include "OrbE/Scripting/ScriptGlue.h"
#include "OrbE/Scripting/ScriptEngine.h"

#include "OrbE/Math/Math.h"
#include "OrbE/Core/KeyCodes.h"
#include "OrbE/Core/Input.h"

#include "OrbE/Scene/Scene.h"
#include "OrbE/Scene/Entity.h"

#include "mono/metadata/object.h"

namespace ORB {

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

	static void Entity_GetTranslation(UUID entityID, v3* outTranslation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		
		Entity entity = scene->GetEntityByUUID(entityID);
		*outTranslation  = entity.GetComponent<TransformComponent>().Translation;
	}

	static void Entity_SetTranslation(UUID entityID, v3* translation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();

		Entity entity = scene->GetEntityByUUID(entityID);
		entity.GetComponent<TransformComponent>().Translation = *translation;
	}

	static bool Input_IsKeyDown(KeyCode keycode)
	{
		return Input::IsKeyPressed(keycode);
	}

	void ScriptGlue::RegisterFunctions()
	{
		ORBE_ADD_INTERNAL_CALL(NativeLog);
		ORBE_ADD_INTERNAL_CALL(NativeLog_Vector);
		ORBE_ADD_INTERNAL_CALL(NativeLog_VectorDot);

		ORBE_ADD_INTERNAL_CALL(Entity_GetTranslation);
		ORBE_ADD_INTERNAL_CALL(Entity_SetTranslation);
		
		ORBE_ADD_INTERNAL_CALL(Input_IsKeyDown);

	}
}
