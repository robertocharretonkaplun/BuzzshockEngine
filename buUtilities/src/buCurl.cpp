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
  buCurl::post(String _url, String data) {
    m_curl = curl_easy_init();
    if (m_curl) {
      curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1);
      curl_easy_setopt(m_curl, CURLOPT_URL, _url.c_str());

      struct curl_slist* headers = nullptr;
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");

      curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "POST");
      // curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, "{ \"text\" : \"hello world\" , \"timestamp\": \"2021-05-07 T10:43:30+06:00\" }");
  //    curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, "{ \"x\" : \"1\" , \"y\": \"2\", \"z\": \"3\" }");
      curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, data.c_str());

      /* Perform the request, res will get the return code */
      m_res = curl_easy_perform(m_curl);
      /* Check for errors */
      if (m_res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
        curl_easy_strerror(m_res));
      }

      /* always cleanup */
      curl_easy_cleanup(m_curl);
      curl_global_cleanup();
    }
  }

  void buCurl::get(String _url)
  {
    /*m_curl = curl_easy_init();
    if (m_curl) {
      curl_easy_setopt(m_curl, CURLOPT_URL, _url.c_str());
      curl_easy_setopt(m_curl, CURLOPT_NOPROGRESS, 1L);
      curl_easy_setopt(m_curl, CURLOPT_MAXREDIRS, 50L);
      curl_easy_setopt(m_curl, CURLOPT_TCP_KEEPALIVE, 1L);

      String response_string;
      String header_string;
      curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION,  WriteCallback);
      curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, response_string.data());
      curl_easy_setopt(m_curl, CURLOPT_HEADERDATA, &header_string);

      curl_easy_perform(m_curl);
      std::cout << response_string;
      curl_easy_cleanup(m_curl);
      curl_global_cleanup();
      m_curl = NULL;
    }*/

    m_curl = curl_easy_init();
    if (m_curl) {
      curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1);
      curl_easy_setopt(m_curl, CURLOPT_URL, _url.c_str());
      
      struct curl_slist* headers = nullptr;
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");

      curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "GET");
      curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, "{\"query\": {\"query_string\": {\"query\": \"*\"}}}");

      /* Perform the request, res will get the return code */
      m_res = curl_easy_perform(m_curl);
      /* Check for errors */
      if (m_res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
          curl_easy_strerror(m_res));
    }

    String response_string;
    String header_string;
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, response_string.data());
    curl_easy_setopt(m_curl, CURLOPT_HEADERDATA, &header_string);

    std::cout << response_string;
    curl_easy_cleanup(m_curl);
    curl_global_cleanup();
    m_curl = NULL;
  }
}