#define nrOfSteppers 1

const int stepperDirectionPin[nrOfSteppers] = {11};
const int stepperPulsePin[nrOfSteppers] = {10};

int motorSpeed;
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
  Serial.println("---Welcome to fishrobot fish tail tester---");
  Serial.println(" 1 --- Start motor");
  Serial.println(" 2 --- Set motor speed");
  Serial.println(" 3 --- Set to home position");
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available())
  {
    menuselect = Serial.readStringUntil('\n');
    if (menuselect.equals("1"))
    {
      for (int i = 0; i < 20; i++) {
        stepper(0, 200, 1, motorSpeed);
        stepper(0, 200, 0, motorSpeed);
      }
    }
    else if (menuselect.equals("2"))
    {
      Serial.println("Set speed:  ");
      delay(1000);
      int y = Serial.parseInt();
      if (y > 349) {
        motorSpeed = y;
        Serial.println("Speed set to");
        Serial.println(motorSpeed);
      }
      else
      {
        Serial.println("Current motor speed:  ");
        Serial.println(motorSpeed);
      }

    }
    else if (menuselect.equals("3"))
    {

    }
    else {
      Serial.println("Invalid command");
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
