#pragma once
#include "buMatrix4x4.h"
namespace buEngineSDK {
	struct CBCamera
	{
		buMatrix4x4 view;
		buMatrix4x4 projection;

	};

	struct CBChangesEveryFrame {
		buMatrix4x4 mWorld = buMatrix4x4::ZERO;
		buVector4F viewDirection;
		buVector4F LightPos;
		buVector4F LightColor;
		buVector4F surfColor;
    buVector4F constants;
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