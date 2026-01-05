// Robot Auto-Equilibrado
#include <PID_v1.h>
#include <LMotorController.h>
#include <I2Cdev.h>
#include <MPU6050_6Axis_MotionApps20.h>

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
 #include "Wire.h"
#endif

#define MIN_ABS_SPEED 30

MPU6050 mpu;

// Variables de control/estado del MPU
bool dmpListo = false;             // será true si la inicialización del DMP fue exitosa
uint8_t estadoIntMPU;              // almacena el byte real de status de interrupción del MPU
uint8_t estadoDev;                 // status devuelto tras cada operación del dispositivo (0 = éxito)
uint16_t tamanoPaquete;            // tamaño esperado del paquete DMP (por defecto 42 bytes)
uint16_t conteoFIFO;               // cantidad de bytes actuales en FIFO
uint8_t bufferFIFO[64];            // buffer de almacenamiento FIFO

// Variables de orientación/movimiento
Quaternion q;                      // [w, x, y, z] contenedor de cuaternión
VectorFloat gravedad;              // [x, y, z] vector gravedad
float ypr[3];                      // [yaw, pitch, roll] contenedor yaw/pitch/roll

// PID
double puntoInicial = 243.0;
double puntoDeseado = puntoInicial;
double offsetAnguloMovimiento = 0.1;
double entrada, salida;

// Ajustar estos valores según tu propio diseño
double Kp = 40;   
double Kd = 0.8;
double Ki = 0;
PID pid(&entrada, &salida, &puntoDeseado, Kp, Ki, Kd, DIRECT);

double factorVelMotorIzq = 1;
double factorVelMotorDer = 1;

// CONTROLADOR DE MOTORES
int ENA = 11;
int IN1 = 7;
int IN2 = 6;
int IN3 = 5;
int IN4 = 4;
int ENB = 10;

LMotorController motorController(
  ENA, IN1, IN2,
  ENB, IN3, IN4,
  factorVelMotorIzq, factorVelMotorDer
);

volatile bool interrupcionMPU = false; // indica si el pin de interrupción del MPU está en alto

void dmpListoCallback()
{
 interrupcionMPU = true;
}

void setup()
{
 Serial.begin(115200);
 
 // unirse al bus I2C (la librería I2Cdev no hace esto automáticamente)
 #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
 Wire.begin();
 TWBR = 24; // reloj I2C a 400 kHz (200 kHz si CPU es 8 MHz)
 #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
 Fastwire::setup(400, true);
 #endif

 mpu.initialize();

 estadoDev = mpu.dmpInitialize();

 // Ingresa aquí tus propios offsets del giroscopio
 mpu.setXGyroOffset(0);
 mpu.setYGyroOffset(0);
 mpu.setZGyroOffset(0);
 mpu.setZAccelOffset(0); // 1688 valor por defecto de fábrica

 // Comprueba si funcionó (devuelve 0 si es así)
 if (estadoDev == 0)
 {
   // Activar el DMP
   mpu.setDMPEnabled(true);

   // habilitar detección de interrupciones en Arduino
   attachInterrupt(0, dmpListoCallback, RISING);
   estadoIntMPU = mpu.getIntStatus();

   // indicar que el DMP está listo
   dmpListo = true;

   // obtener el tamaño del paquete DMP
   tamanoPaquete = mpu.dmpGetFIFOPacketSize();
 
   // Configuración del PID
   pid.SetMode(AUTOMATIC);
   pid.SetSampleTime(10);
   pid.SetOutputLimits(-255, 255); 
 }
 else
 {
   // ERROR
   // 1 = fallo en carga de memoria inicial
   // 2 = fallo en configuraciones del DMP
   Serial.print(F("Fallo en inicialización DMP (código "));
   Serial.print(estadoDev);
   Serial.println(F(")"));
 }
}

void loop()
{
 // si la inicialización falló, no hacer nada
 if (!dmpListo) return;

 // esperar interrupción del MPU o paquetes extra disponibles
 while (!interrupcionMPU && conteoFIFO < tamanoPaquete)
 {
   // sin datos del MPU: ejecutar PID y mover motores
   pid.Compute();
   motorController.move(salida, MIN_ABS_SPEED);
 }

 // resetear la bandera de interrupción
 interrupcionMPU = false;
 estadoIntMPU = mpu.getIntStatus();

 // cantidad actual en FIFO
 conteoFIFO = mpu.getFIFOCount();

 // comprobar overflow (solo ocurre si el código es muy lento)
 if ((estadoIntMPU & 0x10) || conteoFIFO == 1024)
 {
   mpu.resetFIFO();
   Serial.println(F("¡Desbordamiento FIFO!"));
 }
 else if (estadoIntMPU & 0x02)
 {
   // esperar datos suficientes
   while (conteoFIFO < tamanoPaquete) 
       conteoFIFO = mpu.getFIFOCount();

   // leer paquete desde FIFO
   mpu.getFIFOBytes(bufferFIFO, tamanoPaquete);
     // disminuir conteo FIFO
   conteoFIFO -= tamanoPaquete;

   mpu.dmpGetQuaternion(&q, bufferFIFO);
   mpu.dmpGetGravity(&gravedad, &q);
   mpu.dmpGetYawPitchRoll(ypr, &q, &gravedad);

   entrada = ypr[1] * 180/M_PI + 180;
 }
}
