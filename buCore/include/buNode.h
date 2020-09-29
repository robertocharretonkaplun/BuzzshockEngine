#pragma once
#include <buPrerequisitesCore.h>
#include <buMatrix4x4.h>
namespace buEngineSDK{
	class buNode {
	public:
		buNode();
		~buNode();

	private:
		/**
		 * @brief Name of the node.
		 */
		String m_name;
		/**
		 * @brief Relative transformation to the parent node.
		 */
		buMatrix4x4 m_transformation;
		/**
		 * @brief Parent Node. NULL if this is the root node.
		 */
		buNode* m_parent;
		/**
		 * @brief The number of child nodes of this node.
		 */
		uint32 m_numChildren;
		/**
		 * @brief The childe nodes of this node. NULL if numChildrens is 0.
		 */
		buNode** m_children;
		/**
		 * @brief The number of meshes of this node.
		 */
		uint32 m_numMeshes;

		/**
		 * @brief The meshes of this node. Each entry is an index into the
		 * mesh list of the #aiScene.
		 */
		uint32* m_meshes;
	};
}
