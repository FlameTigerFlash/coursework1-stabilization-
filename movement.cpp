#include "movement.h"

void setState(Adafruit_PWMServoDriver& pwm, int state[4][3])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			pwm.setPWM(legPins[i][j], 0, state[i][j]);
		}
	}
}

int** getState(Adafruit_PWMServoDriver& pwm)
{
	int** state = new int*[3];
	for (int i = 0; i < 4; i++)
	{
		state[i] = new int[3];
		for (int j = 0; j < 3; j++)
		{
			state[i][j] = pwm.getPWM(legPins[i][j]);
		}
	}
	return state;
}