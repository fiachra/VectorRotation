#include <stdio.h>
#include "VectorRotation.h"

int NUM_TESTS = 5;

double LIST_ROT_VALUES[] ={90, 0, 0, 90, 0, 0, 90, 0, 0, 90, 0, 0, 90, 0, 0};
double LIST_POS_VALUES[] ={0, 0, 0, 0, 10, 0, 0, 10, 5, 0, 10, 25, -5, 10, 25};
double OBJ_POS_VALUES[] ={-10, 0, 0, -10, 0, 5, -10, 10, 5, -10, 20, 5, -10, 20, 25};
double NEW_OBJ_POS_VALUES[] ={-10, 0, 0, -10, 5, 10, -10, 0, 0, -10, -20, -10, -5, 0, -10};


int main(){

	int i;
	int count = 0;

	for(i = 0;i<NUM_TESTS;i++)
	{
		Vec3 listenerPos;
		listenerPos.x = LIST_POS_VALUES[count+0];
		listenerPos.y = LIST_POS_VALUES[count+1];
		listenerPos.z = LIST_POS_VALUES[count+2];

		Rot3 listenerRot;
		listenerRot.roll = LIST_ROT_VALUES[count+0];
		listenerRot.pitch = LIST_ROT_VALUES[count+1];
		listenerRot.yaw = LIST_ROT_VALUES[count+2];

		Vec3 objectPos;
		objectPos.x = OBJ_POS_VALUES[count+0];
		objectPos.y = OBJ_POS_VALUES[count+1];
		objectPos.z = OBJ_POS_VALUES[count+2]; 

		Vec3 objectPosLSExpected;
		objectPosLSExpected.x = NEW_OBJ_POS_VALUES[count+0];
		objectPosLSExpected.y = NEW_OBJ_POS_VALUES[count+1];
		objectPosLSExpected.z = NEW_OBJ_POS_VALUES[count+2]; 

		Vec3 objectPosLS;

		RotationErrorCode err = ConvertToListenerSpace(&objectPos, &listenerPos , &listenerRot, &objectPosLS);

		printf("Test %i:\n", i+1);
		printf("Listener Position:");
		printVec3(&listenerPos);
		printf("Listener Rotation:");
		printRot3(&listenerRot);
		printf("Object Position:");
		printVec3(&objectPos);
		printf("Object Expected Position:");
		printVec3(&objectPosLSExpected);
		printf("Object Calculated Position:");
		printVec3(&objectPosLS);

		if(err != REC_OK)
		{
			printf("Result: FAILED\n\n");
		}
		else
		{
			printf("Result: PASSED\n\n");
		}
	}

	return 0;
}