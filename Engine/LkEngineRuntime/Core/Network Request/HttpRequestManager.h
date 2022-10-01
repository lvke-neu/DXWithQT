/***************************************************************************************
Author: lvke
Date:2022/9/30 21:34
Description:
package http request
****************************************************************************************/

#pragma once
#include "../base/SingletonInterface.h"
#include <curl/curl.h>
#include <string>

namespace LkEngine 
{
	class HttpRequestManager : public ISingleton<HttpRequestManager>
	{
	public:
		CURLcode download(const std::string& url, const std::string& relativeFilePath);
	private:
		//size_t writeFunc(void *buffer, size_t size, size_t nmemb, FILE* user_p);
	};
}
