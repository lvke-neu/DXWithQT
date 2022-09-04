#include "Chapter1Scene.h"
#include "Chapter2Scene.h"
#include "Chapter3Scene.h"
#include "Chapter4Scene.h"
#include "Chapter5Scene.h"
#include "Chapter6Scene.h"
#include "Chapter7Scene.h"
#include "Chapter8Scene.h"
#include "Chapter9Scene.h"
#include "Chapter10Scene.h"
#include <string>




class SceneFactory
{
public:
	static IScene* createChpaterScene(std::string type, ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext, 
		ComPtr<ID3D11RenderTargetView> pRenderTargetView = nullptr,
		ComPtr<ID3D11DepthStencilView> pDepthStencilView = nullptr)
	{
		if (type == "Chapter 1")
			return new Chapter1Scene(pd3dDevice, pd3dImmediateContext);
		else if (type == "Chapter 2")
			return new Chapter2Scene(pd3dDevice, pd3dImmediateContext);
		else if (type == "Chapter 3")
			return new Chapter3Scene(pd3dDevice, pd3dImmediateContext);
		else if (type == "Chapter 4")
			return new Chapter4Scene(pd3dDevice, pd3dImmediateContext);
		else if (type == "Chapter 5")
			return new Chapter5Scene(pd3dDevice, pd3dImmediateContext);
		else if (type == "Chapter 6")
			return new Chapter6Scene(pd3dDevice, pd3dImmediateContext);
		else if (type == "Chapter 7")
			return new Chapter7Scene(pd3dDevice, pd3dImmediateContext);
		else if (type == "Chapter 8")
			return new Chapter8Scene(pd3dDevice, pd3dImmediateContext);
		else if (type == "Chapter 9")
			return new Chapter9Scene(pd3dDevice, pd3dImmediateContext, pRenderTargetView, pDepthStencilView);
		else if (type == "Chapter 10")
			return new Chapter10Scene(pd3dDevice, pd3dImmediateContext);

		return nullptr;
	}
};