#include <Servo.h>

//------------------------- SENSOR TCS3200 -------------------------
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Calibración (valores referenciales, deben ajustarse)
int redMin = 80, redMax = 279;
int greenMin = 80, greenMax = 320;
int blueMin = 66, blueMax = 264;

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

  // Configurar pines del sensor
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
  digitalWrite(pinRelay, LOW);  // Cinta encendida inicialmente

  // angulo inicial del servo 
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
}

// ------------------------- LOOP -------------------------
void loop() {
  // --- Sección opcional de mostrar valores ---
  /*
  Serial.print("Rojo = ");
  Serial.print(Valor_RGB("rojo"));
  Serial.print(" - Verde = ");
  Serial.print(Valor_RGB("verde"));
  Serial.print(" - Azul = ");
  Serial.println(Valor_RGB("azul"));
  */

  // --- Lógica principal ---
  if (colorDetectado()) {
    digitalWrite(pinRelay, HIGH); // Detener cinta
    delay(50);

    // Obtener valores RGB
    int rojo = Valor_RGB("rojo");
    int verde = Valor_RGB("verde");
    int azul = Valor_RGB("azul");

    // TODO: Implementar lógica de detección y selección de color
    // Ejemplo guía:
    // if (rojo > X && verde > X && azul > X) {
    //   accionarServo("blanco");
    // }

  } else {
    Serial.println("ERROR: No se detecta color válido.");
    digitalWrite(pinRelay, LOW); // Continuar cinta
    delay(100);
  }
}

// ------------------------- FUNCIONES AUXILIARES -------------------------

// Retorna valor RGB para el color especificado
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

// Determina si hay algún color presente (objeto bajo sensor)
bool colorDetectado() {
  int r = Valor_RGB("rojo");
  int g = Valor_RGB("verde");
  int b = Valor_RGB("azul");
  return (r > 0 || g > 0 || b > 0);
}

// Función auxiliar que mueve el servo dado y la cinta transportadora.
void accionarServo(Servo& servo) {
  servo.write(angulo);
  digitalWrite(pinRelay, LOW); // Activar cinta para que objeto caiga
  delay(10000);
  servo.write(angulo - 90);    // Volver a posición inicial
}

