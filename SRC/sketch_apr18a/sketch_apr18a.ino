#define nrOfSteppers 1

const int stepperDirectionPin[nrOfSteppers] = {11};
const int stepperPulsePin[nrOfSteppers] = {10};

int motorSpeed = 500;
String menuselect;

void setup() {
  // put your setup code here, to run once:

  for (int s = 0; s < nrOfSteppers; s++) {
    pinMode(stepperDirectionPin[s], OUTPUT);
    digitalWrite(stepperDirectionPin[s], LOW);
    pinMode(stepperPulsePin[s], OUTPUT);
    digitalWrite(stepperPulsePin[s], LOW);
  }
  Serial.begin(9600);
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
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
