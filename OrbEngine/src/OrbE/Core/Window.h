#pragma once

#include <sstream>

#include "OrbE/Core/Base.h"
#include "OrbE/Events/Event.h"

namespace ORB {

	struct WindowProps
	{
		std::string Title;
		uint32_t Width, Height;

		WindowProps(std::string_view title = "De Orb Engine",
						uint32_t width = 1680,
						uint32_t height = 900)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Interface representing a desktop system based Window
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};

}
