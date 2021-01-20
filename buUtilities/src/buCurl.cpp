#include "buCurl.h"

namespace buEngineSDK {

  buCurl::buCurl(String _url) {
    m_curl = curl_easy_init();
    if (m_curl) {
      curl_easy_setopt(m_curl, CURLOPT_URL, "http://www.google.com");
      curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &m_readBuffer);
      m_res = curl_easy_perform(m_curl);
      curl_easy_cleanup(m_curl);

      std::cout << m_readBuffer << std::endl;
    }
  }

  buCurl::~buCurl() {

  }
}