#include "StdAfx.h"
#include "TransformationController.h"


TransformationController::TransformationController(void)
{
	//initialize with identity matrix
	matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1.0;
	matrix[1] = matrix[2] = matrix[3] = matrix[4] = matrix[6] =
		matrix[7] = matrix[8] = matrix[9] = matrix[11] = matrix[12]=
		matrix[13] = matrix[14] = 0.0;
}

float* TransformationController::getMatrix()
{
	return matrix;
}

void TransformationController::translate(double x, double y, double z) {
	matrix[0] = 1;	matrix[4] = 0;	matrix[8] = 0;	matrix[12] = x;
	matrix[1] = 0;	matrix[5] = 1;	matrix[9] = 0;	matrix[13] = y;
	matrix[2] = 0;	matrix[6] = 0;	matrix[10] = 1;	matrix[14] = z;
	matrix[3] = 0;	matrix[7] = 0;	matrix[11] = 0;	matrix[15] = 1;
}

void TransformationController::scale(double x, double y, double z) {
	matrix[0] = x;	matrix[4] = 0;	matrix[8] = 0;	matrix[12] = 0;
	matrix[1] = 0;	matrix[5] = y;	matrix[9] = 0;	matrix[13] = 0;
	matrix[2] = 0;	matrix[6] = 0;	matrix[10] = z;	matrix[14] = 0;
	matrix[3] = 0;	matrix[7] = 0;	matrix[11] = 0;	matrix[15] = 1;
}

void TransformationController::rotate(double theta) {
	matrix[0] = cos(theta);	matrix[4] = -sin(theta);  matrix[8] = 0;	matrix[12] = 0;
	matrix[1] = sin(theta);	matrix[5] = cos(theta);	  matrix[9] = 0;	matrix[13] = 0;
	matrix[2] = 0;			matrix[6] = 0;			  matrix[10] = 1;	matrix[14] = 0;
	matrix[3] = 0;			matrix[7] = 0;			  matrix[11] = 0;	matrix[15] = 1;
}


TransformationController::~TransformationController(void)
{
}
