#include <stdio.h>
#include "VectorRotation.h"

int main(){

	Vec3 objectPos;
	objectPos.x = 15;
	objectPos.y = 0;
	objectPos.z = 0; 

	Vec3 listenerPos;
	listenerPos.x = 10;
	listenerPos.y = 0;
	listenerPos.z = 0;

	Rot3 listenerRot;
	listenerRot.roll = 0;
	listenerRot.pitch = 0;
	listenerRot.yaw = 90;

	Vec3 objectLS;

	ConvertToListenerSpace(&objectPos, &listenerPos , &listenerRot, &objectLS);

	return 0;
}