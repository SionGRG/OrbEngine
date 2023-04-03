#include "OrbPCH.h"
#include "Renderer.h"

namespace ORB {

	void Renderer::BeginScene()
	{
	}
	
	void Renderer::EndScene()
	{
	}

	// Submit meshes/Geomentry
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}