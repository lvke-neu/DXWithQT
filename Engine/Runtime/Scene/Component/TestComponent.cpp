#include "TestComponent.h"
#include "../../Core/Bindable/BindableManager.h"

namespace Twinkle
{
	TestComponent::TestComponent()
	{
		std::vector<Vertex> vertices{

			{0.0f, 0.5f, 1.0f, 0.0f, 0.0f},
			{0.5f, 0.0f, 0.0f, 1.0f, 0.0f},
			{-0.5f, 0.0f, 0.0f, 0.0f, 1.0f},
			{0.0f, -0.5f, 1.0f, 0.0f, 0.0f}
		};
		
		vertexBuffer = Singleton<BindableManager>::GetInstance().CreateVertexBuffer<Vertex>(vertices);

		//indexbuffer
		std::vector<UINT32> indices{ 0,1,2,2,1,3 };
		
		indexBuffer = Singleton<BindableManager>::GetInstance().CreateIndexBuffer<UINT32>(indices, DXGI_FORMAT_R32_UINT);

		//vertexshader
		vertexShader = Singleton<BindableManager>::GetInstance().CreateVertexShader("\\builtin\\BinShader\\VertexShader.cso");
		
		//inputlayout
		std::vector<D3D11_INPUT_ELEMENT_DESC> ied
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		
		inputLayout = Singleton<BindableManager>::GetInstance().CreateInputLayout("\\builtin\\BinShader\\VertexShader.cso", ied);

		//pixelshader
		pixelShader = Singleton<BindableManager>::GetInstance().CreatePixelShader("\\builtin\\BinShader\\PixelShader.cso");


		//constantbuffer
		struct ColorCB
		{
			float r;
			float g;
			float b;
			float a;
		};
		ColorCB ccb{ 1.0f, 1.0f, 0.0f, 1.0f };
		IBindable* constantBuffer = Singleton<BindableManager>::GetInstance().CreateConstantBuffer<ColorCB>(0);
		dynamic_cast<ConstantBuffer<ColorCB>*>(constantBuffer)->update(ccb);
		
		cbs.push_back(constantBuffer);
	}

	TestComponent::~TestComponent()
	{
		Singleton<BindableManager>::GetInstance().Release(vertexBuffer);
		Singleton<BindableManager>::GetInstance().Release(indexBuffer);
		Singleton<BindableManager>::GetInstance().Release(vertexShader);
		Singleton<BindableManager>::GetInstance().Release(inputLayout);
		Singleton<BindableManager>::GetInstance().Release(pixelShader);
		Singleton<BindableManager>::GetInstance().Release(cbs);
	}

	void TestComponent::draw()
	{
		Singleton<BindableManager>::GetInstance().DrawCall<UINT32>(vertexBuffer, indexBuffer, vertexShader, inputLayout, pixelShader, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, cbs);
	}
}

