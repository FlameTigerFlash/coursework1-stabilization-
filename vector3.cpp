#include "vector3.h"
#include <math.h>


vector3::vector3(const vector3& vec1)
{
	this->x = vec1.x;
	this->y = vec1.y;
	this->z = vec1.z;
}

double vector3::len()
{
	return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}

double vector3::distance(const vector3& vec2)
{
	return sqrt((x - vec2.x) * (x - vec2.x) + (y - vec2.y) * (y - vec2.y) + (z - vec2.z) * (z - vec2.z));
}

vector3 vector3::operator +(const vector3& vec2)
{
	return vector3(x + vec2.x, y + vec2.y, z + vec2.z);
}

vector3 vector3::operator -(const vector3& vec2)
{
	return vector3(x - vec2.x, y - vec2.y, z - vec2.z);
}

vector3 vector3::operator *(double num)
{
	return vector3(x * num, y * num, z * num);
}

vector3& vector3::operator=(const vector3& vec2)
{
	x = vec2.x;
	y = vec2.y;
	z = vec2.z;
	return *this;
}

vector3 vector3::normalized(double num)
{
	double newL = (num / this->len());
	return vector3(x * newL, y * newL, z * newL);
}