#pragma once
#include <vector>
#include "../../Core/Engine/Engine.h"

namespace Twinkle
{
	class IBindable;
	class TestComponent
	{
		struct Vertex
		{
			float x;
			float y;
			float r;
			float g;
			float b;
		};
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
		std::vector<IBindable*> cbs;
	};
}