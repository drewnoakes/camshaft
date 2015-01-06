#include "camshaft/http.hh"

#include <curl/curl.h>
#include <sstream>
#include <stdexcept>

using namespace std;

size_t callback(void* contents, size_t size, size_t nmemb, void* user)
{
  auto chunk = reinterpret_cast<char*>(contents);
  auto buffer = reinterpret_cast<vector<char>*>(user);

  size_t priorSize = buffer->size();
  size_t sizeIncrease = size * nmemb;

  buffer->resize(priorSize + sizeIncrease);
  std::copy(chunk, chunk + sizeIncrease, buffer->data() + priorSize);

  return sizeIncrease;
}

vector<char> download(string url, long* responseCode)
{
  vector<char> data;

  curl_global_init(CURL_GLOBAL_ALL);
  CURL* handle = curl_easy_init();
  curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, callback);
  curl_easy_setopt(handle, CURLOPT_WRITEDATA, &data);
  curl_easy_setopt(handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
  CURLcode result = curl_easy_perform(handle);
  if (responseCode != nullptr)
    curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, responseCode);
  curl_easy_cleanup(handle);
  curl_global_cleanup();

  if (result != CURLE_OK)
  {
    stringstream err;
    err << "Error downloading from URL \"" << url << "\": " << curl_easy_strerror(result);
    throw runtime_error(err.str());
  }

  return std::move(data);
}
