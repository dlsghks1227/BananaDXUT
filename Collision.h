#pragma once
#include "DXUT.h"

namespace Collision
{
	bool BoundingBoxCollision(D3DXPLANE const& rectA, D3DXPLANE const& rectB)
	{
		if (rectA.a < rectB.c && 
			rectA.c > rectB.a && 
			rectA.b < rectB.d && 
			rectA.d > rectB.b)
			return true;
		return false;
	}
	
	bool BoundingBoxPointCollision(D3DXPLANE const& rect, D3DXVECTOR3 const& point)
	{
		if (rect.a < point.x &&
			rect.c > point.x &&
			rect.b < point.y &&
			rect.d > point.y)
			return true;
		return false;
	}
}