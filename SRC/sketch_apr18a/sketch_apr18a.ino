#define BLYNK_PRINT Serial
#define ESP8266_BAUD 9600
#define BLYNK_TEMPLATE_ID "TMPLw_qpjb4o"
#define BLYNK_DEVICE_NAME "MMPFishrobot"
#define nrOfSteppers 1
#define encoderA 2
#define encoderB 3

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>

const int stepperDirectionPin[nrOfSteppers] = {11};
const int stepperPulsePin[nrOfSteppers] = {10};

int motorSpeed = 500;
String menuselect;

//Blynk auth code
char auth[] = "p86vJfZq6gdOe6wOPgWEcw93mAwO5-1A";

//Wifi login information
char ssid[] = "G5Zone"; //You can replace the wifi name to your wifi
char pass[] = "";  //Type password of your wifi.

SoftwareSerial EspSerial(2, 3); // RX, TX
WidgetLCD lcd(V0);

ESP8266 wifi(&EspSerial);

void setup() {
  // put your setup code here, to run once:
  for (int s = 0; s < nrOfSteppers; s++) {
    pinMode(stepperDirectionPin[s], OUTPUT);
    digitalWrite(stepperDirectionPin[s], LOW);
    pinMode(stepperPulsePin[s], OUTPUT);
    digitalWrite(stepperPulsePin[s], LOW);
  }

  Serial.begin(9600);
  delay(10);

  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);

}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();

  /*
    Serial.println("---Welcome to fishrobot fish tail tester---");
    Serial.println(" 1 --- Start motor");
    Serial.println(" 2 --- Set motor speed");
    Serial.println(" 3 --- Move one roation");
    Serial.println(" 4 --- Move manually");
    Serial.println(" 0 --- Menu");
    for (;;) {
    switch (Serial.read()) {
      case '1':
        for (int i = 0; i < 20; i++) {
          stepper(0, 100, 1, motorSpeed);
          stepper(0, 200, 0, motorSpeed);
          stepper(0, 100, 1, motorSpeed);
        }
        Serial.println("Stopped");
        break;
      case '2':
        setMotorSpeed();
        break;
      case '3':
        stepper(0, 400, 1, motorSpeed);
        Serial.println("Stopped");
        break;
      case'4':
        manualControll();
      case'0': return;
      default: continue;
    }
    }
  */
}

BLYNK_WRITE(V0) {
  int pinValue = param.asInt();
  if (pinValue < 0) {
    for (int i = 0; i < 20; i++) {
      stepper(0, 100, 1, motorSpeed);
      stepper(0, 200, 0, motorSpeed);
      stepper(0, 100, 1, motorSpeed);
    }
    Serial.println("Stopped");
  }
}
BLYNK_WRITE(V1) {
  int pinValue = param.asInt();
  if (pinValue < 0) {
    stepper(0, 400, 1, motorSpeed);
    Serial.println("Stopped");
  }
}
BLYNK_WRITE(V2) {
  int pinValue = param.asInt();
  if (pinValue < 0) {
    stepper(0, 1, 1, motorSpeed);
  }
}
BLYNK_WRITE(V3) {
  int pinValue = param.asInt();
  if (pinValue < 0) {
    stepper(0, 1, 0, motorSpeed);
  }
}

void stepper(int motor, int steps, boolean stepDirection, int Speed) {
  int currentDirection = digitalRead(stepperDirectionPin[motor]);
  if (stepDirection != currentDirection) {
    digitalWrite(stepperDirectionPin[motor], stepDirection);
    delay(100);
  }
  for (int s = 0; s < steps; s++) {
    digitalWrite(stepperPulsePin[motor], LOW);
    digitalWrite(stepperPulsePin[motor], HIGH);
    delayMicroseconds(Speed);
  }
}

void setMotorSpeed() {
  Serial.flush();
  Serial.println("Current speed: ");
  Serial.println(motorSpeed);
  Serial.println("Set speed:  ");
  while (Serial.available() == 0) {}
  int y = Serial.parseInt();
  if (y > 349) {
    motorSpeed = y;
    Serial.println("Speed set to");
    Serial.println(motorSpeed);
  } else {
    Serial.println("Speed not set");
  }
}
void manualControll() {
  Serial.println("1 --- Clockwise");
  Serial.println("2 --- Anti-clockwise");
  Serial.println("0 --- Menu");
  for (;;) {
    switch (Serial.read()) {
      case'1':
        stepper(0, 1, 1, 500);
        break;
      case'2':
        stepper(0, 1, 0, 500);
        break;
      case'0': return;
      default: continue;
    }
  }
}
