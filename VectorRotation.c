#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "VectorRotation.h"

RotationErrorCode ConvertToListenerSpace(Vec3* objPos,Vec3* listPos, Rot3* listRot,Vec3* objLSPos)
{
	Matrix *S1, *S2, *transformation, *transformationInv, *resultMat;
	int percisionManagmentVal = 1000;

	if(objPos == NULL || listPos == NULL || listRot == NULL || objLSPos == NULL)
		return REC_INPUT_INVALID;

	//Degrees to Rad for all input angles
	double rollRad = DEG_TO_RAD(listRot->roll);
	double pitchRad = DEG_TO_RAD(listRot->pitch);
	double yawRad = DEG_TO_RAD(listRot->yaw);

	// encode translation and rotations as 4x4 transformation Matrices.
	// Matrices are seperated to allow a change to the multiplication order if desired!
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

	Matrix matTranslation = {4,4,translationData};
	Matrix matRoll = {4,4,rollData};
	Matrix matPitch = {4,4,pitchData};
	Matrix matYaw = {4,4,yawData};
	
	// multiply all matrices to get local to world transformation
	S1 = matMul(&matTranslation, &matRoll);
	S2 = matMul(S1, &matPitch);
	transformation = matMul(S2, &matYaw);
	//matShow(transformation);

	//Get inverse to get world to local transformation, return error if non invertable
	transformationInv = matNew(4,4);
	if(!getInverse4x4(transformation, transformationInv))
		return REC_MAT_NONINVERTIBLE;

	//matShow(transformationInv);

	//create Matric 4x1 matrix for object postion
	double objPosData[] = {
		objPos->x, objPos->y, objPos->z,1
	};
	Matrix matObj = {4,1,objPosData};

	//multiply object position by transformation to get final result 
	resultMat = matMul(transformationInv, &matObj);
	//matShow(resultMat);

	//copy output values to return object and set percision to about 5 places
	objLSPos->x = floorf(resultMat->x[0] * percisionManagmentVal) / percisionManagmentVal;
	objLSPos->y = floorf(resultMat->x[1] * percisionManagmentVal) / percisionManagmentVal;
	objLSPos->z = floorf(resultMat->x[2] * percisionManagmentVal) / percisionManagmentVal;

	//Clean up
	free(S1);
	free(S2); 
	free(transformation);
	free(transformationInv);
	free(resultMat);

	return REC_OK;
}

RotationErrorCode ConvertToListenerSpaceQuat(Vec3* objPos, Vec3* listPos, Rot3* listRot, Vec3* objLSPos)
{
	Quaternion* listRotQ = toQuaternion(listRot);
	Quaternion* objPosQ = quaternionNewSet(0,objPos->x - listPos->x,objPos->y - listPos->y, objPos->z - listPos->z);
	Quaternion* listRotQConj = quaternionNew();
	Quaternion* S1 = quaternionNew();
	Quaternion* result = quaternionNew();

	quaternionConj(listRotQConj, listRotQ);
	
	//quaternionMul(S1, listRotQ, objPosQ);
	//quaternionMul(result, S1, listRotQConj);

	quaternionMul(S1, objPosQ, listRotQ);
	quaternionMul(result, listRotQConj, S1);

	objLSPos->x = result->q[1];
	objLSPos->y = result->q[2];
	objLSPos->z = result->q[3];

	return REC_OK;

}
