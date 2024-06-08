#pragma once
#define SERVOMIN  100 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
#define ROBOTLENGTH 350
#define ROBOTWIDTH 100
#define ROBOTHEIGHT 80

const double length[3] = { 40, 60, 70 };
//Подключение выводов к конкретным пинам платы
const int legPins[4][3] = {  
  {0, 1, 2},     // Передняя правая
  {4, 5, 6},     // Передняя левая
  {8, 9, 10},    // Задняя правая
  {12, 13, 14}}; // Задняя левая

//Список состояний робота
const int stayState[1][4][3] = {};

const int runForwardState[2][4][3] = {};

const int runBackState[2][4][3] = {};

const int turnLeftState[3][4][3] = {};

const int turnRightState[3][4][3] = {};

const int sitState[2][4][3] = {};

const int tiltLeftState[2][4][3] = {};

const int tiltRightState[2][4][3] = {};

const int initState[1][4][3] = {};
