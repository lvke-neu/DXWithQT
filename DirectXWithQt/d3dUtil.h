#pragma once 

#include <d3dcompiler.h>

#define SAFERELEASE(p) { if ((p)) { delete (p); (p) = nullptr; } }

HRESULT CreateShaderFromFile(
	const WCHAR* csoFileNameInOut,
	const WCHAR* hlslFileName,
	LPCSTR entryPoint,
	LPCSTR shaderModel,
	ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;


	ID3DBlob* errorBlob = nullptr;
	hr = D3DCompileFromFile(hlslFileName, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel,
		dwShaderFlags, 0, ppBlobOut, &errorBlob);
	if (FAILED(hr))
	{
		if (errorBlob != nullptr)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(errorBlob->GetBufferPointer()));
		}
		SAFERELEASE(errorBlob);
		return hr;
	}

	// 若指定了输出文件名，则将着色器二进制信息输出
	if (csoFileNameInOut)
	{
		return D3DWriteBlobToFile(*ppBlobOut, csoFileNameInOut, FALSE);
	}
	
	return hr;
}
