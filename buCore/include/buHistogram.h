#pragma once
#include "buPrerequisitesCore.h"
#include "buCommons.h"
#include "CL\cl.h"

namespace buEngineSDK {

	class BU_CORE_EXPORT buHistogram
	{
	public:
		buHistogram() = default;
		~buHistogram() = default;

		void 
		init();

		void 
		drawUI(String _windowName, String _description);
	private:
		Vector<int32> m_red;
		Vector<int32> m_green;
		Vector<int32> m_blue;
		Vector<int32> m_alpha;
		float arr[10] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
	};
}