#include <Wire.h>
#include "Adafruit_PWMServoDriver.h"
#include "settings.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

//Задание состояний сервоприводов. 
//На вход подается массив матриц состояний для каждого сервопривода. 
//Каждая матрица выполняется последовательно.
//Таким образом, каждое подобное состояние состоит из подсостояний.
void setState3D(int state[][4][3]) {
  int len = sizeof(state)/sizeof(state[0]);
  for (int k = 0; k < len; k++) {
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 3; j++)
        pwm.setPWM(legPins[i][j], 0, state[k][i][j]);
    delay(300);
  }
}

//Функция для тестирования сервоприводов робота.
void setServoFromSerial() {
  // Drive each servo one at a time using setPWM()
  Serial.print("Input leg: ");
  int leg = Serial.parseInt();
  Serial.print("Input serv: ");
  int serv = Serial.parseInt();
  Serial.print("Input pulse: ");
  int puls = Serial.parseInt();
  
  pwm.setPWM(legPins[leg][serv], 0, puls);
  Serial.print(leg);
  Serial.print(" ");
  Serial.print(serv);
  Serial.print(" -> ");
  Serial.println(puls);
}

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(100000);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);  
}

void loop() {
  //Примеры вызова функций
  //setState3D(runState);
  setServoFromSerial();
}
