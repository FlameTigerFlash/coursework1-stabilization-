#include "sensor.h"
#include "vtransform.h"
#include "stabilization.h"

MPU6050 mpu;

uint8_t fifoBuffer[45];



void setup()
{
	sensor_setup(mpu);
}
void loop()
{
  return;
}