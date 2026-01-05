// #include <I2Cdev.h>
// #include <PID_v1.h>
// #include <MPU6050_6Axis_MotionApps20.h>
#include <Wire.h>

const byte MOTOR_A_PWM = 5;
const byte MOTOR_A_IN1 = 6;
const byte MOTOR_A_IN2 = 7;
const byte MOTOR_B_PWM = 10;
const byte MOTOR_B_IN1 = 9;
const byte MOTOR_B_IN2 = 8;

// PID
float Kp = 50.0, Ki = 0.0, Kd = 0.0;
float error = 0, prev_error = 0, integral = 0;



const int MPU_ADDR = 0x68;

int16_t ax, ay, az;
int16_t gx, gy, gz;


// Setearlos con la calibracion externa. También setear az_offset
int16_t gx_offset = 83, gy_offset = -61, gz_offset = -8;

float roll = 0, pitch = 0, yaw = 0;
float dt;
unsigned long lastTime;




void setup() {
  Wire.begin();
  Serial.begin(9600);

  pinMode(MOTOR_A_PWM, OUTPUT);
  pinMode(MOTOR_A_IN1, OUTPUT);
  pinMode(MOTOR_A_IN2, OUTPUT);
  pinMode(MOTOR_B_PWM, OUTPUT);
  pinMode(MOTOR_B_IN1, OUTPUT);
  pinMode(MOTOR_B_IN2, OUTPUT);

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);


  // Una vez hayamos calibrado, podemos sacar este:
  // calibrateGyro();

  lastTime = millis();
}

void loop() {
  readMPU6050();

  unsigned long now = millis();
  dt = (now - lastTime) / 1000.0;
  lastTime = now;

  float ax_f = ax, ay_f = ay, az_f = az;
  float denominator = sqrt(ay_f * ay_f + az_f * az_f);
  if (denominator < 0.0001) denominator = 0.0001;

  roll = atan2(ay_f, az_f) * 180.0 / PI;
  pitch = atan2(-ax_f, denominator) * 180.0 / PI;
  float gyro_z = (gz - gz_offset) / 131.0; // deg/s
  yaw += gyro_z * dt;

  // === PID ===
  // Cambiar esto con las configuraciones de calibración
  float setpoint = -11;
  error = setpoint - pitch;
  integral += error * dt;
  float derivative = (error - prev_error) / dt;
  float output = Kp * error + Ki * integral + Kd * derivative;
  prev_error = error;

  // Muestra datos
  Serial.print("Pitch: "); Serial.println(pitch);
  // Serial.print("Roll: "); Serial.println(roll);
  // Serial.print("Yaw: "); Serial.println(yaw);


  Serial.print(" | PID output: "); Serial.println(output);

  // Control motor A y B igual por ahora
  moverMotor(output, MOTOR_A_IN1, MOTOR_A_IN2, MOTOR_A_PWM);
  moverMotor(output, MOTOR_B_IN1, MOTOR_B_IN2, MOTOR_B_PWM);

  delay(50);
}

void moverMotor(float salidaPID, byte in1, byte in2, byte pwmPin) {
  int pwm = abs(salidaPID-50);
  if (pwm < 350) pwm = 0;
  if (pwm > 350 && pwm < 450) pwm = 170;
  if (pwm > 650) pwm = 200;

  if (salidaPID > 5) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(pwmPin, pwm);
  } else if (salidaPID < -5) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(pwmPin, pwm);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(pwmPin, 0);
  }

  // Serial.print("PWM enviado: "); Serial.println(pwm);
}

void readMPU6050() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);

  ax = Wire.read() << 8 | Wire.read();
  ay = Wire.read() << 8 | Wire.read();
  az = Wire.read() << 8 | Wire.read();
  Wire.read(); Wire.read(); // Temperatura
  gx = Wire.read() << 8 | Wire.read();
  gy = Wire.read() << 8 | Wire.read();
  gz = Wire.read() << 8 | Wire.read();
}

void calibrateGyro() {
  long sumX = 0, sumY = 0, sumZ = 0;
  const int samples = 100;

  for (int i = 0; i < samples; i++) {
    readMPU6050();
    sumX += gx;
    sumY += gy;
    sumZ += gz;
    delay(5);
  }

  gx_offset = sumX / samples;
  gy_offset = sumY / samples;
  gz_offset = sumZ / samples;
}

