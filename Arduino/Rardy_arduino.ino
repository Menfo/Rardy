// Rardy
// Arduino code for moving the wheels with a joystick and getting data from an ultrasound sensor

// Wheels one & three = right
// Wheels two & four = left

// Wheel 1 ports
const int in1MotorOne = 22;
const int in2MotorOne = 23;
const int enMotorOne = 2;

// Wheel 2 ports
const int in1MotorTwo = 24;
const int in2MotorTwo = 25;
const int enMotorTwo = 3;

// Wheel 3 ports
const int in1MotorThree = 26;
const int in2MotorThree = 27;
const int enMotorThree = 4;

// Wheel 4 ports
const int in1MotorFour = 28;
const int in2MotorFour = 29;
const int enMotorFour = 5;

// Wheels Variables
int motorSpeed1 = 0;
int motorSpeed2 = 0;
int motorSpeed3 = 0;
int motorSpeed4 = 0;

// Ultrasonic sensor ports
const int trigPin = 52;
const int echoPin = 53;

// Ultrasound sensor variables
long duration;
int distance;


void setup() {
  // Set wheels pin modes
  
  pinMode(in1MotorOne, OUTPUT);
  pinMode(in1MotorTwo, OUTPUT);
  pinMode(in1MotorThree, OUTPUT);
  pinMode(in1MotorFour, OUTPUT);

  pinMode(in2MotorOne, OUTPUT);
  pinMode(in2MotorTwo, OUTPUT);
  pinMode(in2MotorThree, OUTPUT);
  pinMode(in2MotorFour, OUTPUT);

  // Set en (wheels) pin modes
 
  pinMode(enMotorOne, OUTPUT);
  pinMode(enMotorTwo, OUTPUT);
  pinMode(enMotorThree, OUTPUT);
  pinMode(enMotorFour, OUTPUT);

  // Set ultrasonic sensor pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Start serial comunication
  Serial.begin(9600);

}

void loop() {

  
  // Ultrasonic sensor code

  // Send a wave by turning high and low the trigpin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Determines the time that the echo of the echo from the wave has taken
  duration = pulseIn(echoPin, HIGH);

  // s = v * t, being v equals to the sound speed in the air (340 m/s) in microseconds) and dividing it all by 2 because it's an echo
  distance = duration * 0.034 / 2;

  // Prints the distance into the serial
  Serial.println(distance);


  // DC Motors code (base = https://howtomechatronics.com/tutorials/arduino/arduino-dc-motor-control-tutorial-l298n-pwm-h-bridge/)
  
  
  int xAxis = analogRead(A0); // Read Joysticks X-axis
  int yAxis = analogRead(A1); // Read Joysticks Y-axis
 
  // Y-axis used for forward and backward control
  if (yAxis < 470) {
    
    // Set Motor 1 backward
    digitalWrite(in1MotorOne, HIGH);
    digitalWrite(in2MotorOne, LOW);
    // Set Motor 2 backward
    digitalWrite(in1MotorTwo, HIGH);
    digitalWrite(in2MotorTwo, LOW);
    // Set Motor 3 backward
    digitalWrite(in1MotorThree, HIGH);
    digitalWrite(in2MotorThree, LOW);
    // Set Motor 4 backward
    digitalWrite(in1MotorFour, HIGH);
    digitalWrite(in2MotorFour, LOW);
    
    // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeed1 = map(yAxis, 470, 0, 0, 255);
    motorSpeed2 = map(yAxis, 470, 0, 0, 255);
    motorSpeed3 = map(yAxis, 470, 0, 0, 255);
    motorSpeed4 = map(yAxis, 470, 0, 0, 255);
    
  }
  else if (yAxis > 550) {
    
    // Set Motor One forward
    digitalWrite(in1MotorOne, LOW);
    digitalWrite(in2MotorOne, HIGH);
    // Set Motor Two forward
    digitalWrite(in1MotorTwo, LOW);
    digitalWrite(in2MotorTwo, HIGH);
    // Set Motor Three forward
    digitalWrite(in1MotorThree, LOW);
    digitalWrite(in2MotorThree, HIGH);
    // Set Motor Four forward
    digitalWrite(in1MotorFour, LOW);
    digitalWrite(in2MotorFour, HIGH);
    
    // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeed1 = map(yAxis, 550, 1023, 0, 255);
    motorSpeed2 = map(yAxis, 550, 1023, 0, 255);
    motorSpeed3 = map(yAxis, 550, 1023, 0, 255);
    motorSpeed4 = map(yAxis, 550, 1023, 0, 255);
  }
  
  // If joystick stays in middle the motors are not moving
  else {
    motorSpeed1 = 0;
    motorSpeed2 = 0;
    motorSpeed3 = 0;
    motorSpeed4 = 0;
  }

  
  // X-axis used for left and right control
  if (xAxis < 470) {
    
    // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
    int xMapped = map(xAxis, 470, 0, 0, 255);
    
    // Move to left - decrease left motor speed, increase right motor speed
    motorSpeed1 = motorSpeed1 - xMapped;
    motorSpeed2 = motorSpeed2 + xMapped;
    motorSpeed3 = motorSpeed3 - xMapped;
    motorSpeed4 = motorSpeed4 + xMapped;
    
    // Confine the range from 0 to 255
    if (motorSpeed1 < 0) {
      motorSpeed1 = 0;
    }
    if (motorSpeed2 > 255) {
      motorSpeed2 = 255;
    }
    if (motorSpeed3 < 0) {
      motorSpeed3 = 0;
    }
    if (motorSpeed4 > 255) {
      motorSpeed4 = 255;
    }
  }
  
  if (xAxis > 550) {
    
    // Convert the increasing X-axis readings from 550 to 1023 into 0 to 255 value
    int xMapped = map(xAxis, 550, 1023, 0, 255);
    
    // Move right - decrease right motor speed, increase left motor speed
    motorSpeed1 = motorSpeed1 + xMapped;
    motorSpeed2 = motorSpeed2 - xMapped;
    motorSpeed3 = motorSpeed3 + xMapped;
    motorSpeed4 = motorSpeed4 - xMapped;
    
    // Confine the range from 0 to 255
    if (motorSpeed1 > 255) {
      motorSpeed1 = 255;
    }
    if (motorSpeed2 < 0) {
      motorSpeed2 = 0;
    }
    if (motorSpeed3 > 255) {
      motorSpeed3 = 255;
    }
    if (motorSpeed4 < 0) {
      motorSpeed4 = 0;
    }
  }
  
  // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
  if (motorSpeed1 < 70) {
    motorSpeed1 = 0;
  }
  if (motorSpeed2 < 70) {
    motorSpeed2 = 0;
  }
  if (motorSpeed3 < 70) {
    motorSpeed3 = 0;
  }
  if (motorSpeed4 < 70) {
    motorSpeed4 = 0;
  }
  
  analogWrite(enMotorOne, motorSpeed1); // Send PWM signal to motor 1
  analogWrite(enMotorTwo, motorSpeed2); // Send PWM signal to motor 2
  analogWrite(enMotorThree, motorSpeed3); // Send PWM signal to motor 3
  analogWrite(enMotorFour, motorSpeed4); // Send PWM signal to motor 4

  
}




























