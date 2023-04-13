#include "OrbPCH.h"
#include "OrbE/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace ORB {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}