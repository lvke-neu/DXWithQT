namespace Twinkle
{

    #define SAFE_DELETE_SETNULL(p)              \
    {	                                        \
        if((p))                                   \
        {                                       \
		    delete (p);                           \
            (p)=nullptr;                          \
         }                                      \
    }

    #define SAFE_RELEASE(p)              \
    {	                                        \
        if((p))                                   \
        {                                       \
	        (p)->Release();                          \
        }\
    }

}

#include <string>
#include <windows.h>

void RelativePath2AbsolutePath(const std::string& relativePath, std::string& absolutePath);

void AbsolutePath2RelativePath(const std::string& absolutePath, std::string& relativePath);

wchar_t* multiByteToWideChar(const std::string& pKey);

char* wideCharToMultiByte(const wchar_t* pWCStrKey);