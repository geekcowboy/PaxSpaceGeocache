//**********************************
//
//
//**********************************

#include <Servo.h>

#define HallSensor1 0
#define HallSensor2 1
#define HallSensor3 2
#define HallSensorLock 3

#define Servo1_pin 9
#define Servo2_pin 10

#define LED1 11
#define LED2 12
#define LED3 13

#define HallOnOff 100
#define TroubleshootDelay 3000
#define Servo1_openPos 0
#define Servo2_openPos 90
#define Servo1_closePos 90
#define Servo2_closePos 0

int Status_HallSensor1 = 0;
int Status_HallSensor2 = 0;
int Status_HallSensor3 = 0;
int Status_HallSensorLock = 0;

enum State {
  start,
  letter1,
  letter2,
  opened
};

State currentState;

Servo Servo1;
Servo Servo2;


int checkHallSensor(int sensorNum);
void openBox();
void closeBox();
void flashLED10();



//**********************************
//
//
//**********************************
void setup() {
  Serial.begin(9600);
  Serial.println("Geocache initializing...");

  Servo1.attach(Servo1_pin);
  Servo2.attach(Servo2_pin);
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);

  currentState = start;

  Serial.print("Geocache opening for 10 seconds...");
  openBox();
  closeBox();
  Servo1.detach();
  Servo2.detach();
  Serial.println("LOCKED");
  Serial.println("Geocache now running...");
}








//**********************************
//
//
//**********************************
void loop() {  
  Serial.print("HallSensor1 Status: ");
  Status_HallSensor1 = checkHallSensor(HallSensor1);
  if (Status_HallSensor1 == 1 && currentState == start) {
    currentState = letter1;
    digitalWrite(LED1, HIGH);
   }

  Serial.print("HallSensor2 Status: ");
  Status_HallSensor2 = checkHallSensor(HallSensor2);
  if (Status_HallSensor2 == 1 && currentState == letter1) {
    currentState = letter2;
    digitalWrite(LED2, HIGH);
   }

  Serial.print("HallSensor3 Status: ");
  Status_HallSensor3 = checkHallSensor(HallSensor3);
  if (Status_HallSensor3 == 1 && currentState == letter2) {
    digitalWrite(LED3, HIGH);
    openBox();
    currentState = opened;
   }

  Serial.print("HallSensorLock Status: ");
  Status_HallSensorLock = checkHallSensor(HallSensorLock);
  if (Status_HallSensorLock == 1 && currentState == opened) {
    closeBox();
    currentState = start;
   }

  Serial.print("Current State: ");
  Serial.println(currentState);
  delay(TroubleshootDelay);
}







//**********************************
//
//
//**********************************
int checkHallSensor(int sensorNum) {
  int sensorReading = analogRead(sensorNum);
  if (sensorReading < HallOnOff ) {
    Serial.println("MAGNET DETECTED");
    return 1;
  }
  else {
    Serial.println("NO MAGNET");
    return 0;
  }
}





//**********************************
//
//
//**********************************
void openBox() {
  Servo1.attach(Servo1_pin);
  Servo2.attach(Servo2_pin);
  Servo1.write(Servo1_openPos);
  Servo2.write(Servo2_openPos);
  flashLED10();
  Servo1.detach();
  Servo2.detach();
}





//**********************************
//
//
//**********************************
void closeBox() {
  Servo1.attach(Servo1_pin);
  Servo2.attach(Servo2_pin);
  flashLED10();
  Servo1.write(Servo1_closePos);
  Servo2.write(Servo2_closePos);
  Servo1.detach();
  Servo2.detach();
}






//**********************************
//
//
//**********************************
void flashLED10() {
  for (int x=0; x<4; x++) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    delay(1500);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    delay(1500);
  }
  
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  delay(3000);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
}

