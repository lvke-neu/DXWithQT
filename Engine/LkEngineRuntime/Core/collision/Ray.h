/************************************************************************
Author: lvke
Date:2022/08/11 10:40
Description:
Ray Detection
************************************************************************/

#include <DirectXMath.h>
#include <DirectXCollision.h>
namespace LkEngine
{
	using namespace DirectX;
	class Ray
	{
	public:
		Ray() = default;
		Ray(const XMFLOAT3& origin, const XMFLOAT3& dir);

		bool hit(const BoundingBox& AABB, float& distance);
		bool hit(const BoundingOrientedBox& OBB, float& distance);
		static Ray ScreenToRay(float screenPtX, float screenPtY);
	private:
		XMFLOAT3 m_origin;
		XMFLOAT3 m_dir;
	};
}

