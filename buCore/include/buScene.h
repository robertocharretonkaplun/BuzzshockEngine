#pragma once
#include <buPrerequisitesCore.h>
#include <buNode.h>

namespace buEngineSDK {
	class buScene	{
	public:
		buScene();
		~buScene();

	private:
		/**
		 * @brief 
		 */
		buNode* m_rootNode;
		/**
		 * @brief 
		 */
		uint32 m_numAnimations;
		/**
		 * @brief 
		 */
		buAnimation** m_animation;
	};
}
