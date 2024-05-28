#include "sensor.h"

volatile bool mpuFlag = false;

void dmpReady() {
	mpuFlag = true;
}

void sensor_setup(MPU6050 mpu)
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