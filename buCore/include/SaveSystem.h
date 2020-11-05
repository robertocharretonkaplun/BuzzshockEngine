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

		void 
		setString(String _key, String _val);

		void
		setInt(String _key, int _val);
		
		void
		setFloat(String _key, float _float);

		void
		setBool(String _key, bool _bool);

		void
		setIntVec4(String _key, int _val[4]);
		
		void
		setIntVec3(String _key, int _val[3]);

		void
		setFloatVec4(String _key, float _val[4]);
		
		void
		setFloatVec3(String _key, float _val[3]);

		String 
		getString(String _key);

		int
		getInt(String _key);
		
		float
		getFloat(String _key);

		bool
		getBool(String _key);

		buVector4I
		getIntVec4(String _key);
		
		buVector3I
		getIntVec3(String _key);
		
		buVector4F
		getFloatVec4(String _key);
		
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