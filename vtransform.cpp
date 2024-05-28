#include <math.h>
#include "vector3.h"

double* transform(double v[3], double a1, double a2, double a3)
{
	double mat[3][3] =
	{ {cos(a2) * cos(a3), -sin(a3) * cos(a2), sin(a2)},
	{sin(a1) * sin(a2) * sin(a3) + sin(a3) * cos(a1), -sin(a1) * sin(a2) * sin(a3) + cos(1) * cos(3), -sin(a1) * cos(a2)},
	{sin(a1) * sin(a3) - sin(a2) * cos(a1) * cos(a3), sin(a1) * cos(a3) + sin(a2) * sin(a3) * cos(a1), cos(a1) * cos(a2)} };
	double res[3];
	res[0] = mat[0][0] * v[0] + mat[0][1] * v[1] + mat[0][2] * v[2];
	res[1] = mat[1][0] * v[0] + mat[1][1] * v[1] + mat[1][2] * v[2];
	res[2] = mat[2][0] * v[0] + mat[2][1] * v[1] + mat[2][2] * v[2];
	return res;
}

vector3* makeCircle(vector3 p1, vector3 p2, double h, int num = 1)
{
	vector3* res = new vector3[num];

	double floor = fmin(p1.z, p2.z);
	vector3 radVec = p2 - p1; radVec.z = 0;

	vector3 center;
	if (p1.z > p2.z)
	{
		center = p2 + radVec.normalized(-h);
	}
	else
	{
		center = p1 + radVec.normalized(h);
	}
	center.z = floor;

	double dist = radVec.len();
	vector3 start = p1; start.z = floor;
	vector3 step = radVec.normalized(dist / num);
	
	for (int i = 0; i < num; i++)
	{
		vector3 newP = center + step * (i + 1);
		double l = step.len() * (i + 1);
		double newZ = floor + sqrt(fabs(h * h - l * l));
		newP.z = newZ;
		res[i] = newP;
	}

	return res;
}