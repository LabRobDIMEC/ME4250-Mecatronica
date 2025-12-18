/*
  Robot Auto-Balancín "SEGWAY MONKEY" - Control PID
  Motores: 2 x NEMA17 con drivers tipo A3967/A4988
  Izquierdo en pines 2 (STEP) y 3 (DIR)
  Derecho en pines 6 (STEP) y 8 (DIR) 
  Plotter: angle, setpoint, pidOutput
*/

#include <Wire.h>
#include <MPU6050.h>
#include <AccelStepper.h>

// ====== CONFIGURACIÓN DE MOTORES ======

#define L_STEP 11   // STEP motor izquierdo
#define R_STEP 6   // STEP motor derecho
#define L_DIR  10  // DIR motor izquierdo
#define R_DIR  8   // DIR motor derecho

AccelStepper motorL(AccelStepper::DRIVER, L_STEP, L_DIR);
AccelStepper motorR(AccelStepper::DRIVER, R_STEP, R_DIR);

const float MAX_SPEED = 1500.0;   
const float MAX_ACCEL = 2000.0;   

// ====== CONFIGURACIÓN SENSOR (MPU6050) ======
MPU6050 mpu;

int16_t ax, ay, az;
int16_t gx, gy, gz;

long offsetAx, offsetAy, offsetAz;
long offsetGx, offsetGy, offsetGz;

float angle = 0.0;
float angleAcc = 0.0;
float angleGyro = 0.0;
unsigned long previousTime = 0;
const float alpha = 0.98;  // filtro complementario

// ====== PID ======
float setpoint = 0.0;  
float Kp = 300.0;
float Ki = 1.0;
float Kd = 170;

float error, lastError = 0;
float integral = 0;
float derivative;
float pidOutput;
const float MAX_PID_OUTPUT = 1200.0; 

const bool INVERT_ANGLE = false;

// ====== FUNCIONES ======
void calibrarMPU() {
  const int N = 500;
  offsetAx = offsetAy = offsetAz = 0;
  offsetGx = offsetGy = offsetGz = 0;

  for (int i = 0; i < N; i++) {
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    offsetAx += ax;
    offsetAy += ay;
    offsetAz += az;
    offsetGx += gx;
    offsetGy += gy;
    offsetGz += gz;
    delay(3);
  }

  offsetAx /= N;
  offsetAy /= N;
  offsetAz = (offsetAz / N) - 16384.0;  // Compensa gravedad (1g)
  offsetGx /= N;
  offsetGy /= N;
  offsetGz /= N;

  Serial.println("Calibracion MPU lista.");
}

void leerAngulo() {
  unsigned long currentTime = millis();
  float dt = (currentTime - previousTime) / 1000.0;
  if (dt <= 0) dt = 0.001;
  previousTime = currentTime;

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // quitar offset
  ax -= offsetAx;
  ay -= offsetAy;
  az -= offsetAz;
  gx -= offsetGx;
  gy -= offsetGy;
  gz -= offsetGz;

  angleAcc = atan2(-(float)ax, (float)az) * 180.0 / PI;

  angleGyro = angle + ((float)gy / 131.0) * dt;

  angle = alpha * angleGyro + (1 - alpha) * angleAcc;

  // invertir signo si está corrigiendo al revés
  if (INVERT_ANGLE) {
    angle = -angle;
  }
}

void aplicarPID() {
  error = setpoint - angle;

  integral += error;
  if (integral > 1000) integral = 1000;
  if (integral < -1000) integral = -1000;

  derivative = error - lastError;
  lastError = error;

  pidOutput = Kp * error + Ki * integral + Kd * derivative;

  if (pidOutput > MAX_PID_OUTPUT) pidOutput = MAX_PID_OUTPUT;
  if (pidOutput < -MAX_PID_OUTPUT) pidOutput = -MAX_PID_OUTPUT;

  motorL.setSpeed(pidOutput);
  motorR.setSpeed(pidOutput);
}

// ====== SETUP ======
void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Inicialización de motores
  motorL.setMaxSpeed(MAX_SPEED);
  motorR.setMaxSpeed(MAX_SPEED);
  motorL.setAcceleration(MAX_ACCEL);
  motorR.setAcceleration(MAX_ACCEL);

  // Inicializar MPU6050
  Serial.println("Iniciando MPU...");
  mpu.initialize();
  if (mpu.testConnection()) {
    Serial.println("MPU detectado. Calibrando...");
    delay(500);
    calibrarMPU();
  } else {
    Serial.println("No se detecta MPU.");
  }

  previousTime = millis();
}

// ====== LOOP ======
void loop() {
  leerAngulo();   
  aplicarPID();  

  
  motorL.runSpeed();
  motorR.runSpeed();


  Serial.print(angle);  
  Serial.print("\t");
  Serial.print(setpoint);
  Serial.print("\t");
  Serial.println(pidOutput);

}
