#pragma once
#include <buPrerequisitesCore.h>
#include <buMatrix4x4.h>
namespace buEngineSDK {
	class buCamera
	{
	public:
		buCamera(String _name, uint32 _id);
		~buCamera() = default;

		void
		update(float posX[3], float posY[3], float posZ[3]);

		void 
		render();

	private:
		String m_name;
		uint32 m_id;
		buMatrix4x4 m_view;
		buMatrix4x4 m_proyection;

		buVector3F Eye;
		buVector3F Up;
		buVector3F At;

		float Near;
		float Far;
		float Angle;
	};
}