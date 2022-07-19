#include "Chapter1Scene.h"
#include "Chapter2Scene.h"
#include "Chapter3Scene.h"
#include <string>




class SceneFactory
{
public:
	static IScene* createChpaterScene(std::string type, ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
	{
		if (type == "Chapter 1")
			return new Chapter1Scene(pd3dDevice, pd3dImmediateContext);
		else if (type == "Chapter 2")
			return new Chapter2Scene(pd3dDevice, pd3dImmediateContext);
		else if (type == "Chapter 3")
			return new Chapter3Scene(pd3dDevice, pd3dImmediateContext);

		return nullptr;
	}
};