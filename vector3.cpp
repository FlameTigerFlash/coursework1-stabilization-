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