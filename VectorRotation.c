#include <stdio.h>
#include <math.h>
#include "VectorRotation.h"

RotationErrorCode ConvertToListenerSpace(Vec3* objPos,Vec3* listPos, Rot3* listRot,Vec3* objLSPos)
{
	Matrix *S1, *S2, *transformation, *transformationInv, *resultMat;
	double rollRad = DEG_TO_RAD(listRot->roll);
	double pitchRad = DEG_TO_RAD(listRot->pitch);
	double yawRad = DEG_TO_RAD(listRot->yaw);


	double translationData[] = {
		1.0, 0, 0, listPos->x, 
		0, 1.0, 0, listPos->y, 
		0, 0, 1.0, listPos->z, 
		0, 0, 0, 1.0
	};

	double rollData[] = {
		1.0, 0, 0, 0, 
		0, cos(rollRad), -sin(rollRad), 0, 
		0, sin(rollRad), cos(rollRad), 0, 
		0, 0, 0, 1.0
	};

	double pitchData[] = {
		cos(pitchRad), 0, sin(pitchRad), 0, 
		0, 1.0, 0, 0, 
		-sin(pitchRad), 0, cos(pitchRad), 0, 
		0, 0, 0, 1.0
	};

	double yawData[] = {
		cos(yawRad), -sin(yawRad), 0, 0, 
		sin(yawRad), cos(yawRad), 0, 0, 
		0, 0, 1.0, 0, 
		0, 0, 0, 1.0
	};

	double objPosData[] = {
		objPos->x, objPos->y, objPos->z,1
	};

	Matrix matTranslation = {4,4,translationData};
	Matrix matRoll = {4,4,rollData};
	Matrix matPitch = {4,4,pitchData};
	Matrix matYaw = {4,4,yawData};
	Matrix matObj = {4,1,objPosData};

	S1 = matMul(&matTranslation, &matRoll);
	S2 = matMul(S1, &matPitch);
	transformation = matMul(S2, &matYaw);

	matShow(transformation);

	transformationInv = matNew(4,4);

	getInverse4x4(transformation, transformationInv);

	matShow(transformationInv);

	resultMat = matMul(transformationInv, &matObj);

	matShow(resultMat);

	return REC_OK;
}