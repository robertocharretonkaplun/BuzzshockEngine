#include "buJsonParser.h"

namespace buEngineSDK {
	buJsonParser::buJsonParser()
	{
	}
	void buJsonParser::parse() {
    // 1. Parse a JSON string into DOM.
    m_json = "{\"project\":\"rapidjson\",\"stars\":10}";
    m_document.Parse(m_json);

    // 2. Modify it by DOM.
    rapidjson::Value& s = m_document["stars"];
    s.SetInt(s.GetInt() + 1);

    // 3. Stringify the DOM
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    m_document.Accept(writer);

    // Output {"project":"rapidjson","stars":11}
    std::cout << buffer.GetString() << std::endl;

  }

  void 
  buJsonParser::writeIntoJson() {
		// document is the root of a json message
		rapidjson::Document document;

		// define the document as an object rather than an array
		document.SetObject();

		// create a rapidjson array type with similar syntax to std::vector
		rapidjson::Value array(rapidjson::kArrayType);

		// must pass an allocator when the object may need to allocate memory
		rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

		// chain methods as rapidjson provides a fluent interface when modifying its objects
		array.PushBack("hello", allocator).PushBack("world", allocator);//"array":["hello","world"]

		document.AddMember("Name", "XYZ", allocator);
		document.AddMember("Rollnumer", 2, allocator);
		document.AddMember("array", array, allocator);

		// create a rapidjson object type
		rapidjson::Value object(rapidjson::kObjectType);
		object.AddMember("Math", "50", allocator);
		object.AddMember("Science", "70", allocator);
		object.AddMember("English", "50", allocator);
		object.AddMember("Social Science", "70", allocator);
		document.AddMember("Marks", object, allocator);
		//	fromScratch["object"]["hello"] = "Yourname";

		rapidjson::StringBuffer strbuf;
		rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
		document.Accept(writer);

		String BUFF = strbuf.GetString();
		std::cout << strbuf.GetString() << std::endl;
  }

	void buJsonParser::openDoc() {
		// define the document as an object rather than an array
		m_document.SetObject();

		// create a rapidjson array type with similar syntax to std::vector
		rapidjson::Value array(rapidjson::kArrayType);

		// must pass an allocator when the object may need to allocate memory
		allocator = m_document.GetAllocator();

		// chain methods as rapidjson provides a fluent interface when modifying its objects
		array.PushBack("hello", allocator).PushBack("world", allocator);//"array":["hello","world"]
	}

	void
	buJsonParser::writePositions(buVector3F _vec) {
		// create a rapidjson object type
		rapidjson::Value object(rapidjson::kObjectType);
		object.AddMember("X", _vec.x, allocator);
		object.AddMember("Y", _vec.y, allocator);
		object.AddMember("Z", _vec.z, allocator);
		m_document.AddMember("Positions", object, allocator);
		//	fromScratch["object"]["hello"] = "Yourname";
	}

	void
	buJsonParser::createBuf() {
		rapidjson::StringBuffer strbuf;
		rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
		m_document.Accept(writer);

		m_buffer = strbuf.GetString();
		std::cout << std::endl;
		std::cout << strbuf.GetString() << std::endl;
	}

}