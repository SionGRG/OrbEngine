#include "OrbPCH.h"
#include "OrbE/Core/LayerStack.h"

namespace ORB {

	LayerStack::~LayerStack()
	{
		for (auto layer : m_Layers)
		{
			layer->OnDetach();
		}
	}

	void LayerStack::PushLayer(Ref<Layer> layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Ref<Layer> overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Ref<Layer> layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Ref<Layer> overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end() + m_LayerInsertIndex)
		{
			overlay->OnDetach();
			m_Layers.erase(it);
		}
	}
}