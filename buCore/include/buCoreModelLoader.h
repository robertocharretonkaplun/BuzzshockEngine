#pragma once
#include <buPrerequisitesCore.h>
#include <buPrerequisitesUtil.h>
#include <buVector3F.h>
#include <buVector2F.h>

namespace buEngineSDK {

	class buCoreModelLoader	{
	public:
		buCoreModelLoader();
		~buCoreModelLoader();
		void
		loadMesh(String _filepath);
	private:
		buVector3F Pos;
		buVector2F Tex;
		uint32* Index = NULL;

		
	//	aiVector3D* VertexArray;
		Vector<uint32> IndexArray;
		//aiVector3D* textCoord;
		String TexName;
		Vector<String> textNames;
		uint32 numVertices = 0;
		uint32 numIndices = 0;
	};
}
