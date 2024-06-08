#include "movement.h"
#include "sensor.h"
#include "vtransform.h"
#include "stabilization.h"
#include "vector3.h"
#include "settings.h"
#include <math.h>

MPU6050 mpu;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

bool ready = false;

uint8_t fifoBuffer[45];

void dmpReady()
{
	ready = true;
}

void sensor_setup()
{
	Serial.begin(115200);
	Wire.begin();
	mpu.initialize();
	mpu.dmpInitialize();
	mpu.setDMPEnabled(true);


	attachInterrupt(0, dmpReady, RISING);
	mpu.CalibrateAccel(6);
	mpu.CalibrateGyro(6);
}

double puls2rad(int puls)
{
	return map(puls, SERVOMIN, SERVOMAX, -3.14, 3.14);
}

int rad2puls(double rad)
{
	return map(rad, -3.14, 3.14, SERVOMIN, SERVOMAX);
}

void setup()
{
	sensor_setup();
}
void loop()
{
	float* angles = getAngles(mpu, fifoBuffer);
	float revAngles[3] = { -angles[0], -angles[1], -angles[2] };

	vector3 sp[4] =
	{ vector3(60, -10, 0),
	vector3(60, 10, 0),
	vector3(-60, -10, 0),
	vector3(-60, 10, 0) };

	int** curState = getState(pwm);
	double** curStateAngles = new double* [3];
	for (int i = 0; i < 4; i++)
	{
		curStateAngles[i] = new double[3];
		for (int j = 0; j < 3; j++)
		{
			curStateAngles[i][j] = puls2rad(curState[i][j]);
		}
	}
	vector3 cords[4];
	
	cords[0] = sp[0] + angles2pos(curStateAngles[0], length);
	cords[1] = sp[1] + angles2pos(curStateAngles[1], length, true);
	cords[2] = sp[2] + angles2pos(curStateAngles[2], length);
	cords[3] = sp[3] + angles2pos(curStateAngles[3], length, true);

	cords[0] = transform(cords[0], angles);
	cords[1] = transform(cords[1], angles);
	cords[2] = transform(cords[2], angles);
	cords[3] = transform(cords[3], angles);


	vector3* newCords = stabilize(cords);

	newCords[0] = transform(newCords[0], revAngles);
	newCords[1] = transform(newCords[1], revAngles);
	newCords[2] = transform(newCords[2], revAngles);
	newCords[3] = transform(newCords[3], revAngles);

	int newState[4][3];

	for (int i = 0; i < 4; i++)
	{
		double* newAngles = pos2angles(newCords[i], length);
		newState[i][0] = rad2puls(newAngles[0]);
		newState[i][1] = rad2puls(newAngles[1]);
		newState[i][2] = rad2puls(newAngles[2]);
	}
	setState(pwm, newState);
	delay(10);
}