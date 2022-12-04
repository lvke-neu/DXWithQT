#include "Utility.h"

void RelativePath2AbsolutePath(const std::string& relativePath, std::string& absolutePath)
{
	char exePath[MAX_PATH];
	GetModuleFileName(NULL, (LPSTR)exePath, sizeof(exePath));
	std::string exeDirectory(exePath);

	size_t n = exeDirectory.rfind("Editor");
	exeDirectory = exeDirectory.erase(n, exeDirectory.size() - n);

	absolutePath = exeDirectory + relativePath;
}

void AbsolutePath2RelativePath(const std::string& absolutePath, std::string& relativePath)
{
	char exePath[MAX_PATH];
	GetModuleFileName(NULL, (LPSTR)exePath, sizeof(exePath));
	std::string exeDirectory(exePath);

	size_t n = exeDirectory.rfind("Editor");
	exeDirectory = exeDirectory.erase(n, exeDirectory.size() - n);

	size_t pos = absolutePath.find("builtin");

	relativePath = absolutePath.substr(pos);
}

wchar_t *multiByteToWideChar(const std::string& pKey)
{
	const char* pCStrKey = pKey.c_str();

	int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, (int)strlen(pCStrKey) + 1, NULL, 0);
	wchar_t *pWCStrKey = new wchar_t[pSize];

	MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, (int)strlen(pCStrKey) + 1, pWCStrKey, pSize);
	return pWCStrKey;
}


char* wideCharToMultiByte(const wchar_t* pWCStrKey)
{

	int pSize = WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, (int)wcslen(pWCStrKey), NULL, 0, NULL, NULL);
	char* pCStrKey = new char[pSize + 1];

	WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, (int)wcslen(pWCStrKey), pCStrKey, pSize, NULL, NULL);
	pCStrKey[pSize] = '\0';
	return pCStrKey;

}