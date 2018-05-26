#include "MiniginPCH.h"
#include "Transform.h"


void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
}

void dae::Transform::SetAngle(float angle)
{
	mAngle = angle;
}
