#define HallSensor1 0
#define HallSensor2 1
#define HallSensor3 2
#define HallSensorLock 3

#define Solenoid1 8
#define Solenoid2 9

#define LED1 11
#define LED2 12
#define LED3 13

#define HallOnOff 100
#define troubleshootDelay 3000

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

int checkHallSensor(int sensorNum);
void toggleSolenoid();
void flashLED10();

void setup() {
  Serial.begin(9600);
  Serial.println("Geocache initializing...");
  
  pinMode(Solenoid1, OUTPUT);
  pinMode(Solenoid2, OUTPUT); 
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  digitalWrite(Solenoid1, LOW);
  digitalWrite(Solenoid2, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);

  currentState = start;

  Serial.print("Geocache opening for 10 seconds...");
  toggleSolenoid();
  Serial.println("LOCKED");
  Serial.println("Geocache now running...");
}

void loop() {
  // put your main code here, to run repeatedly
  
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
    currentState = opened;
    digitalWrite(LED3, HIGH);
    toggleSolenoid();
   }

  Serial.print("HallSensorLock Status: ");
  Status_HallSensorLock = checkHallSensor(HallSensorLock);
  if (Status_HallSensorLock == 1 && currentState == opened) {
    currentState = start;
    toggleSolenoid();
   }


  Serial.print("Current State: ");
  Serial.println(currentState);
  delay(troubleshootDelay);
}


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


void toggleSolenoid() {
  digitalWrite(Solenoid1, HIGH);
  digitalWrite(Solenoid2, HIGH);
  flashLED10();
  digitalWrite(Solenoid1, LOW);
  digitalWrite(Solenoid2, LOW);
}


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

