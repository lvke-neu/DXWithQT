//***************************************************************************************
// Created By X_Jun(MKXJun)
//Modified By lvke
//***************************************************************************************

#pragma once

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <string>
#include <algorithm>
#include <locale>
#include "Geometry.h"
#include "Material.h"


class MtlReader;

class ObjReader
{
public:
	struct ObjPart
	{
		ObjPart() : material() {}
		~ObjPart() = default;

		Material material;							
		std::vector<VertexPosNormalTex> vertices;	
		std::vector<DWORD> indices16;
		std::vector<DWORD> indices32;				
		std::wstring texStrDiffuse;		
		

	};

	ObjReader()  {}
	~ObjReader() = default;


	bool Read(const wchar_t* mboFileName, const wchar_t* objFileName);
	
	bool ReadObj(const wchar_t* objFileName);
	bool ReadMbo(const wchar_t* mboFileName);
	bool WriteMbo(const wchar_t* mboFileName);
public:
	std::vector<ObjPart> objParts;

	XMVECTOR  vecMax = g_XMNegInfinity;
	XMVECTOR  vecMin = g_XMInfinity;
private:
	void AddVertex(const VertexPosNormalTex& vertex, DWORD vpi, DWORD vti, DWORD vni);
	std::unordered_map<std::wstring, DWORD> vertexCache;

};

class MtlReader
{
public:
	bool ReadMtl(const wchar_t* mtlFileName);


public:
	std::map<std::wstring, Material> materials;
	std::map<std::wstring, std::wstring> mapKdStrs;
};



