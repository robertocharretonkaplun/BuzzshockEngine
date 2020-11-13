#pragma once
#include <buPrerequisitesCore.h>
#include <buVector4F.h>
#include <buVector3F.h>
#include <buVector4i.h>
#include <buVector3i.h>
namespace buEngineSDK {
	class BU_CORE_EXPORT SaveSystem
	{
	public:
		SaveSystem() = default;
		~SaveSystem() = default;
		
		/**
		 * @brief Method in charge of cleaning the current file data.
		 */
		void
		cleanFileData();

		/**
		 * @brief Method that store the file name where all the data will be saved.
		 */
		void 
		setSaveFile(String _filename);

		/**
		 * @brief Method in charge of saving a string on the file.
		 */
		void 
		setString(String _key, String _val);

		/**
		 * @brief Method in charge of storing a int on the file.
		 */
		void
		setInt(String _key, int _val);
		
		/**
		 * @brief Mehtod in charge of storing a float on the file.
		 */
		void
		setFloat(String _key, float _float);

		/**
		 * @brief Method in charge of storing a bool on the file.
		 */
		void
		setBool(String _key, bool _bool);

		/**
		 * @brief Method in charge of storing a int array of 4 values in the file.
		 */
		void
		setIntVec4(String _key, int _val[4]);
		
		/**
		 * @brief Method in charge of storing a int array of 3 values in the file.
		 */
		void
		setIntVec3(String _key, int _val[3]);

		/**
		 * @brief Method in charge of storing a float array of 4 values in the file.
		 */
		void
		setFloatVec4(String _key, float _val[4]);
		
		/**
		 * @brief Method in charge of storing a float array of 3 values in the file.
		 */
		void
		setFloatVec3(String _key, float _val[3]);

		/**
		 * @brief Method in charge of getting a string from the [_key] value
		 */
		String 
		getString(String _key);

		/**
		 * @brief Method in charge of getting a int from the [_key] value
		 */
		int
		getInt(String _key);
		
		/**
		 * @brief Method in charge of getting a float from the [_key] value
		 */
		float
		getFloat(String _key);

		/**
		 * @brief Method in charge of getting a bool from the [_key] value
		 */
		bool
		getBool(String _key);

		/**
		 * @brief Method in charge of getting a 4 int vector from the [_key] value
		 */
		buVector4I
		getIntVec4(String _key);
		
		/**
		 * @brief Method in charge of getting a 3 int vector from the [_key] value
		 */
		buVector3I
		getIntVec3(String _key);
		
		/**
		 * @brief Method in charge of getting a 4 float vector from the [_key] value
		 */
		buVector4F
		getFloatVec4(String _key);
		
		/**
		 * @brief Method in charge of getting a 3 float vector from the [_key] value
		 */
		buVector3F
		getFloatVec3(String _key);
	private:

		Map<String, String> m_string;
		Map<String, float> m_float;
		Map<String, int> m_int;
		Map<String, bool> m_bool;

		Map<String, float[4]> m_vec4f;
		Map<String, float[3]> m_vec3f;
		
		Map<String, int[4]> m_vec4i;
		Map<String, int[3]> m_vec3i;
	};
}