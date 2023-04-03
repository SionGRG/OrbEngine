#include "OrbPCH.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace ORB {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}