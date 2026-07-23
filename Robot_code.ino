// declare stepper motor pin numbers here
int DIR_PIN = 0;
int STEP_PIN = 1;
int en_pin_base = 2;
int en_pin_vertical = 3;
int en_pin_horizontal = 4;
int en_pin_flip = 5;

// declare number of steps per each stepper motor phase
int steps_for_base = 100;
int steps_for_vertical = 800;
int steps_for_horizontal = 100;
int steps_for_flip = 100;

// declare delay between steps
int delay_steps_base = 500;
int delay_steps_vertical = 100;
int delay_steps_horizontal = 500;
int delay_steps_flip = 500;

// declare UltraSonic sensors variables here
int trigPin = 10;
int echo_pin_base = 6;
int echo_pin_vertical = 7;
int echo_pin_horizontal = 8;
int echo_pin_flip = 9;
float duration, distance;
float measured_distance;

// declare vertical move variables
float robot_height = 12.5;

// declare other variables
int userInput;

void setup(){
	pinMode(DIR_PIN, OUTPUT);
	pinMode(STEP_PIN, OUTPUT);
	pinMode(en_pin_base, OUTPUT);
	pinMode(en_pin_vertical, OUTPUT);
	pinMode(en_pin_horizontal, OUTPUT);
	pinMode(en_pin_flip, OUTPUT);
	pinMode(trigPin, OUTPUT);
	pinMode(echo_pin_base, INPUT);
	pinMode(echo_pin_vertical, INPUT);
	pinMode(echo_pin_horizontal, INPUT);
	pinMode(echo_pin_flip, INPUT);

	digitalWrite(en_pin_base, HIGH);
	digitalWrite(en_pin_vertical, HIGH);
	digitalWrite(en_pin_horizontal, HIGH);
	digitalWrite(en_pin_flip, HIGH);
	Serial.begin(9600);

	Serial.print("The Robot is ready!\n enter the task number from the options below.\n");
	Serial.println("[16-19]: Display distance by reading ULtraSonic sensor value. First digit should 1, second digit is the sensor number in the robot.");
	Serial.println("2: base rotation");
	Serial.println("3: vertical movement");
	Serial.println("4: horizontal movement");
	Serial.println("5: flip movement");
	Serial.println("6: Move robot to the desired height.");
}

void loop(){
	if (Serial.available() > 0) { //in loop function
    userInput = Serial.parseInt(); 
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
	if(userInput>10 && userInput < 20){
		measured_distance = ultrasonic_sensor(userInput%10);
    Serial.print("Distance: ");
    Serial.println(measured_distance);
	}
	else if(userInput == 2){ // base rotation
		digitalWrite(en_pin_base, LOW);
		digitalWrite(DIR_PIN, HIGH);
		rotate_motor(steps_for_base, delay_steps_base);
	}
	else if(userInput == 3){ // vertical movement
		digitalWrite(en_pin_vertical, LOW);
		digitalWrite(DIR_PIN, HIGH);
		rotate_motor(steps_for_vertical, delay_steps_vertical);
	}
	else if(userInput == 4){ // horizontal movement
		digitalWrite(en_pin_horizontal, LOW);
		digitalWrite(DIR_PIN, HIGH);
		rotate_motor(steps_for_horizontal, delay_steps_horizontal);
	}
	else if(userInput == 5){ // flip movement
		digitalWrite(en_pin_flip, LOW);
		digitalWrite(DIR_PIN, HIGH);
		rotate_motor(steps_for_flip, delay_steps_flip);
	}
	else if(userInput == 6){ // automatic vertical movement
		measured_distance = ultrasonic_sensor(echo_pin_vertical);
		if(measured_distance < robot_height - 0.3){
			digitalWrite(en_pin_vertical, LOW);
			digitalWrite(DIR_PIN, HIGH);
			rotate_motor(steps_for_vertical, delay_steps_vertical);
		}
		else if(measured_distance > robot_height + 0.3){
			digitalWrite(en_pin_vertical, LOW);
			digitalWrite(DIR_PIN, LOW);
			rotate_motor(steps_for_vertical, delay_steps_vertical);
		}
		else{
			measured_distance = ultrasonic_sensor(echo_pin_vertical);
    	Serial.print("Robot height is: ");
    	Serial.println(measured_distance);
			digitalWrite(en_pin_vertical, HIGH);
			userInput = 0;
		}
	}
	else{
		digitalWrite(en_pin_base, HIGH);
		digitalWrite(en_pin_vertical, HIGH);
		digitalWrite(en_pin_horizontal, HIGH);
		digitalWrite(en_pin_flip, HIGH);
		digitalWrite(trigPin, LOW);
	}
}

float ultrasonic_sensor(int echoPin){
	digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);

  duration = pulseIn(echoPin, HIGH);
  distance = ((duration*340)/2)/10000;
  //Serial.print("Distance: ");
  //Serial.println(distance);
	return distance;
}

void rotate_motor(int steps, int delay_between_steps){
	  for (int i=0; i<steps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(delay_between_steps);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(delay_between_steps);
  }
}
