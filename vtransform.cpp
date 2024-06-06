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

double angle(vector3 v1, vector3 v2)
{
  if (v1.len() == 0 or v2.len() == 0)
  {
    return 0;
  }
	return acos((v1.len()*v1.len() + v2.len()* v2.len() - (v1-v2).len() * (v1 - v2).len()) / (2 * v1.len() * v2.len()));
}

double distance(vector3 v1, vector3 v2)
{
	return sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y) + (v1.z - v2.z) * (v1.z - v2.z));
}

double* intersection(double dist, double rad1, double rad2)
{
	double* ans = new double[2];
	ans[0] = 0; ans[1] = ans[0];
	
	if (rad1 + dist < rad2 or rad2 + dist < rad1)
	{
		return ans;
	}
	if (dist > rad1 + rad2)
	{
		return ans;
	}

	double dif = (rad1 * rad1 - rad2 * rad2) / (dist);
	double hor = (dist + dif) / 2;
	double vert = sqrt(rad1 * rad1 - hor * hor);
	ans[0] = atan(vert / hor);
	ans[1] = atan(vert / (dist - hor));
	return ans;
}

double* moveData(vector3 v2, double pt1, double pt2, double pt3)
{
	vector3 start = (0, 0, 0);
	vector3 side = v2; side.x = 0;
	double ret[3] = { 0, 0, 0 };
	if (side.len() < pt1)
	{
		return ret;
	}
	
	double rad2 = sqrt(side.len() * side.len() - pt1 * pt1);
	double dif = (pt1 * pt1 - rad2 * rad2) / (side.len());
	vector3 aux = side.normalized((side.len() + dif) / 2);
	vector3 perp(0, -aux.z, aux.y);
	if (perp.y < 0)
	{
		perp = perp * (-1);
	}

	vector3 v1 = aux + perp.normalized(sqrt(pt1 * pt1 - aux.len() * aux.len()));
	ret[0] = angle(vector3(0, pt1, 0), v1);
	if (v1.y < 0)
	{
		ret[0] *= (-1);
	}

	ret[1] = angle(vector3(0, 0, -pt1), (v2 - v1));
	if (v2.x < 0)
	{
		ret[1] *= (-1);
	}

	double* bend = intersection(pt2, pt3, distance(v1, v2));
	ret[1] -= bend[0];
	ret[2] = bend[1];

	return ret;
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