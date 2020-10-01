#pragma once
#include <buVector3F.h>

namespace buEngineSDK {
	class buTransform
	{
	public:
		/**
		 * @brief Default Constructor
		 */
		buTransform() = default;
		/**
		 * @brief Destructor
		 */
		~buTransform() = default;
		
		/**
		 * @brief Method in charge of fill the position vector.
		 */
		void 
		setPosition(float _x, float _y, float _z) {
			m_position = { _x, _y, _z };
		}

		/**
		 * @brief Method in charge of fill the rotation vector.
		 */
		void 
	  setRotation(float _x, float _y, float _z) {
			m_rotation = { _x, _y, _z };
		}

		/**
		 * @brief Method in charge of fill the scale vector.
		 */
		void 
		setScale(float _x, float _y, float _z) {
			m_scale = { _x, _y, _z };
		}

		/**
		 * @brief Method in charge of getting the position vector.
		 */
		buVector3F & 
		getPosition() {
			return m_position;
		}

		/**
		 * @brief Method in charge of getting the rotation vector.
		 */
		buVector3F &
		getRotation() {
			return m_rotation;
		}

		/**
	 	 * @brief Method in charge of getting the scale vector.
	 	 */
		buVector3F &
	  getScale() {
			return m_scale;
		}

	private:
		/**
		 * @brief Position vector for the object. 
		 */
		buVector3F m_position = { 0.0f, 0.0f, 0.0f };
		/**
		 * @brief Rotation vector for the object.
		 */
		buVector3F m_rotation = { 0.0f, 0.0f, 0.0f };
		/**
		 * @brief Scale vector for the object.
		 */
		buVector3F m_scale = { 0.0f, 0.0f, 0.0f };
	};
}