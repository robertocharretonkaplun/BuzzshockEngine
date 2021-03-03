#pragma once
#include <buPrerequisitesCore.h>

namespace buEngineSDK {
	class buCoreGeometryShader {
	public:
		/**
		 * @brief Default Constructor
		 */
		buCoreGeometryShader() = default;
		/**
		 * @brief Destructor
		 */
		~buCoreGeometryShader() {};
		
		/**
		 * @brief Virtual method that initialize the object.
		 */
		virtual void
		init(WString _fileName) = 0;
	};
}
