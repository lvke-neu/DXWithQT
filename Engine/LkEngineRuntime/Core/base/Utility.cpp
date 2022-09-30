#include "Utility.h"
#include <fstream>

void RelativePath2AbsolutePath(const std::string& relativePath, std::string& absolutePath)
{
	char exePath[MAX_PATH];
	GetModuleFileName(NULL, (LPSTR)exePath, sizeof(exePath));
	std::string exeDirectory(exePath);

	size_t n = exeDirectory.rfind("LkEngineEditor");
	exeDirectory = exeDirectory.erase(n, exeDirectory.size() - n);

	absolutePath = exeDirectory + relativePath;
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

void readFile(const std::string& relativeFilePath, std::string& readContent)
{
	std::string absoluteShaderPath;
	RelativePath2AbsolutePath(relativeFilePath, absoluteShaderPath);

	std::ifstream ifs;
	ifs.open(absoluteShaderPath, std::ios::in);

	char arr[4096] = { 0 };
	while (ifs >> arr)
	{
		readContent += arr;
	}
	ifs.close();
}

void writeFile(const std::string& relativeFilePath, const std::string& writerContent)
{
	std::string absoluteShaderPath;
	RelativePath2AbsolutePath(relativeFilePath, absoluteShaderPath);

	std::ofstream ofs;
	ofs.open(absoluteShaderPath, std::ios::out | std::ios::trunc);
	ofs << writerContent;
	ofs.close();
}
