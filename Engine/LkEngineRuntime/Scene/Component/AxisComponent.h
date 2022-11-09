/***************************************************************************************
Author: lvke
Date:2022/11/06 11:31
Description:
Axis Component when pick something
****************************************************************************************/

#pragma once
#include "../../../LkEngineRuntime/Core/Event/FrameMoveEventManager.h"
#include "../Component/Interface/ComponentInterface.h"

namespace LkEngine
{
	enum DragType
	{
		SCALE,
		ROTATION,
		TRANSITION
	};

	class AxisComponent : public FrameMoveEvent
	{
	public:
		AxisComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
		~AxisComponent();

		virtual void onFrameMove(float deltaTime) override;

		void bindComponent(IComponent* bindComponent);
		IComponent* getBindedComponent() { return m_bindComponent; }
		void enableShow(bool flag) { m_bShow = flag; }
		void  draw(DragType dragType);
		std::string pickDetection(uint16_t mouseX, uint16_t mouseY, DragType dragType);
		void setAxisLength(float length);
	private:
		void initAxis();
		void initArrow();
		void initCube();
		void initSphere();
		void moveAll(const XMFLOAT3& pos);
	private:
		ComPtr<ID3D11Device> m_pd3dDevice;
		ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext;

		std::map<std::string, IComponent*> m_arrowComponets;
		std::map<std::string, IComponent*> m_cubeComponets;
		std::map<std::string, IComponent*> m_sphereComponets;
		std::map<std::string, std::string> m_UuidWithName;
		//green
		IComponent* icUp{ nullptr };
		IComponent* icUpArrow{ nullptr };
		IComponent* icUpCube{ nullptr };
		IComponent* icUpSphere{ nullptr };
		//red
		IComponent* icRight{ nullptr };
		IComponent* icRightArrow{ nullptr };
		IComponent* icRightCube{ nullptr };
		IComponent* icRightSphere{ nullptr };
		//blue
		IComponent* icForward{ nullptr };
		IComponent* icForwardArrow{ nullptr };
		IComponent* icForwardCube{ nullptr };
		IComponent* icForwardSphere{ nullptr };


		bool m_bShow = false;

		IComponent* m_bindComponent{ nullptr };
		XMFLOAT3 m_position{0.0f, 0.0f, 0.0f};

		float m_length = 50.0f;
	};
}


