const int STEP_PIN = 3;
const int DIR_PIN = 2;
const int EN_PIN = 4;
const int trigPin = 9;
const int echoPin = 10;
float duration, distance;
const int object_in = 8;

const int STEPS_PER_REV = 200;
const int MICROSTEPS = 10;
const int DELAY_US = 100;

double tower_height_bottom_limit = 21.5;
double tower_height_top_limit = 20.5;

int userInput=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(object_in, INPUT);

  digitalWrite(EN_PIN, LOW); 
  Serial.begin(9600);
  Serial.println("Stepper Motor Control Ready");
  Serial.println("Enter a number from 1 to 4: ");
}

void loop() {
  if (Serial.available() > 0) {
    
    // Look for the next valid integer in the serial stream
    userInput = Serial.parseInt(); 

    // Clear any leftover newline characters (\n) from pressing Enter
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
  
    if(userInput == 1){
  // put your main code here, to run repeatedly:
  Serial.println("Rotating forward...");
  rotateMotor(true, STEPS_PER_REV * MICROSTEPS);
  //delay(2000);
    }
  else if(userInput == 2) {
  Serial.println("Rotating backward...");
  rotateMotor(false, STEPS_PER_REV * MICROSTEPS);
  //delay(2000);
  }
  else if(userInput == 3){
    check_distance();
    delay(700);
  }
  else if(userInput == 4){
    analyze_vertical();
  }
  else{
    digitalWrite(STEP_PIN, LOW);
    delay(1000);
  }
}



void analyze_vertical(){
    int distance = check_distance();
    if(distance < tower_height_top_limit){
      Serial.println("Rotating forward...");
      rotateMotor(true, STEPS_PER_REV * MICROSTEPS);
    }
    else if(distance > tower_height_bottom_limit){
      Serial.println("Rotating backward...");
      rotateMotor(false, STEPS_PER_REV * MICROSTEPS);
    }
    else{
      String message = "Finished vertical movement at height: " + String(check_distance());
      Serial.println(message);
      userInput = 0;
    }
    
}

int photo_coupler(){
  int value = digitalRead(object_in); // Read HIGH (1) or LOW (0)
  Serial.print("Digital value: ");
  Serial.println(value);
  return value;
}

double check_distance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = ((duration*340)/2)/10000;
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}

void rotateMotor(bool direction, int steps) {
  digitalWrite(DIR_PIN, direction ? HIGH : LOW);
  
  for (int i=0; i<steps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(DELAY_US);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(DELAY_US);
  }
}
