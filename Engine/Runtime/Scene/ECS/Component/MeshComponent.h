/***************************************************************************************
Author: lvke
Date:2022/12/05 21:36
Description:
Transform Component
****************************************************************************************/
#pragma once
#include "Interface/ComponentInterface.h"


namespace Twinkle
{
	class IBindable;
	class MeshComponent : public IComponent
	{
	public:
		MeshComponent();
		virtual ~MeshComponent();

		virtual void tick(float deltaTime) override;
	private:
		IBindable* m_vertexBuffer{ nullptr };
		IBindable* m_indexBuffer{ nullptr };
		IBindable* m_vertexShader{ nullptr };
		IBindable* m_inputLayout{ nullptr };
		IBindable* m_pixelShader{ nullptr };
		IBindable* m_texture{ nullptr };
		IBindable* m_samplerState{ nullptr };
	};
}