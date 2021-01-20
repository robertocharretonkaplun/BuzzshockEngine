#pragma once
#include "buPrerequisitesUtil.h"
#include "curl\curl.h"
namespace buEngineSDK {
	class buCurl
	{
	public:
		buCurl() = default;
		buCurl(String _url);
		~buCurl();
		static size_t 
	  WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)	{
			((std::string*)userp)->append((char*)contents, size * nmemb);
			return size * nmemb;
		}

	private:
		CURL* m_curl;
		CURLcode m_res;
		String m_readBuffer;
		String m_url;
	};
}