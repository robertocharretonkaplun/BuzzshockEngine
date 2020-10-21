#pragma once
#include "buMatrix4x4.h"
namespace buEngineSDK {
	struct CBCamera
	{
		buMatrix4x4 view;
		buMatrix4x4 projection;

	};

}

namespace CameraType {
	enum E {
		PROJECTION_TYPE,
		ORTHOGRAPHIC_TYPE
	};
}

namespace GameObjectType {
	enum E {
		DEFAULT_TYPE,
		MESH_TYPE
	};
}