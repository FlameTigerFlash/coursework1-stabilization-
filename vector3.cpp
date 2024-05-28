#include "vector3.h"
#include <math.h>

double vector3::len()
{
	return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}

vector3 vector3::operator +(vector3& vec1, vector3& vec2)
{
	return vector3(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

vector3 vector3::operator -(vector3& vec1, vector3& vec2)
{
	return vector3(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}

vector3 vector3::operator *(vector3& vec1, double num)
{
	return vector3(vec1.x * num, vec1.y * num, vec1.z * num);
}

vector3 vector3::normalized(vector3& vec1, double num)
{
	double newL = (num / vec1.len());
	return vector3(vec1.x * newL, vec1.y * newL, vec1.z * newL);
}