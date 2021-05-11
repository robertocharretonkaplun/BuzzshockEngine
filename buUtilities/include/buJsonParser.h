//Tencent is pleased to support the open source community by making RapidJSON available.
//
//Copyright(C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
//Licensed under the MIT License(the "License"); you may not use this file except
//in compliance with the License.You may obtain a copy of the License at
//
//http ://opensource.org/licenses/MIT
//
//Unless required by applicable law or agreed to in writing, software distributed
//under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
//CONDITIONS OF ANY KIND, either express or implied.See the License for the
//specific language governing permissionsand limitations under the License.
#pragma once
#include "buPrerequisitesUtil.h"
#include "rapidjson\document.h"
#include "rapidjson\writer.h"
#include "rapidjson\stringbuffer.h"
#include "buVector3F.h"

namespace buEngineSDK {
	class BU_UTILITY_EXPORT buJsonParser
	{
	public:
		/**
		 * @brief Default Constructor
		 */
		buJsonParser();

		/**
		 * @brief Default Destructor
		 */
		~buJsonParser() = default;
		
		/**
		 * @brief Parse json into DOM
		 */
		void
		parse();

		/**
	 	 * @brief Test method in charge of creating a Json string
	   */
		void
		writeIntoJson();

		/**
		 * @brief 
		 */
		void
		openDoc();

		void
		writePositions(buVector3F _vec);

		void
		createBuf();

	private:
		const char* m_json;
		rapidjson::Document m_document;
		rapidjson::Document::AllocatorType allocator;
		rapidjson::Value s;
	};
}
