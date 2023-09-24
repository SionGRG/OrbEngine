#pragma once

#include <filesystem>

extern "C" {
	typedef struct _MonoClass MonoClass;
	typedef struct _MonoObject MonoObject;
	typedef struct _MonoMethod MonoMethod;
}

namespace ORB {

	class ScriptEngine
	{
	public:
		static void Init();
		static void Terminate();

		static void LoadAssembly(const std::filesystem::path& filepath);
	private:
		static void InitMono();
		static void TerminateMono();

		static MonoObject* InstanciateClass(MonoClass* monoClass);
		
		friend class ScriptClass;
	};

	class ScriptClass
	{
	public:
		ScriptClass() = default;

		ScriptClass(std::string_view classNamespace, std::string_view className);

		MonoObject* Instanciate();
		MonoMethod* GetMethod(std::string_view name, int parameterCount);
		MonoObject* InvokeMethod(MonoObject* instance, MonoMethod* method, void** params = nullptr);

	private:
		std::string m_ClassNamespace;
		std::string m_ClassName;

		MonoClass* m_MonoClass = nullptr;
	};
}
