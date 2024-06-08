#include "stabilization.h"
#include "vector3.h"
#include "settings.h"

#ifndef max
#define max(a,b) a>b? a:b
#endif

#ifndef min
#define min(a,b) a<b? a:b
#endif


template<typename T> T clamp(T val, T left, T right)
{
	if (left > right)
	{
		T c = left;
		left = right;
		right = c;
	}
	return min(max(val, left), right);
}


vector3* stabilize(vector3* cur)
{
	vector3 rightFront = cur[0];
	vector3 leftFront = cur[1];
	vector3 rightBack = cur[2];
	vector3 leftBack = cur[3];

	vector3 rightFrontPos = (ROBOTLENGTH/2, ROBOTWIDTH/2, ROBOTHEIGHT);
	vector3 leftFrontPos = (ROBOTLENGTH / 2, -ROBOTWIDTH / 2, ROBOTHEIGHT);
	vector3 rightBackPos = (-ROBOTLENGTH / 2, ROBOTWIDTH / 2, ROBOTHEIGHT);
	vector3 leftBackPos = (-ROBOTLENGTH / 2, -ROBOTWIDTH / 2, ROBOTHEIGHT);

	double floor = rightFront.z;
	floor = min(floor, leftFront.z);
	floor = min(floor, rightBack.z);
	floor = min(floor, leftBack.z);

	enum states {leftFall, rightFall, wrongPos, rightPos};

	int state = rightPos;

	if (rightFront.y < 5 and rightBack.y < 5)
	{
		state = rightFall;
	}
	else if (leftFront.y < 5 and leftBack.y < 5)
	{
		state = leftFall;
	}
	else
	{
		if ((rightFront.z - floor) > 6 or 
			(leftFront.z - floor > 6) or
			(rightBack.z - floor > 6) or
			(leftBack.z - floor > 6))
		{
			state = wrongPos;
		}
		if (rightFront.distance(rightFrontPos) > 15 or
			leftFront.distance(leftFrontPos) > 15 or
			rightBack.distance(rightBackPos) > 15 or
			leftBack.distance(leftBackPos) > 15)
		{
			state = wrongPos;
		}
	}

	bool leftSupport = (leftFront.z - floor <= 6 or leftBack.z - floor <= 6);
	bool rightSupport = (rightFront.z - floor <= 6 or rightBack.z - floor <= 6);

	switch (state)
	{
	case rightPos:
		break;
	case wrongPos:
		if (rightFront.z - floor > 6 or (rightFront.distance(rightFrontPos) > 15 and rightSupport))
		{
			cur[0] = rightFrontPos;
		}
		if (leftFront.z - floor > 6 or (leftFront.distance(leftFrontPos) > 15 and leftSupport))
		{
			cur[1] = leftFrontPos;
		}
		if (rightBack.z - floor > 6 or (rightBack.distance(rightBackPos) > 15 and rightSupport))
		{
			cur[2] = rightBackPos;
		}
		if (leftBack.z - floor > 6 or (leftBack.distance(leftBackPos) > 15 and leftSupport))
		{
			cur[3] = leftBackPos;
		}
		break;
	case leftFall:
		if (rightSupport)
		{
			cur[1] = leftFrontPos;
			cur[3] = leftBackPos;
		}
		else
		{
			cur[0] = rightFrontPos;
			cur[2] = rightBackPos;
		}
		break;
	case rightFall:
		if (leftSupport)
		{
			cur[0] = rightFrontPos;
			cur[2] = rightBackPos;
		}
		else
		{
			cur[1] = leftFrontPos;
			cur[3] = leftBackPos;
		}
		break;
	}
	return cur;
}