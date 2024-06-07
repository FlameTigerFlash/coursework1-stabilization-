#pragma once
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "settings.h"


void move(Adafruit_PWMServoDriver& pwm, int* pins, double* angles);