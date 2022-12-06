#include "CameraController.h"
#include "Runtime/Platform/Windows/PerspectiveCamera.h"

namespace Twinkle
{
	CameraController::CameraController()
	{
		Singleton<InputEventManager>::GetInstance().RegisterEvent(this);
		Singleton<TickEventManager>::GetInstance().RegisterEvent(this);
	}

	CameraController::~CameraController()
	{
		Singleton<InputEventManager>::GetInstance().UnRegisterEvent(this);
		Singleton<TickEventManager>::GetInstance().UnRegisterEvent(this);
	}

	void CameraController::tick(float deltaTime)
	{
		if (Singleton<InputEventManager>::GetInstance().IsKeyPress(Key_W))
		{
			Singleton<PerspectiveCamera>::GetInstance().moveZAxis(deltaTime * 10.0f);
		}

		if (Singleton<InputEventManager>::GetInstance().IsKeyPress(Key_S))
		{
			Singleton<PerspectiveCamera>::GetInstance().moveZAxis(-deltaTime * 10.0f);
		}

		if (Singleton<InputEventManager>::GetInstance().IsKeyPress(Key_A))
		{
			Singleton<PerspectiveCamera>::GetInstance().moveXAxis(-deltaTime * 10.0f);
		}

		if (Singleton<InputEventManager>::GetInstance().IsKeyPress(Key_D))
		{
			Singleton<PerspectiveCamera>::GetInstance().moveXAxis(deltaTime * 10.0f);
		}
	}
}