#include <math.h>
#include "vector3.h"

vector3 transform(vector3 v, double a1, double a2, double a3)
{
	double mat[3][3] =
	{ {cos(a2) * cos(a3), -sin(a3) * cos(a2), sin(a2)},
	{sin(a1) * sin(a2) * sin(a3) + sin(a3) * cos(a1), -sin(a1) * sin(a2) * sin(a3) + cos(1) * cos(3), -sin(a1) * cos(a2)},
	{sin(a1) * sin(a3) - sin(a2) * cos(a1) * cos(a3), sin(a1) * cos(a3) + sin(a2) * sin(a3) * cos(a1), cos(a1) * cos(a2)} };
	vector3 res;
	res.x = mat[0][0] * v.x + mat[0][1] * v.y + mat[0][2] * v.z;
	res.y = mat[1][0] * v.x + mat[1][1] * v.y + mat[1][2] * v.z;
	res.z = mat[2][0] * v.x + mat[2][1] * v.y + mat[2][2] * v.z;
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

double* pos2angles(vector3 v2, double* ln)
{
	double pt1 = ln[0], pt2 = ln[1], pt3 = ln[2];
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
	ret[2] = bend[1] + bend[0];

	return ret;
}

vector3 angles2pos(double* ang, double* ln)
{
	vector3 j1, j2, j3;
	j1.x = 0;
	j1.y = ln[0] * cos(ang[0]);
	j1.z = ln[0] * sin(ang[0]);

	j2.y = ln[1] * sin(ang[1]) * cos(ang[2]);
	j2.x = ln[1] * sin(ang[2]);
	j2.z = ln[1] * (-cos(ang[1])) * cos(ang[2]);

	double ang2 = ang[1] + ang[2];
	j3.y = ln[2] * sin(ang[1]) * cos(ang2);
	j3.x = ln[2] * sin(ang2);
	j3.z = ln[2] * (-cos(ang[1])) * cos(ang2);
	
	return j1 + j2 + j3;
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