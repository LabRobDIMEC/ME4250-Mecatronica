#include <Servo.h>

//------------------------- SENSOR TCS3200 -------------------------
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Calibración (ajustar según pruebas individuales)
int redMin = 77, redMax = 119;
int greenMin = 85, greenMax = 167;
int blueMin = 73, blueMax = 140;

//------------------------- ACTUADORES -------------------------
Servo servo1;  // Blanco
Servo servo2;  // Verde
Servo servo3;  // Azul
Servo servo4;  // Negro

#define pinServo1 3
#define pinServo2 9
#define pinServo3 10
#define pinServo4 11
#define pinRelay 12

int angulo = 90;  // Ángulo de activación

// ------------------------- SETUP -------------------------
void setup() {
  Serial.begin(9600);

  // Configurar pines sensor
  pinMode(S0, OUTPUT); digitalWrite(S0, HIGH);
  pinMode(S1, OUTPUT); digitalWrite(S1, LOW);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Inicializar servos y relay
  servo1.attach(pinServo1);
  servo2.attach(pinServo2);
  servo3.attach(pinServo3);
  servo4.attach(pinServo4);
  pinMode(pinRelay, OUTPUT);
  digitalWrite(pinRelay, LOW);  // Cinta encendida

  // angulo inicial del servo 
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
}

// ------------------------- LOOP -------------------------
void loop() {
  if (colorDetectado()) {
    digitalWrite(pinRelay, HIGH); // Detener cinta
    delay(50); // Estabilizar lectura

    int rojo = Valor_RGB("rojo");
    int verde = Valor_RGB("verde");
    int azul = Valor_RGB("azul");
    Serial.print(rojo);
    Serial.print("-");
    Serial.print(verde);
    Serial.print("-");
    Serial.println(azul);


    // Clasificación por color
    if (rojo > 200 && verde > 200 && azul > 200) {
      Serial.println("COLOR BLANCO DETECTADO");
      accionarServo(servo1);
    }
    else if (verde > rojo + 30 && verde > azul + 30 && verde > 80) {
      Serial.println("COLOR VERDE DETECTADO");
      accionarServo(servo2);
    }
    else if (azul > rojo + 30 && azul > verde + 30 && azul > 80) {
      Serial.println("COLOR AZUL DETECTADO");
      accionarServo(servo3);
    }
    else if (rojo <60 && verde < 60 && azul < 60) {
      Serial.println("COLOR NEGRO DETECTADO");
      accionarServo(servo4);
    }
    else {
      Serial.println("COLOR NO CLASIFICADO");
      digitalWrite(pinRelay, LOW);
      delay(50);
    }
  } else {
    Serial.println("ERROR: No se detecta color.");
    digitalWrite(pinRelay, LOW); // Continuar cinta
    delay(100);
  }
}

// ------------------------- FUNCIONES -------------------------

int Valor_RGB(String color) {
  int r, g, b;

  // Rojo
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  int redPW = pulseIn(sensorOut, LOW);
  redPW = constrain(redPW, redMin, redMax);
  r = constrain(map(redPW, redMin, redMax, 255, 0), 0, 255);
  delay(200);

  // Verde
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  int greenPW = pulseIn(sensorOut, LOW);
  greenPW = constrain(greenPW, greenMin, greenMax);
  g = constrain(map(greenPW, greenMin, greenMax, 255, 0), 0, 255);
  delay(200);

  // Azul
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  int bluePW = pulseIn(sensorOut, LOW);
  bluePW = constrain(bluePW, blueMin, blueMax);
  b = constrain(map(bluePW, blueMin, blueMax, 255, 0), 0, 255);
  delay(200);

  if (color == "rojo") return r;
  if (color == "verde") return g;
  if (color == "azul") return b;
  return 0;
}

bool colorDetectado() {
  int r = Valor_RGB("rojo");
  int g = Valor_RGB("verde");
  int b = Valor_RGB("azul");
  return (r > 0 || g > 0 || b > 0);
}

void accionarServo(Servo& servo) {
  servo.write(angulo);
  digitalWrite(pinRelay, LOW); // Activar cinta para que objeto caiga
  delay(10000);
  servo.write(angulo - 90);    // Volver a posición inicial
}
