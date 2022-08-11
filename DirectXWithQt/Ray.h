/************************************************************************
Author: lvke
Date:2022/08/11 10:40
Description:
射线类，包含创建射线的方法（传入相机与屏幕点）
可以检测该射线与场景中的物体相交的情况
************************************************************************/

#include <DirectXMath.h>
#include "Camera.h"
using namespace DirectX;
class Ray
{
public:
	Ray() = default;
	Ray(const XMFLOAT3& origin, const XMFLOAT3& dir);

	bool hit(const BoundingBox& AABB, float& distance);
	static Ray ScreenToRay(Camera camera, float x, float y);
private:
	XMFLOAT3 m_origin;
	XMFLOAT3 m_dir;
};
