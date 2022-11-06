/***************************************************************************************
Author: lvke
Date:2022/11/06 11:31
Description:
Axis Component when pick something
****************************************************************************************/

#pragma once
#include "CylinderComponent.h"
#include "ConeComponent.h"
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
		IComponent* getBindedComponent() { return m_bindComponent; }
		void enableShow(bool flag) { m_bShow = flag; }
		void  draw();
		std::string pickDetection(uint16_t mouseX, uint16_t mouseY);
	private:
		std::map<std::string, IComponent*> m_componets;
		std::map<std::string, std::string> m_UuidWithName;
		//green
		IComponent* icUp{ nullptr };
		IComponent* icUpArrow{ nullptr };
		//red
		IComponent* icRight{ nullptr };
		IComponent* icRightArrow{ nullptr };
		//blue
		IComponent* icForward{ nullptr };
		IComponent* icForwardArrow{ nullptr };


		bool m_bShow = false;

		IComponent* m_bindComponent{ nullptr };
		XMFLOAT3 m_position{0.0f, 0.0f, 0.0f};
	};
}


