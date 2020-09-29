#pragma once
#include <buPrerequisitesCore.h>

namespace buEngineSDK {
	struct NodeAnim {
		String m_nodeName;
		uint32 m_numPositionKeys;
	};

	class buAnimation
	{
	public:
		buAnimation();
		~buAnimation();

	private:
		/**
		 * @brief 
		 */
		String m_name;
		/**
		 * @brief 
		 */
		double m_duration;
		/**
		 * @brief 
		 */
		double m_ticksPerSecond;
		/**
		 * @brief 
		 */
		uint32 m_numChannels;
	};

}
