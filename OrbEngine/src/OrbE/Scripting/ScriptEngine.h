#pragma once


namespace ORB {

	class ScriptEngine
	{
	public:
		static void Init();
		static void Terminate();

	private:
		static void InitMono();
		static void TerminateMono();
	};
}
