#include "OrbPCH.h"
#include "OrbE/Scripting/ScriptGlue.h"

#include "OrbE/Math/Math.h"

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

	void ScriptGlue::RegisterFunctions()
	{
		ORBE_ADD_INTERNAL_CALL(NativeLog);
		ORBE_ADD_INTERNAL_CALL(NativeLog_Vector);
		ORBE_ADD_INTERNAL_CALL(NativeLog_VectorDot);

		// mono_add_internal_call("ORB.InternalCalls::NativeLog", NativeLog);
		// mono_add_internal_call("ORB.InternalCalls::NativeLog_Vector", NativeLog_Vector);
		// mono_add_internal_call("ORB.InternalCalls::NativeLog_VectorDot", NativeLog_VectorDot);
	}
}
