#pragma once
#include "MPU6050_6Axis_MotionApps20.h"
#include "I2Cdev.h"


float* getAngles(MPU6050& mpu, uint8_t* fifoBuffer);
