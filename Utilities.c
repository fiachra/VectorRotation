#include "Utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printVec3(Vec3* v)
{
	printf("X: %f Y: %f Z: %f\n", v->x,v->y,v->z);
}

void printRot3(Rot3* r)
{
	printf("Roll: %f Pitch: %f Yaw: %f\n", r->roll,r->pitch,r->yaw);
}
// Matrix manipulation code lifted from https://rosettacode.org/wiki/Matrix_multiplication#C
double dot(double *a, double *b, int len, int step)
{
	double r = 0;
	while (len--) {
		r += *a++ * *b;
		b += step;
	}
	return r;
}
 
Matrix* matNew(int h, int w)
{
	Matrix* r = malloc(sizeof(Matrix) + sizeof(double) * w * h);
	r->h = h, r->w = w;
	r->x = (double*)(r + 1);
	return r;
}
 
Matrix* matMul(Matrix* a, Matrix* b)
{
	Matrix* r;
	double *p, *pa;
	int i, j;
	if (a->w != b->h) return 0;
 
	r = matNew(a->h, b->w);
	p = r->x;
	for (pa = a->x, i = 0; i < a->h; i++, pa += a->w)
		for (j = 0; j < b->w; j++)
			*p++ = dot(pa, b->x + j, a->w, b->w);
	return r;
}
 
void matShow(Matrix* a)
{
	int i, j;
	double *p = a->x;
	for (i = 0; i < a->h; i++, putchar('\n'))
		for (j = 0; j < a->w; j++)
			printf("\t%7.3f", *p++);
	putchar('\n');
}

bool getInverse4x4(Matrix* src, Matrix* dest)
{
	int order = 4;

	double s0 = src->x[(0*order)+0] * src->x[(1*order)+1] - src->x[(1*order)+0] * src->x[(0*order)+1];
    double s1 = src->x[(0*order)+0] * src->x[(1*order)+2] - src->x[(1*order)+0] * src->x[(0*order)+2];
    double s2 = src->x[(0*order)+0] * src->x[(1*order)+3] - src->x[(1*order)+0] * src->x[(0*order)+3];
    double s3 = src->x[(0*order)+1] * src->x[(1*order)+2] - src->x[(1*order)+1] * src->x[(0*order)+2];
    double s4 = src->x[(0*order)+1] * src->x[(1*order)+3] - src->x[(1*order)+1] * src->x[(0*order)+3];
    double s5 = src->x[(0*order)+2] * src->x[(1*order)+3] - src->x[(1*order)+2] * src->x[(0*order)+3];

    double c5 = src->x[(2*order)+2] * src->x[(3*order)+3] - src->x[(3*order)+2] * src->x[(2*order)+3];
    double c4 = src->x[(2*order)+1] * src->x[(3*order)+3] - src->x[(3*order)+1] * src->x[(2*order)+3];
    double c3 = src->x[(2*order)+1] * src->x[(3*order)+2] - src->x[(3*order)+1] * src->x[(2*order)+2];
    double c2 = src->x[(2*order)+0] * src->x[(3*order)+3] - src->x[(3*order)+0] * src->x[(2*order)+3];
    double c1 = src->x[(2*order)+0] * src->x[(3*order)+2] - src->x[(3*order)+0] * src->x[(2*order)+2];
    double c0 = src->x[(2*order)+0] * src->x[(3*order)+1] - src->x[(3*order)+0] * src->x[(2*order)+1];

    double invdet = 1.0 / (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);

    if(invdet == 0)
    	return false;

    dest->x[(0*order)+0] = ( src->x[(1*order)+1] * c5 - src->x[(1*order)+2] * c4 + src->x[(1*order)+3] * c3) * invdet;
    dest->x[(0*order)+1] = (-src->x[(0*order)+1] * c5 + src->x[(0*order)+2] * c4 - src->x[(0*order)+3] * c3) * invdet;
    dest->x[(0*order)+2] = ( src->x[(3*order)+1] * s5 - src->x[(3*order)+2] * s4 + src->x[(3*order)+3] * s3) * invdet;
    dest->x[(0*order)+3] = (-src->x[(2*order)+1] * s5 + src->x[(2*order)+2] * s4 - src->x[(2*order)+3] * s3) * invdet;

    dest->x[(1*order)+0] = (-src->x[(1*order)+0] * c5 + src->x[(1*order)+2] * c2 - src->x[(1*order)+3] * c1) * invdet;
    dest->x[(1*order)+1] = ( src->x[(0*order)+0] * c5 - src->x[(0*order)+2] * c2 + src->x[(0*order)+3] * c1) * invdet;
    dest->x[(1*order)+2] = (-src->x[(3*order)+0] * s5 + src->x[(3*order)+2] * s2 - src->x[(3*order)+3] * s1) * invdet;
    dest->x[(1*order)+3] = ( src->x[(2*order)+0] * s5 - src->x[(2*order)+2] * s2 + src->x[(2*order)+3] * s1) * invdet;

    dest->x[(2*order)+0] = ( src->x[(1*order)+0] * c4 - src->x[(1*order)+1] * c2 + src->x[(1*order)+3] * c0) * invdet;
    dest->x[(2*order)+1] = (-src->x[(0*order)+0] * c4 + src->x[(0*order)+1] * c2 - src->x[(0*order)+3] * c0) * invdet;
    dest->x[(2*order)+2] = ( src->x[(3*order)+0] * s4 - src->x[(3*order)+1] * s2 + src->x[(3*order)+3] * s0) * invdet;
    dest->x[(2*order)+3] = (-src->x[(2*order)+0] * s4 + src->x[(2*order)+1] * s2 - src->x[(2*order)+3] * s0) * invdet;

    dest->x[(3*order)+0] = (-src->x[(1*order)+0] * c3 + src->x[(1*order)+1] * c1 - src->x[(1*order)+2] * c0) * invdet;
    dest->x[(3*order)+1] = ( src->x[(0*order)+0] * c3 - src->x[(0*order)+1] * c1 + src->x[(0*order)+2] * c0) * invdet;
    dest->x[(3*order)+2] = (-src->x[(3*order)+0] * s3 + src->x[(3*order)+1] * s1 - src->x[(3*order)+2] * s0) * invdet;
    dest->x[(3*order)+3] = ( src->x[(2*order)+0] * s3 - src->x[(2*order)+1] * s1 + src->x[(2*order)+2] * s0) * invdet;

    return true;
}

Quaternion *toQuaternion(Rot3 *r)
{
	double t0 = cos(DEG_TO_RAD(r->yaw) * 0.5);
	double t1 = sin(DEG_TO_RAD(r->yaw) * 0.5);
	double t2 = cos(DEG_TO_RAD(r->roll) * 0.5);
	double t3 = sin(DEG_TO_RAD(r->roll) * 0.5);
	double t4 = cos(DEG_TO_RAD(r->pitch) * 0.5);
	double t5 = sin(DEG_TO_RAD(r->pitch) * 0.5);

	double w = t0 * t2 * t4 + t1 * t3 * t5;
	double x = t0 * t3 * t4 - t1 * t2 * t5;
	double y = t0 * t2 * t5 + t1 * t3 * t4;
	double z = t1 * t2 * t4 - t0 * t3 * t5;

	return quaternionNewSet(w,x,y,z);
}

Rot3 toEulerianAngle(Quaternion* q)
{
	double ysqr = q->q[2] * q->q[2];
	Rot3 r;

	// roll (x-axis rotation)
	double t0 = +2.0 * (q->q[0] * q->q[1] + q->q[2] * q->q[3]);
	double t1 = +1.0 - 2.0 * (q->q[1] * q->q[1] + ysqr);
	r.roll = RAD_TO_DEG(atan2(t0, t1));

	// pitch (y-axis rotation)
	double t2 = +2.0 * (q->q[0] * q->q[2] - q->q[3] * q->q[1]);
	t2 = ((t2 > 1.0) ? 1.0 : t2);
	t2 = ((t2 < -1.0) ? -1.0 : t2);
	r.pitch = RAD_TO_DEG(asin(t2));

	// yaw (z-axis rotation)
	double t3 = +2.0 * (q->q[0] * q->q[3] + q->q[1] * q->q[2]);
	double t4 = +1.0 - 2.0 * (ysqr + q->q[3] * q->q[3]);  
	r.yaw = RAD_TO_DEG(atan2(t3, t4));

	return r;
}
