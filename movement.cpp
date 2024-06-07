#include "movement.h"
#define THRESHOLD 0.003

#ifndef max
#define max(a,b) a>b? a:b
#endif

#ifndef min
#define min(a,b) a<b? a:b
#endif

#ifndef abs
#define abs(a) a<0? -a:a
#endif

void move(Adafruit_PWMServoDriver& pwm, int* pins, double* angles)
{
	for (int i = 0; i < 3; i++)
	{
		if (abs(angles[i]) < THRESHOLD)
		{
			angles[i] = 0;
		}
	}
	double maxAng = max(max(abs(angles[0]), abs(angles[1])), abs(angles[2]));
	double k = SERVOMAX / maxAng;
	for (int i = 0; i < 3; i++)
	{
		double val = angles[i] * k;
		if (abs(val) >= SERVOMIN)
		{
			pwm.setPWM(pins[i], 0, val);
		}
	}
}