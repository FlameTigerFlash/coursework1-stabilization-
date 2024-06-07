#include "movement.h"
#include "sensor.h"
#include "vtransform.h"
#include "stabilization.h"
#include "vector3.h"

MPU6050 mpu;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

bool ready = false;

void setState3D(int state[][4][3]) {
  int len = sizeof(state)/sizeof(state[0]);
  for (int k = 0; k < len; k++) {
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 3; j++)
        pwm.setPWM(legPins[i][j], 0, state[k][i][j]);
    delay(300);
  }
}

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

void setup()
{
	sensor_setup();
}
void loop()
{
	delay(10);
}