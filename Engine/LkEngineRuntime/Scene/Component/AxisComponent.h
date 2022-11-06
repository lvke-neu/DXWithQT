/***************************************************************************************
Author: lvke
Date:2022/11/06 11:31
Description:
Axis Component when pick something
****************************************************************************************/

#pragma once
#include "CylinderComponent.h"
#include "../../../LkEngineRuntime/Core/Event/FrameMoveEventManager.h"

namespace LkEngine
{
	class AxisComponent : public FrameMoveEvent
	{
	public:
		AxisComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
		~AxisComponent();

		virtual void onFrameMove(float deltaTime) override;

		void bindComponent(IComponent* bindComponent);
		void enableShow(bool flag) { m_bShow = flag; }
		void  draw();
	private:
		//green
		IComponent* icUp{ nullptr };
		//red
		IComponent* icRight{ nullptr };
		//blue
		IComponent* icForward{ nullptr };

		bool m_bShow = false;

		IComponent* m_bindComponent{ nullptr };
		XMFLOAT3 m_position;
	};
}


