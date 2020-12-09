#pragma once
#include <buPrerequisitesCore.h>
#include <buMatrix4x4.h>
#include <buCoreBuffer.h>
#include <buCoreGraphicsAPI.h>
#include <buDegrees.h>
#include <buCommons.h>

namespace buEngineSDK {

	class BU_CORE_EXPORT buCamera
	{
	public:
		buCamera() = default;
		buCamera(String _name, uint32 _id);
		~buCamera() = default;

		void
		update(buVector3F _eye,
					 buVector3F _up, 
					 buVector3F _at,
					 float _angle,
					 float _aspectRatio, 
					 float _near, 
					 float _far);

		void 
		render();

	private:
		CBCamera m_cameraData;
		SPtr<buCoreBuffer> m_cameraBuffer;
		CameraType::E m_cameraType = CameraType::E::PROJECTION_TYPE;

		buVector3F m_cameraPos = buVector3F::Zero;
		buVector3F m_cameraTar = buVector3F::Zero;
		buVector3F m_cameraDir = buVector3F::Zero;

		buVector3F m_up = buVector3F::Zero;
		buVector3F m_cameraUp = buVector3F::Zero;
		buVector3F m_right = buVector3F::Zero;
		buVector3F m_cameraRight = buVector3F::Zero;
		buVector3F m_front = buVector3F::Zero;
		buVector3F m_cameraFront = buVector3F::Zero;
	public:
		String m_name = "";
		uint32 m_id = 0;
		bool m_isCameraActive = false;
		bool m_static = false;
	};
}