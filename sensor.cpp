#include "sensor.h"


float* getAngles(MPU6050& mpu, uint8_t* fifoBuffer)
{
	Quaternion q;
	VectorFloat gravity;

	float ypr[3] = {0, 0, 0};

	mpu.dmpGetQuaternion(&q, fifoBuffer);
	mpu.dmpGetGravity(&gravity, &q);
	mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
	return ypr;
}



