#define BLYNK_PRINT Serial
#define ESP8266_BAUD 9600
#define BLYNK_TEMPLATE_ID "TMPLw_qpjb4o"
#define BLYNK_DEVICE_NAME "MMPFishrobot"
#define nrOfSteppers 2

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>

const int stepperDirectionPin[nrOfSteppers] = {11, 13};
const int stepperPulsePin[nrOfSteppers] = {10, 12};

int motorSpeed = 500;
String inputString = "";
SimpleTimer timer;

WidgetLED led1(V5);
WidgetLED led2(V12);
WidgetTerminal terminal(V6);

//Blynk auth code
char auth[] = "p86vJfZq6gdOe6wOPgWEcw93mAwO5-1A";

//Wifi login information
char ssid[] = "G5Zone"; //You can replace the wifi name to your wifi
char pass[] = "";  //Type password of your wifi.
bool connecteToBlynk = false;

SoftwareSerial EspSerial(2, 3); // RX, TX
WidgetLCD lcd(V0);

ESP8266 wifi(&EspSerial);

void setup() {
  // put your setup code here, to run once:
  led2.off();
  Serial.begin(9600);
  delay(10);

  for (int s = 0; s < nrOfSteppers; s++) {
    pinMode(stepperDirectionPin[s], OUTPUT);
    digitalWrite(stepperDirectionPin[s], LOW);
    pinMode(stepperPulsePin[s], OUTPUT);
    digitalWrite(stepperPulsePin[s], LOW);
  }
  Blynk.virtualWrite(V4, motorSpeed);

  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);


}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  led2.on();
  timer.run();
  
}
void Sent_serial() {
  // Sent serial data to Blynk terminal - Unlimited string readed
  String content = "";  //null string constant ( an empty string )
  char character;
  while (Serial.available()) {
    character = Serial.read();
    content.concat(character);

  }
  if (content != "") {
    Blynk.virtualWrite (V2, content);
  }
}

BLYNK_WRITE(V0) {

  int pinValue = param.asInt();
  if (pinValue == 1) {
    led1.on();
    for (int i = 0; i < 20; i++) {
      stepper(0, 100, 1, motorSpeed);
      stepper(1, 100, 0, motorSpeed);
      stepper(0, 200, 0, motorSpeed);
      stepper(1, 200, 1, motorSpeed);
      stepper(0, 100, 1, motorSpeed);
      stepper(1, 100, 0, motorSpeed);
    }
    Serial.println("Stopped");
  }
  led1.off();
}
BLYNK_WRITE(V1) {
  int pinValue = param.asInt();
  if (pinValue == 1) {
    led1.on();
    stepper(0, 400, 1, motorSpeed);
    Serial.println("Stopped");
  }
  led1.off();
}
BLYNK_WRITE(V2) {
  int pinValue = param.asInt();
  if (pinValue == 1) {
    led1.on();
    stepper(0, 1, 1, 2000);
  }
  led1.off();
}
BLYNK_WRITE(V3) {
  int pinValue = param.asInt();
  if (pinValue == 1) {
    led1.on();
    stepper(0, 1, 0, 2000);
  }
  led1.off();
}

BLYNK_WRITE(V7) {
  Blynk.setProperty(V7, "step", 50);

  int pinValue = param.asInt();
  Serial.println(pinValue);

  if (pinValue >= 350 <= 3000) {
    motorSpeed = pinValue;
  }
  Blynk.virtualWrite(V4, motorSpeed);
}
BLYNK_WRITE(V8) {
  int pinValue = param.asInt();
  if (pinValue == 1) {
    motorSpeed = 500;
    Blynk.virtualWrite(V4, motorSpeed);
  }
}
BLYNK_WRITE(V9) {
  int pinValue = param.asInt();
  if (pinValue == 1) {
    motorSpeed = 1000;
    Blynk.virtualWrite(V4, motorSpeed);
  }
}
BLYNK_WRITE(V10) {
  int pinValue = param.asInt();
  if (pinValue == 1) {
    motorSpeed = 1500;
    Blynk.virtualWrite(V4, motorSpeed);
  }
}
BLYNK_WRITE(V11) {
  int pinValue = param.asInt();
  if (pinValue == 1) {
    motorSpeed = 2000;
    Blynk.virtualWrite(V4, motorSpeed);
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
