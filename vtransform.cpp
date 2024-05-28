#include <math.h>


double dist(double p1[3], double p2[3] = {0,0,0})
{
	return sqrt((p1[1] - p2[1]) * (p1[1] - p2[1]) + (p1[2] - p2[2]) * (p1[2] - p2[2]) + (p1[3] - p2[3]) * (p1[3] - p2[3]));
}

double* multiply(double v1[3], double n)
{
	double res[3] = { v1[1] * n, v1[2] * n, v1[3] * n };
	return res;
}

double* normalize(double v1[3], double n)
{
	double d = dist(v1, { 0,0,0 });
	return multiply(v1, n / d);
}

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

double** makeCircle(double p1[3], double p2[3], double h, int num = 1)
{
	double** res = new double[3][num];

	double floor[3] = fmin(p1[3], p2[3]);
	double d = dist({ p1[1], p1[2], floor }, { p2[1], p2[2], floor });

	double radius_vector[3] = {p1[1] - p2[1], p1[2] - p2[2], 0};
	radius_vector = normalize(radius_vector, h);
	double center[3] = {p2[1] + radius_vector[1], p2[2] + radius_vector[2], p2[3] + radius_vector[3]};

	double flat_vector[3] = {p2[1] - p1[1], p2[2] - p1[2], 0};
	flat_vector = normalize(flat_vector, ((double)1)/ num);
	for (int i = 0; i < num; i++)
	{
		double flatPoint[3] = { p1[1] + flat_vector[1] * (i + 1), p1[2] + flat_vector[2] * (i + 1), floor};
		double curDist = dist(flatPoint, center);
		double newH = floor + sqrt(fabs(h * h - curDist * curDist));
		res[i][0] = flatPoint[0]; res[i][1] = flatPoint[1]; res[i][2] = newH;
	}

	return res;
}