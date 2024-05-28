#include "stabilization.h"

template<typename T> T min(T a, T b)
{
	if (a < b) return a;
	return b;
}

template<typename T> T max(T a, T b)
{
	if (a > b) return a;
	return b;
}

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

/*pos* stabilize(pos* cur)
{
	pos* rightFront = &cur[0];
	pos* leftFront = &cur[1];
	pos* rightBack = &cur[2];
	pos* leftBack = &cur[3];

	

	if (rightFront->w < 5 or rightBack->w < 5)
	{
		rightFront->w = min(20.0, rightFront->w);
		rightBack->w = min(20.0, rightBack->w);
	}
	if (leftFront->w < 5 or leftBack->w < 5)
	{
		leftFront->w = min(20.0, leftFront->w);
		leftBack->w = min(20.0, leftBack->w);
	}
	return cur;
}*/



pos* stabilize(pos* cur)
{
	pos* rightFront = &cur[0];
	pos* leftFront = &cur[1];
	pos* rightBack = &cur[2];
	pos* leftBack = &cur[3];

	return cur;
}