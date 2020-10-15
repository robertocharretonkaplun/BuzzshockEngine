#pragma once
#include <buPrerequisitesCore.h>
#include <buMatrix4x4.h>
namespace buEngineSDK {
	class buCamera
	{
	public:
		buCamera();
		~buCamera();

		void
		update();

		void 
		render();

	private:
		String m_name;
		uint32 m_id;
		buMatrix4x4 m_view;
		buMatrix4x4 m_proyection;
	};
}