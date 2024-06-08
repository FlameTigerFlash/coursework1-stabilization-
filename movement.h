#pragma once
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "settings.h"


void setState(Adafruit_PWMServoDriver& pwm, int state[4][3]);

int** getState(Adafruit_PWMServoDriver& pwm);