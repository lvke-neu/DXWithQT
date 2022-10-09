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

void readRelativeFile(const std::string& relativeFilePath, std::string& readContent)
{
	std::string absoluteFilePath;
	RelativePath2AbsolutePath(relativeFilePath, absoluteFilePath);
	readAbsoluteFile(absoluteFilePath, readContent);
}

void writeRelativeFile(const std::string& relativeFilePath, const std::string& writerContent)
{
	std::string absoluteFilePath;
	RelativePath2AbsolutePath(relativeFilePath, absoluteFilePath);
	writeabsoluteFile(absoluteFilePath, writerContent);
}

void readAbsoluteFile(const std::string& absoluteFilePath, std::string& readContent)
{
	std::ifstream ifs;
	ifs.open(absoluteFilePath, std::ios::in);

	ifs.seekg(0, std::ios_base::end);
	char* arr = new char[ifs.tellg()];
	ifs.seekg(0, std::ios_base::beg);

	while (ifs >> arr)
	{
		readContent += arr;
	}
	ifs.close();
}

void writeabsoluteFile(const std::string& absoluteFilePath, const std::string& writerContent)
{
	std::ofstream ofs;
	ofs.open(absoluteFilePath, std::ios::out | std::ios::trunc);
	ofs << writerContent;
	ofs.close();
}