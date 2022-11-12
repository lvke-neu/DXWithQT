#include "ComponentInterface.h"
#include "../../../Asset/AssetManager.h"

namespace LkEngine
{
	IComponent::IComponent(void** parameter)
	{
		m_pd3dDevice = (ID3D11Device*)parameter[0];
		m_pd3dImmediateContext = (ID3D11DeviceContext*)parameter[1];

		D3D11_BUFFER_DESC cbd;
		ZeroMemory(&cbd, sizeof(cbd));
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.ByteWidth = sizeof(WorldMatrix);
		m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pWorldMatrixCB.GetAddressOf());


		cbd.ByteWidth = sizeof(Material);
		m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pMaterialCB.GetAddressOf());


		cbd.ByteWidth = sizeof(UseTexOrColor);
		m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pUseColorCB.GetAddressOf());

		//generate uui
		GUID guid;
		CoCreateGuid(&guid);
		const UINT bufferLength = 256;
		char* guidStr = new char[bufferLength];
		_snprintf_s(guidStr, bufferLength, bufferLength - 1,
			"%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1], guid.Data4[2],
			guid.Data4[3], guid.Data4[4], guid.Data4[5],
			guid.Data4[6], guid.Data4[7]);
		m_uuid = guidStr;

		bind_Set_Func();

		setMaterial(COMMON_MAT);
	}

	IComponent::IComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext) :
		m_pd3dDevice(pd3dDevice), m_pd3dImmediateContext(pd3dImmediateContext)
	{
		D3D11_BUFFER_DESC cbd;
		ZeroMemory(&cbd, sizeof(cbd));
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.ByteWidth = sizeof(WorldMatrix);
		m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pWorldMatrixCB.GetAddressOf());


		cbd.ByteWidth = sizeof(Material);
		m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pMaterialCB.GetAddressOf());


		cbd.ByteWidth = sizeof(UseTexOrColor);
		m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pUseColorCB.GetAddressOf());

		//generate uui
		GUID guid;
		CoCreateGuid(&guid);
		const UINT bufferLength = 256;
		char* guidStr = new char[bufferLength];
		_snprintf_s(guidStr, bufferLength, bufferLength - 1,
			"%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1], guid.Data4[2],
			guid.Data4[3], guid.Data4[4], guid.Data4[5],
			guid.Data4[6], guid.Data4[7]);
		m_uuid = guidStr;


		bind_Set_Func();

		setMaterial(COMMON_MAT);
	}

	void IComponent::bind_Set_Func()
	{
		m_functions["set_VsShader"] = std::bind(&IComponent::set_VsShader, this, std::placeholders::_1);
		m_functions["set_GsShader"] = std::bind(&IComponent::set_GsShader, this, std::placeholders::_1);
		m_functions["set_PsShader"] = std::bind(&IComponent::set_PsShader, this, std::placeholders::_1);
		m_functions["set_Texture"] = std::bind(&IComponent::set_Texture, this, std::placeholders::_1);
		m_functions["set_Material"] = std::bind(&IComponent::set_Material, this, std::placeholders::_1);
		m_functions["set_Transform"] = std::bind(&IComponent::set_Transform, this, std::placeholders::_1);
	}

	void IComponent::set_VsShader(const rapidjson::Value& funcParameter)
	{
		if (funcParameter.HasMember("vsShader"))
		{
			setVsShader(funcParameter["vsShader"].GetString());
		}
	}
	
	void IComponent::set_GsShader(const rapidjson::Value& funcParameter)
	{
		if (funcParameter.HasMember("gsShader"))
		{
			setGsShader(funcParameter["gsShader"].GetString());
		}
	}

	void IComponent::set_PsShader(const rapidjson::Value& funcParameter)
	{
		if (funcParameter.HasMember("psShader"))
		{
			setPsShader(funcParameter["psShader"].GetString());
		}
	}

	void IComponent::set_Texture(const rapidjson::Value& funcParameter )
	{
		if (funcParameter.HasMember("texture"))
		{
			setTexture(funcParameter["texture"].GetString());
		}
	}

	void IComponent::set_Material(const rapidjson::Value& funcParameter)
	{
		if (funcParameter.HasMember("material"))
		{
			Material material;
			if (funcParameter["material"].HasMember("ambient"))
			{

				material.ambient = XMFLOAT4(std::stof(funcParameter["material"]["ambient"][0].GetString()),
					std::stof(funcParameter["material"]["ambient"][1].GetString()),
					std::stof(funcParameter["material"]["ambient"][2].GetString()),
					std::stof(funcParameter["material"]["ambient"][3].GetString()));
			}
			if (funcParameter["material"].HasMember("diffuse"))
			{
				material.diffuse = XMFLOAT4(std::stof(funcParameter["material"]["diffuse"][0].GetString()),
					std::stof(funcParameter["material"]["diffuse"][1].GetString()),
					std::stof(funcParameter["material"]["diffuse"][2].GetString()),
					std::stof(funcParameter["material"]["diffuse"][3].GetString()));
			}
			if (funcParameter["material"].HasMember("specular"))
			{
				material.specular = XMFLOAT4(std::stof(funcParameter["material"]["specular"][0].GetString()),
					std::stof(funcParameter["material"]["specular"][1].GetString()),
					std::stof(funcParameter["material"]["specular"][2].GetString()),
					std::stof(funcParameter["material"]["specular"][3].GetString()));
			}
			if (funcParameter["material"].HasMember("reflect"))
			{
				material.reflect = XMFLOAT4(std::stof(funcParameter["material"]["reflect"][0].GetString()),
					std::stof(funcParameter["material"]["reflect"][1].GetString()),
					std::stof(funcParameter["material"]["reflect"][2].GetString()),
					std::stof(funcParameter["material"]["reflect"][3].GetString()));
			}
			setMaterial(material);
		}
	}

	void IComponent::set_Transform(const rapidjson::Value& funcParameter)
	{
		if (funcParameter.HasMember("transform"))
		{
			Transform transform;
			if (funcParameter["transform"].HasMember("scale"))
			{
				transform.setScale((XMFLOAT3(std::stof(funcParameter["transform"]["scale"][0].GetString()),
					std::stof(funcParameter["transform"]["scale"][1].GetString()),
					std::stof(funcParameter["transform"]["scale"][2].GetString()))
				));
			}
			if (funcParameter["transform"].HasMember("rotation"))
			{
				transform.setRotation(XMFLOAT3(std::stof(funcParameter["transform"]["rotation"][0].GetString()),
					std::stof(funcParameter["transform"]["rotation"][1].GetString()),
					std::stof(funcParameter["transform"]["rotation"][2].GetString())
				));
			}			
			if (funcParameter["transform"].HasMember("position"))
			{
				transform.setPosition(XMFLOAT3(std::stof(funcParameter["transform"]["position"][0].GetString()),
					std::stof(funcParameter["transform"]["position"][1].GetString()),
					std::stof(funcParameter["transform"]["position"][2].GetString())
				));
			}
			setTransform(transform);
		}
	}

	void IComponent::setUseTexOrColor(bool isUseTex, const XMFLOAT4 & color)
	{
		if (m_pUseColorCB)
		{
			UseTexOrColor useTexOrColor;
			useTexOrColor.isUseTex = isUseTex;
			useTexOrColor.texColor = color;

			if (m_pUseColorCB)
			{
				D3D11_MAPPED_SUBRESOURCE mappedData;
				m_pd3dImmediateContext->Map(m_pUseColorCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
				memcpy_s(mappedData.pData, sizeof(UseTexOrColor), &useTexOrColor, sizeof(UseTexOrColor));
				m_pd3dImmediateContext->Unmap(m_pUseColorCB.Get(), 0);
			}
		}
	}


	IComponent::~IComponent()
	{
		m_pWorldMatrixCB.Reset();
		m_pVertexShader.Reset();
		m_pPixelShader.Reset();
		m_pVertexLayout.Reset();
		m_pTexture.Reset();
		m_pMaterialCB.Reset();
		m_pUseColorCB.Reset();
	}

	void IComponent::setVsShader(const std::string& vsShader)
	{
		m_vsShader = vsShader;
		m_pVertexShader.Reset();

		ComPtr<ID3DBlob> blob;

		m_pVertexShader = AssetManager::getInstance().loadVsShaderAsset(vsShader, blob);
		if (m_pVertexShader)
			createVertexLayout(blob);

		//blob.Reset();


	}

	void IComponent::setGsShader(const std::string& gsShader)
	{
		m_gsShader = gsShader;
		m_pGeometryShader.Reset();

		m_pGeometryShader = AssetManager::getInstance().loadGsShaderAsset(gsShader);
	}

	void IComponent::setPsShader(const std::string& psShader)
	{
		m_psShader = psShader;
		m_pPixelShader.Reset();

		m_pPixelShader = AssetManager::getInstance().loadPsShaderAsset(psShader);
	}

	void IComponent::setTexture(const std::string& texture)
	{
		m_texture = texture;
		m_pTexture.Reset();

		m_pTexture = AssetManager::getInstance().loadTextureAsset(texture);

	}

	void IComponent::setMaterial(const Material& material) 
	{ 
		m_material = material; 

		if (m_pMaterialCB)
		{
			D3D11_MAPPED_SUBRESOURCE mappedData;
			m_pd3dImmediateContext->Map(m_pMaterialCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
			memcpy_s(mappedData.pData, sizeof(Material), &m_material, sizeof(Material));
			m_pd3dImmediateContext->Unmap(m_pMaterialCB.Get(), 0);
		}
	}

	XMMATRIX XM_CALLCONV InverseTranspose(DirectX::FXMMATRIX M)
	{
		using namespace DirectX;

		XMMATRIX A = M;
		A.r[3] = g_XMIdentityR3;

		return XMMatrixTranspose(XMMatrixInverse(nullptr, A));
	}

	void IComponent::onTransformChanged()
	{
		WorldMatrix worldMatrix;
		worldMatrix.g_world = XMMatrixTranspose(m_transform.getWorldMatrix());
		worldMatrix.g_worldInvTranspose = XMMatrixTranspose(InverseTranspose(m_transform.getWorldMatrix()));

		if (m_pWorldMatrixCB)
		{
			D3D11_MAPPED_SUBRESOURCE mappedData;
			m_pd3dImmediateContext->Map(m_pWorldMatrixCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
			memcpy_s(mappedData.pData, sizeof(WorldMatrix), &worldMatrix, sizeof(WorldMatrix));
			m_pd3dImmediateContext->Unmap(m_pWorldMatrixCB.Get(), 0);
		}
	}

	void IComponent::serialize(std::string& serializationStr)
	{

		rapidjson::StringBuffer strBuf;
		rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);

		writer.StartObject();


		writer.Key("classType");
		writer.String(getComponetType().c_str());


		writer.Key("functionName");
		writer.StartArray();
		writer.String("set_VsShader");
		writer.String("set_GsShader");
		writer.String("set_PsShader");
		writer.String("set_Texture");
		writer.String("set_Material");
		writer.String("set_Transform");
		writer.EndArray();

		writer.Key("funcParameter");
		writer.StartArray();

		//VsShader
		writer.StartObject();
		writer.Key("vsShader");
		writer.String(getVsShader().c_str());
		writer.EndObject();
		//GsShader
		writer.StartObject();
		writer.Key("gsShader");
		writer.String(getGsShader().c_str());
		writer.EndObject();
		//PsShader
		writer.StartObject();
		writer.Key("psShader");
		writer.String(getPsShader().c_str());
		writer.EndObject();
		//Texture
		writer.StartObject();
		writer.Key("texture");
		writer.String(getTexture().c_str());
		writer.EndObject();
		//Material
		writer.StartObject();
		writer.Key("material");
		writer.StartObject();
		writer.String("ambient");
		writer.StartArray();
		writer.String(std::to_string(getMaterial().ambient.x).c_str());
		writer.String(std::to_string(getMaterial().ambient.y).c_str());
		writer.String(std::to_string(getMaterial().ambient.z).c_str());
		writer.String(std::to_string(getMaterial().ambient.w).c_str());
		writer.EndArray();
		writer.String("diffuse");
		writer.StartArray();
		writer.String(std::to_string(getMaterial().diffuse.x).c_str());
		writer.String(std::to_string(getMaterial().diffuse.y).c_str());
		writer.String(std::to_string(getMaterial().diffuse.z).c_str());
		writer.String(std::to_string(getMaterial().diffuse.w).c_str());
		writer.EndArray();
		writer.String("specular");
		writer.StartArray();
		writer.String(std::to_string(getMaterial().specular.x).c_str());
		writer.String(std::to_string(getMaterial().specular.y).c_str());
		writer.String(std::to_string(getMaterial().specular.z).c_str());
		writer.String(std::to_string(getMaterial().specular.w).c_str());
		writer.EndArray();
		writer.String("reflect");
		writer.StartArray();
		writer.String(std::to_string(getMaterial().reflect.x).c_str());
		writer.String(std::to_string(getMaterial().reflect.y).c_str());
		writer.String(std::to_string(getMaterial().reflect.z).c_str());
		writer.String(std::to_string(getMaterial().reflect.w).c_str());
		writer.EndArray();
		writer.EndObject();
		writer.EndObject();
		//Transform
		writer.StartObject();
		writer.Key("transform");
		writer.StartObject();
		writer.String("scale");
		writer.StartArray();
		writer.String(std::to_string(getTransform().getScale().x).c_str());
		writer.String(std::to_string(getTransform().getScale().y).c_str());
		writer.String(std::to_string(getTransform().getScale().z).c_str());
		writer.EndArray();
		writer.String("rotation");
		writer.StartArray();
		writer.String(std::to_string(getTransform().getRotation().x).c_str());
		writer.String(std::to_string(getTransform().getRotation().y).c_str());
		writer.String(std::to_string(getTransform().getRotation().z).c_str());
		writer.EndArray();
		writer.String("position");
		writer.StartArray();
		writer.String(std::to_string(getTransform().getPosition().x).c_str());
		writer.String(std::to_string(getTransform().getPosition().y).c_str());
		writer.String(std::to_string(getTransform().getPosition().z).c_str());
		writer.EndArray();
		writer.EndObject();
		writer.EndObject();


		writer.EndArray();
		writer.EndObject();

		serializationStr = strBuf.GetString();
	}

	void IComponent::runFunction(const std::string& funcName, const rapidjson::Value& funcParameter)
	{
		if (m_functions.find(funcName) != m_functions.end())
		{
			m_functions[funcName](funcParameter);
		}
	}
}
