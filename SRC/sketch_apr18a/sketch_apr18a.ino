#define nrOfSteppers 1

const int stepperDirectionPin[nrOfSteppers] = {11};
const int stepperPulsePin[nrOfSteppers] = {10};



void setup() {
  // put your setup code here, to run once:
/*  pinMode(pulPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enblPin, OUTPUT);

  digitalWrite(pulPin, LOW);
  digitalWrite(enblPin, LOW);
   digitalWrite(dirPin, LOW);

  Serial.begin(9600);
  Serial.println("init");

  digitalWrite(enblPin, HIGH);
  delay(100);
  digitalWrite(enblPin, LOW);
*/
for (int s=0; s<nrOfSteppers; s++){
  pinMode(stepperDirectionPin[s], OUTPUT);
  digitalWrite(stepperDirectionPin[s], LOW);
  pinMode(stepperPulsePin[s], OUTPUT);
  digitalWrite(stepperPulsePin[s], LOW);
}

Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  stepper(0,250,1,2500);
  stepper(0,250,0,5000);

Serial.println("---");

}

void stepper(int motor,int steps, boolean stepDirection, int Speed){
  int currentDirection = digitalRead(stepperDirectionPin[motor]);
  if(stepDirection != currentDirection){
    digitalWrite(stepperDirectionPin[motor], stepDirection);
    delay(100);
    }
  for(int s=0; s<steps; s++){
    digitalWrite(stepperPulsePin[motor],LOW);
    digitalWrite(stepperPulsePin[motor], HIGH);
    delayMicroseconds(Speed);
    }
}
