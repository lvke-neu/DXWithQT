#include "HttpRequestManager.h"
#include "../base/Utility.h"

namespace LkEngine
{

	size_t writeFunc(void *buffer, size_t size, size_t nmemb, FILE *user_p)
	{
		size_t return_size = fwrite(buffer, size, nmemb, user_p);

		return return_size;
	}

	CURLcode HttpRequestManager::download(const std::string& url, const std::string& relativeFilePath)
	{
		CURL *curl;
		FILE *fp;
		CURLcode res;
	std::string absolutefilePath;
	RelativePath2AbsolutePath(relativeFilePath, absolutefilePath);

	const char* file_name = absolutefilePath.c_str();
		res = curl_global_init(CURL_GLOBAL_ALL);
		if (CURLE_OK != res)
		{
			printf("init libcurl failed.");
			curl_global_cleanup();
			return (CURLcode)-1;
		}

		curl = curl_easy_init();
		if (curl) {
			fopen_s(&fp, file_name, "wb");


			res = curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			if (res != CURLE_OK)
			{
				fclose(fp);
				curl_easy_cleanup(curl);
				return (CURLcode)-1;
			}

			res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunc);
			if (res != CURLE_OK) {
				fclose(fp);
				curl_easy_cleanup(curl);
				return (CURLcode)-1;
			}

			res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
			if (res != CURLE_OK)
			{
				fclose(fp);
				curl_easy_cleanup(curl);
				return (CURLcode)-1;
			}

			res = curl_easy_perform(curl);

			fclose(fp);

			if (res != CURLE_OK) {

				return (CURLcode)-1;
			}


			curl_easy_cleanup(curl);


		}
		curl_global_cleanup();
		return (CURLcode)0;



	/*	std::string absolutefilePath;
		RelativePath2AbsolutePath(relativeFilePath, absolutefilePath);

		const char* file_name = absolutefilePath.c_str();


		FILE *fp{ nullptr };
		errno_t aa = fopen_s(&fp, file_name, "wb");

  
		CURL *curl = curl_easy_init();

		CURLcode res;
		if (curl)
		{

			struct curl_slist* header_list = NULL;
			header_list = curl_slist_append(header_list, "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64; Trident/7.0; rv:11.0) like Gecko");
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

			curl_easy_setopt(curl, CURLOPT_HEADER, 0);
 
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());


			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

			curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);

			curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);


			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &HttpRequestManager::writeFunc);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

			curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);


			curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 6);
			curl_easy_setopt(curl, CURLOPT_TIMEOUT, 6);

 
			res = curl_easy_perform(curl);
		}

		curl_easy_cleanup(curl);

		fclose(fp);

		return res;*/

	}

}
