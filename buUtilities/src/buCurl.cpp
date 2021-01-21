#include "buCurl.h"

namespace buEngineSDK {

  buCurl::buCurl(String _url) {
    m_curl = curl_easy_init();
    if (m_curl) {
      curl_easy_setopt(m_curl, CURLOPT_URL, _url);
      curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &m_readBuffer);
      m_res = curl_easy_perform(m_curl);
      curl_easy_cleanup(m_curl);

      std::cout << m_readBuffer << std::endl;
    }
  }

  buCurl::~buCurl() {

  }
  void
  buCurl::post() {
    if (m_curl) {
      curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, "name=charre&project=curl");

      /* Perform the request, res will get the return code */
      m_res = curl_easy_perform(m_curl);
      /* Check for errors */
      if (m_res != CURLE_OK) {
        std::cout << "curl_easy_perform() " << curl_easy_strerror(m_res) << std::endl;
      }
      curl_easy_cleanup(m_curl);
    }
  }
}