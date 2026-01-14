// **CÓDIGO SIN LIBRERÍAS WIFI NI CÓDIGO DE SERVIDOR WEB**

// ================= Pines =================
// Motor A (lado izquierdo)
const int AIN1 = 23;
const int AIN2 = 4;
const int PWMA = 22;

// Motor B (lado derecho)
const int BIN1 = 18;
const int BIN2 = 19;
const int PWMB = 21;

// STBY (habilita el TB6612FNG)
const int STBY = 5;

// LEDs (ajústalos si quieres)
const int LED_1 = 32;
const int LED_2 = 26;
const int LED_3 = 33;
const int LED_4 = 25;

// ================= PWM =================
const int pwmFreq = 1000;
const int pwmResolution = 8;
const int pwmChannelA = 0;
const int pwmChannelB = 1;

// Velocidad base (0–255)
int motorSpeed = 180;

// ================= Util LEDs =================
void ledsOff() {

}

// ================= Motores =================
void motorsStop() {

}

void motorsForward() {

}

void motorsBackward() {
 
}

void motorsLeft() { // gira sobre eje: A atrás, B adelante
 
}

void motorsRight() { // gira sobre eje: A adelante, B atrás


// ================= Funciones de Usuario =================
// Función de marcador de posición para "Función 1"
void function1() {
  // **AQUÍ VA EL CÓDIGO PARA LA FUNCIÓN 1**
  ledsOff(); 
  Serial.println("Ejecutando Función 1");
}

// Función de marcador de posición para "Función 2"
void function2() {
  // **AQUÍ VA EL CÓDIGO PARA LA FUNCIÓN 2**
  motorsStop(); 
  Serial.println("Ejecutando Función 2");
}

// ================= Setup =================
void setup() {
  Serial.begin(115200);

// Configuración de Pines
//Definir que tipo de señal son los pines del driver y leds
  

  digitalWrite(STBY, HIGH); // habilitar driver

  // Configurar PWM en ESP32
  ledcSetup(pwmChannelA, pwmFreq, pwmResolution);
  ledcAttachPin(PWMA, pwmChannelA);
  ledcSetup(pwmChannelB, pwmFreq, pwmResolution);
  ledcAttachPin(PWMB, pwmChannelB);

  motorsStop();

  Serial.println("Sistema inicializado. Listo para control serial o por cable.");
}

// ================= Loop =================
void loop() {
  // Este loop está vacío. Puedes añadir aquí la lógica de control.
  // Por ejemplo, leer el puerto serial, usar sensores, o esperar eventos.
}