#pragma once

class vector3
{
public:
	double x = 0;
	double y = 0;
	double z = 0;
	vector3(int x = 0, int y = 0, int z = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	vector3(vector3& vec1)
	{
		this->x = vec1->x;
		this->y = vec1->y;
		this->z = vec1->z;
	}
	double len();
	vector3 operator +(vector3& vec1, vector3& vec2);
	vector3 operator -(vector3& vec1, vector3& vec2);
};