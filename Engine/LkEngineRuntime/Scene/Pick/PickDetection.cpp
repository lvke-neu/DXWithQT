#include "PickDetection.h"
#include "../../Core/collision/Ray.h"
#include "../Component/Interface/ComponentInterface.h"

namespace LkEngine
{

	std::string PickDetection::pickDetect(uint16_t mouseX, uint16_t mouseY, const std::map<std::string, IComponent*>& componets)
	{
		//pick someone, return its uuid, pick null, return -1

		float minDis = FLT_MAX;
		std::string pickUuid = "-1";

		for (auto com : componets)
		{
			Ray ray_camera2pickPoint = Ray::ScreenToRay(mouseX, mouseY);
			BoundingBox aabb;
			com.second->getBoundingBox().Transform(aabb, com.second->getTransform().getWorldMatrix());

			float tmpDis = 0.0f;
			if (ray_camera2pickPoint.hit(aabb, tmpDis))
			{
				if (tmpDis < minDis)
				{
					minDis = tmpDis;
					pickUuid = com.second->getUuId();
				}
			}
		}
		return pickUuid;
	}

}

