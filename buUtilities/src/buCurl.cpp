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
  buCurl::post(String _url, char* data) {
    if (m_curl) {
      curl_easy_setopt(m_curl, CURLOPT_URL, _url);
      curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, data);

      /* if we don't provide POSTFIELDSIZE, libcurl will strlen() by
         itself */
      curl_easy_setopt(m_curl, CURLOPT_POSTFIELDSIZE, (long)strlen(data));

      /* Perform the request, res will get the return code */
      m_res = curl_easy_perform(m_curl);
      /* Check for errors */
      if (m_res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
          curl_easy_strerror(m_res));

      /* always cleanup */
      curl_easy_cleanup(m_curl);
    }
  }

  void buCurl::get(String _url)
  {
    curl_easy_setopt(m_curl, CURLOPT_URL, _url);
    /* example.com is redirected, so we tell libcurl to follow redirection */
    curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);

    /* Perform the request, res will get the return code */
    m_res = curl_easy_perform(m_curl);
    /* Check for errors */
    if (m_res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
        curl_easy_strerror(m_res));

    /* always cleanup */
    curl_easy_cleanup(m_curl);
  }
}