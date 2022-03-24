#pragma once
#include <buPrerequisitesCore.h>

namespace buEngineSDK {
	struct BSPRenderData {
		uint32* indices;
		uint32* vertices;
		uint32 ID;
	};

	class BSPNodeTree
	{
	public:
		BSPNodeTree();
		~BSPNodeTree();

		bool
		build();

		bool
		addPolygon();

		void 
		setAttriubuteCallback();

		void 
		draw();

		void 
		preReset();

		void 
		postReset();

	private:
		bool 
		buildTree();
		
		// polygon * selectBestSplitter

		void 
		drawRecurse();

		bool 
		Repair();

		void 
		RepairTJunctions();

		bool 
		PostBuild();

		void 
		CalculatePolyBounds();

		bool 
		BuildRenderData();

		bool 
		PopulateNodeData();

	private:
		
		bool m_bHardwareTnL; // Use hardware transformation and lighting?.
		//LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer; // Vertex buffer for storage of polygon data
		//LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer; // Dynamic index buffer used for rendering.
		uint32 m_nVertexCount; // Number of vertices stored in VB
		uint32 m_nFaceCount; // Number of faces we need to store in IB.
		//PolygonList m_Polygons; // LIST of Stored polygon data.
		//CALLBACK_FUNC m_AttribCallback; // Callback function pointer 
	};
}