// DESAFÍO 3 MECATRÓNICA 

#include <Servo.h>

// === Pins ===
const int TRIG_LEFT = 7;
const int ECHO_LEFT = 6;
const int TRIG_RIGHT = 5;
const int ECHO_RIGHT = 4;
const int SERVO_PIN = 3;

// === PID Parameters ===
// Cambiar las constantes del sistema aquí
float Kp = 0.0;
float Ki = 0.0;
float Kd = 0.0;

// === PID Variables ===
float error = 0;
float previous_error = 0;
float integral = 0;

Servo beamServo;

// === Function to measure distance from HC-SR04 ===
float readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // timeout 30ms
  float distance = duration * 0.0343 / 2.0;       // convert to cm
  return distance;
}

void setup() {
  Serial.begin(9600);

  // Setup pins
  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);
  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);

  beamServo.attach(SERVO_PIN);
  beamServo.write(90); // Neutral position (beam level)
}

void loop() {
  // Read distances
  float distLeft = readDistance(TRIG_LEFT, ECHO_LEFT);
  float distRight = readDistance(TRIG_RIGHT, ECHO_RIGHT);

  // Calculate error (positive = ball toward right)
  error = distLeft - distRight;

  // PID computations
  integral += error;
  float derivative = error - previous_error;
  float output = Kp * error + Ki * integral + Kd * derivative;

  // Save current error
  previous_error = error;

  // Map PID output to servo angle (bounded 70–110 degrees)
  int servoAngle = constrain(90 + output, 0, 180);
  beamServo.write(servoAngle);

  // Debug info
  Serial.print("L:"); Serial.print(distLeft);
  Serial.print(" R:"); Serial.print(distRight);
  Serial.print(" E:"); Serial.print(error);
  Serial.print(" OUT:"); Serial.println(servoAngle);

  delay(50); // Loop delay
}
