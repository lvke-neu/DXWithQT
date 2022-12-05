#pragma once
#include <vector>

namespace Twinkle
{
	class IBindable;
	class TestComponent
	{
	public:
		TestComponent();
		~TestComponent();

		void draw();

	private:
		IBindable* vertexBuffer{ nullptr };
		IBindable* indexBuffer{ nullptr };
		IBindable*	vertexShader{ nullptr };
		IBindable* inputLayout{ nullptr };
		IBindable* pixelShader{ nullptr };
		IBindable* texture{ nullptr };
		IBindable* samplerState{ nullptr };
		std::vector<IBindable*> cbs;
	};
}