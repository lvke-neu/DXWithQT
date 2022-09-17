#pragma once 

#include <d3d11.h>
#include <string>
#include <vector>
#include <d3dcompiler.h>
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"

//#define SAFERELEASE(p) { if ((p)) { delete (p); (p) = nullptr; } }
#define SAFERELEASE(p) { if ((p)) { (p)->Release(); (p) = nullptr; } }

HRESULT CreateShaderFromFile(const WCHAR* csoFileNameInOut, const WCHAR* hlslFileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** ppBlobOut);



HRESULT CreateWICTexture2DCubeFromFile(ID3D11Device * d3dDevice, ID3D11DeviceContext * d3dDeviceContext, const std::wstring & cubeMapFileName,
	ID3D11Texture2D ** textureArray,
	ID3D11ShaderResourceView ** textureCubeView,
	bool generateMips);

HRESULT CreateWICTexture2DCubeFromFile(
	ID3D11Device * d3dDevice,
	ID3D11DeviceContext * d3dDeviceContext,
	const std::vector<std::wstring>& cubeMapFileNames,
	ID3D11Texture2D ** textureArray,
	ID3D11ShaderResourceView ** textureCubeView,
	bool generateMips);




wchar_t* multiByteToWideChar(const std::string& pKey);

char* wideCharToMultiByte(const wchar_t* pWCStrKey);

void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c);