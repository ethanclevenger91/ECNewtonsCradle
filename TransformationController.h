#ifndef TRANSFORMATIONCONTROLLER_H
#define TRANSFORMATIONCONTROLLER_H

#include <math.h>


class TransformationController
{
public:
	TransformationController(void);
	~TransformationController(void);
	void rotate(double theta);
	void translate(double x, double y, double z);
	void scale(double x, double y, double z);

	float* getMatrix();

private:
	float matrix[16];
};

#endif

