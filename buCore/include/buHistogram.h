#pragma once
#include "buPrerequisitesCore.h"
#include "buCommons.h"
#include "CL\cl.h"

namespace buEngineSDK {

	class BU_CORE_EXPORT buHistogram
	{
	public:
		/**
		 * @brief Default constructor
		 */
		buHistogram() = default;

		/**
		 * @brief Default destructor
		 */
		~buHistogram() = default;

		/**
		 * @brief Method in charge of reading and img with compute
		 */
		void 
		init(String _fileName);

		/**
		 * @brief Method in change of drawing the histogram on imgui
		 */
		void 
		drawUI(String _windowName, String _description);

	private:
		Vector<int32> m_red;
		Vector<int32> m_green;
		Vector<int32> m_blue;
		Vector<int32> m_alpha;
		Vector<float> m_r;
		Vector<float> m_g;
		Vector<float> m_b;
		Vector<float> m_a;
		int32 maxValRed = 0;
		int32 maxValGreen = 0;
		int32 maxValBlue = 0;
		int32 maxValAlpha = 0;
		int outRed[256] = { 0 };
		int outGreen[256] = { 0 };
		int outBlue[256] = { 0 };
		int outAlpha[256] = { 0 };
		float arr[10] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
		String m_filename;
	};
}