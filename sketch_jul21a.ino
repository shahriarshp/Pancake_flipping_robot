int dir=4;
int en=2;
int steps=3;
int steps_total=20000;
int delay_between_steps=100;
int trigPin=5;
int echoPin=6;
float duration, distance;
float dis;
int direction_state;

void setup() {
  // put your setup code here, to run once:
  pinMode(dir, OUTPUT);
  pinMode(en, OUTPUT);
  pinMode(steps, OUTPUT);
  digitalWrite(en, HIGH);
 // digitalWrite(dir, HIGH);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  delay(4000);
}

void loop() {
  // put your main code here, to run repeatedly:
  dis = sensor();
  if(dis<20){
  //  Serial.println("dis is less than 16");
    direction_state=1;
    digitalWrite(en, LOW);
    digitalWrite(dir, HIGH);
    steppermotor();
  }
  else if (dis > 24){
    Serial.println("dis is greater than 20");
    direction_state=2;
    digitalWrite(en, LOW);
    digitalWrite(dir, LOW);
    steppermotor();
  }
  else{
    Serial.println("dis is in range");
    direction_state=3;
    digitalWrite(en, HIGH);
  }
  delay(1000);
}

float sensor(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = ((duration*340)/2)/10000;
  Serial.print("Distance:");
  Serial.println(distance);
  return distance;
}

void steppermotor(){
    for(int i=0; i<steps_total; i++){
    digitalWrite(steps, HIGH);
    delayMicroseconds(delay_between_steps);
    digitalWrite(steps, LOW);
    delayMicroseconds(delay_between_steps);
  }
  //delayMicroseconds(10);
  //delay(1000);
}
