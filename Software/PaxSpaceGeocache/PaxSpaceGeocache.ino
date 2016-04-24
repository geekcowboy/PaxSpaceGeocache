#define HallSensor1 0
#define HallSensor2 1
#define HallSensor3 2
#define HallSensorLock 3

#define Solenoid1 8
#define Solenoid2 9

#define LED 13

#define HallOnOff 100

int Status_HallSensor1 = 0;
int Status_HallSensor2 = 0;
int Status_HallSensor3 = 0;
int Status_HallSensorLock = 0;

enum State {
  initialized,
  letter1,
  letter2,
  opened
};

State currentState;


int checkHallSensor(int sensorNum);
void openBox();
void closeBox();

void setup() {
  // put your setup code here, to run once:
  pinMode(Solenoid1, OUTPUT);
  pinMode(Solenoid2, OUTPUT);

  digitalWrite(Solenoid1, LOW);
  digitalWrite(Solenoid2, LOW);

  Serial.begin(9600);
  Serial.println("Geocache running...");

  digitalWrite(LED, LOW);

  currentState = initialized;

}

void loop() {
  // put your main code here, to run repeatedly
  
  Serial.print("HallSensor1 Status: ");
  Status_HallSensor1 = checkHallSensor(HallSensor1);
  if (Status_HallSensor1 == 1 && currentState == initialized) {
    currentState = letter1;
   }

  Serial.print("HallSensor2 Status: ");
  Status_HallSensor2 = checkHallSensor(HallSensor2);
  if (Status_HallSensor2 == 1 && currentState == letter1) {
    currentState = letter2;
   }

  Serial.print("HallSensor3 Status: ");
  Status_HallSensor3 = checkHallSensor(HallSensor3);
  if (Status_HallSensor3 == 1 && currentState == letter2) {
    currentState = opened;
    openBox();
   }

  Serial.print("HallSensorLock Status: ");
  Status_HallSensorLock = checkHallSensor(HallSensorLock);
  if (Status_HallSensorLock == 1 && currentState == opened) {
    currentState = initialized;
    closeBox();
   }

  Serial.print("Current State: ");
  Serial.println(currentState);
  delay(3000);
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


void openBox() {
  digitalWrite(LED, HIGH);
  digitalWrite(Solenoid1, HIGH);
  digitalWrite(Solenoid2, HIGH);
  delay(5000);
  digitalWrite(Solenoid1, LOW);
  digitalWrite(Solenoid2, LOW);
}

void closeBox() {
  digitalWrite(LED, LOW);
  digitalWrite(Solenoid1, HIGH);
  digitalWrite(Solenoid2, HIGH);
  delay(5000);
  digitalWrite(Solenoid1, LOW);
  digitalWrite(Solenoid2, LOW);
}

