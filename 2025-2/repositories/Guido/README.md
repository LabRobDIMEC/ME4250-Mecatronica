# Mecatrónica [4250] - Proyecto: Robot Auto-Balancín

> 
> ### 👥 Composición del Proyecto
>
> **🛠️ Integrantes**
> - Agustín Montero
> - Emilio Bergez
> - Luis Rosso
> - Manuel Pérez
>
> **👨‍🏫 Profesor**
> - Harold Valenzuela
>
> **📚 Auxiliar**
> - Fernando Navarrete
>
> **📝 Ayudantes**
> - Fernanda Echevarria
> - Valentina Abarca

## Índice de Contenidos
- [Descripción](#descripción)
- [Objetivos](#objetivos)
- [Avance](#avances)
  - [Avance 1](#avance-1)
  - [Avance 2](#avance-2)
  - [Avance 3](#avance-3)
- [Prototipo](#prototipo)
- [Conclusión](#conclusión)

<hr>

## Descripción

<p align="justify"> 
En este apartado se realiza un pequeño "resumen" de lo que se abordará en este repositorio y los distintos apartados. Entre ellos se plantea inicialmente lo que es nuestro proyecto y los objetivos de él durante el desarrollo de él, posteriormente un apartado de todos los avances y las distintas entregas que se realizaron durante el transcurso del curso, ordenados de un inicio hasta obtener el prototipo completo, donde finalmente hay un apartado donde efectivamente ya está el rpototipo completo, donde se señalan las carpetas ordenadas de los distintos apartados, como los componetnes elctricos, los CAD y los códigos.
</p>
<hr>

## Objetivos
<p align="justify"> 
El objetivo principal de este proyecto es el diseño y construcción de un robot autobalancín funcional. El núcleo del desafío consiste en implementar un controlador **PID (Proporcional-Integral-Derivativo)** para mantener el equilibrio dinámico del sistema.
</p>
<p align="justify">
Para lograr este objetivo, se integrarán componentes mecatrónicos esenciales utilizando un microcontrolador **Arduino UNO** como unidad central de procesamiento. Este gestionará la lógica de control programada en C++ y la comunicación entre los sensores (encargados de medir la inclinación) y los actuadores (motores DC seleccionados para las ruedas). Además, el proyecto incluye el diseño de una **estética original y atractiva** como parte de los requerimientos.
</p>
Es importante definir que el alcance del proyecto se centra en la **integración exitosa de los componentes** y en la **demostración de un sistema de autobalanceo funcional**, priorizando esto sobre la optimización de la eficiencia o el rendimiento del diseño. Por lo tanto, aunque el prototipo pueda presentar ciertas ineficiencias, el objetivo principal radica en la aplicación práctica de los conceptos de control.

<p align="justify">
Todas las especificaciones y requerimientos de diseño se detallan en el documento [**Base**](base.pdf).
</p>
<hr>

## Avances

<p align="justify"> 
Esta sección de avances va mostrando los distintos avances cronologicos que se desarrollan en el curso hasta llegar al prototipo final que corresponde a la última sección de este informe o repositorio.
</p>

### Avance 1

La carpeta [**avance_1**](avance_1) contiene los avances iniciales correspondientes a la primera presentación. En esta etapa se establecieron las bases del robot, implementando las ruedas y motores, junto con soportes diseñados para resistir impactos durante las primeras fases de desarrollo del prototipo. La documentación de esta fase se presenta en el archivo [**Presentación**](avance_1/Presentación.pdf). Las piezas se fabricaron mediante impresión 3D utilizando material PLA.

#### Contenido del avance

- **Prototipos iniciales**: Se desarrollaron dos prototipos, seleccionando el segundo para continuar con el desarrollo. Posteriormente se evaluarán mejoras adicionales según los requerimientos. A continuación se visualiza la imagen del cad utilizado para continuar con los avances del proyecto.

<img src="img/11.jpeg" alt="Motor con Reductora" width="400">

- **Código de movimiento**: Se implementó un programa para el control de movimiento de las ruedas, específicamente diseñado para los **motores DC** del prototipo seleccionado.

<hr>
<details>
  <summary> <b>Código</b> </summary>
  
  ```cpp
#include <Stepper.h>
int stepsPerRevolution = 2048;
int motSpeed = 5;
// Pin al que está conectado el potenciómetro
const int PotPin = A0;

// Variable para almacenar el valor leído del potenciómetro
int PotVal;

Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
Stepper myStepper2(stepsPerRevolution, 4, 6, 5, 7);

void setup() {
  myStepper.setSpeed(motSpeed);
  myStepper2.setSpeed(motSpeed);
}

void loop() {
  for (int i = 0; i < stepsPerRevolution; i++) {
    PotVal = analogRead(PotPin);
    if (PotVal <= 60){
      myStepper.step(-1);      // un paso motor 1
      myStepper2.step(1);     // un paso motor 2
    }
      else { 
        myStepper.step(1);      // un paso motor 1
        myStepper2.step(-1);     // un paso motor 2
    }
  }
}
```

</details>
<hr>


#### Observaciones

<p align="justify"> 
- **Material de las ruedas**: Se recomienda implementar un material rugoso para mejorar la tracción
- **Refuerzos estructurales**: Es necesario añadir soportes en zonas críticas susceptibles a daños por impactos
- **Optimización del motor**: Se propone utilizar el motorreductor amarillo por su ligereza y favorable relación torque/velocidad angular
</p>

<img src="img/reductora.jpg" alt="Motor con Reductora" width="400">

### Avance 2

La carpeta [**avance_2**](avance_2) documenta los progresos correspondientes a la segunda entrega del curso, donde se implementaron cambios significativos tanto en el diseño como en la incorporación de componentes y código. 

En cuanto al diseño estético, se seleccionó al personaje **Guido** de la película Cars, considerándolo ideal y atractivo para el proyecto (*inicialmente se contempló R2D2*). Posteriormente se desarrollará una carcasa personalizada con este diseño. La presentación de estos avances se encuentra en [**Presentación 2**](avance_2/presentación2.pdf).

<img src="img/guido.jpg" alt="Guido" width="400">

#### Contenido del avance:

- **Cambio de Diseño**: Se realizó una revisión completa del diseño inicial, implementando mejoras sustanciales en la configuración mecánica y electrónica del sistema. Se incorporó un portapilas que utiliza cuatro baterías en serie, totalizando aproximadamente 12 voltios, suficiente para el correcto funcionamiento del sistema. Además, se integró un giroscopio que proporciona información sobre la inclinación del sistema, la cual se utilizará posteriormente para la autorregulación mediante un controlador PID.

<img src="img/21.jpeg" alt="Prototipo 2" width="400">

- **Sistema de Propulsión**: Se incorporaron motores DC con caja reductora ("motores amarillos"), seleccionados por su óptima relación torque-velocidad angular y mayor eficiencia energética para aplicaciones de balanceo.

- **Configuración Mecánica**:
  - Implementación de montaje con separadores para evitar interferencias con componentes soldados
  - Adopción de diseño estructural abierto que minimiza el uso de material, mejora la ventilación y facilita el acceso al cableado

- **Electrónica del Sistema**:
  - Control de motores mediante puente H L298N
  - Sensor de movimiento: Módulo GY-521 (MPU-6050)
  - Unidad de control: Arduino Uno
  - Alimentación: Banco de baterías de 12V CC

<img src="img/h.jpg" alt="Puente H" width="400"><img src="img/gyro.jpg" alt="Gyroscopio" width="400">
<img src="img/arduino.jpg" alt="Arduino Uno" width="400"><img src="img/soporte.jpeg" alt="Soporte de Pilas" width="400">

- **Ventajas del Nuevo Diseño**:
  - Mayor eficiencia energética
  - Mejor disipación térmica
  - Accesibilidad para mantenimiento
  - Optimización de peso y materiales

- **Código de Movimiento**:

Se implementaron funciones para controlar el movimiento de los motores, permitiendo el giro de las ruedas en diferentes direcciones. Este código servirá como base para la implementación futura del control PID que permitirá el equilibrio del robot.

<hr>
<details>
  <summary> <b>Código</b> </summary>

```cpp
const int PinIN1 = 7;
const int PinIN2 = A0;
const int PinIN3 = 6;
const int PinIN4 = A1;
 
void setup() {
  // inicializar la comunicación serial a 9600 bits por segundo:
  Serial.begin(9600);
  // configuramos los pines como salida
  pinMode(PinIN1, OUTPUT);
  pinMode(PinIN2, OUTPUT);
  pinMode(PinIN3, OUTPUT);
  pinMode(PinIN4, OUTPUT);
}
// Este loop es sólo para demostrar el funcionamiento de las funciones definidas
void loop() {
  
  MotorHorario();
  Serial.println("Giro del Motor en sentido horario");
  delay(1000);
  
  MotorAntihorario();
  Serial.println("Giro del Motor en sentido antihorario");
  delay(1000);
  
  MotorStop();
  Serial.println("Motor Detenido");
  delay(3000);
  
}
 
//función para girar el motor en sentido horario
void MotorHorario()
{
  digitalWrite (PinIN1, HIGH);
  digitalWrite (PinIN2, LOW);
  digitalWrite (PinIN3, HIGH);
  digitalWrite (PinIN4, LOW);
}

//función para girar el motor en sentido antihorario
void MotorAntihorario()
{
  digitalWrite (PinIN1, LOW);
  digitalWrite (PinIN2, HIGH);
  digitalWrite (PinIN3, LOW);
  digitalWrite (PinIN4, HIGH);
}
 
//función para apagar el motor
void MotorStop()
{
  digitalWrite (PinIN1, LOW);
  digitalWrite (PinIN2, LOW);
  digitalWrite (PinIN3, LOW);
  digitalWrite (PinIN4, LOW);
}
```
</details>
<hr>

- **Código del Sensor**:

Se utilizó el código proporcionado en clases para la lectura del sensor MPU-6050, que proporciona los datos de orientación necesarios para el sistema de control.

<hr>
<details>
  <summary> <b>Código</b> </summary>

```cpp
#include <Wire.h>

const int MPU_ADDR = 0x68;

int16_t ax, ay, az;
int16_t gx, gy, gz;

int16_t gx_offset = 0, gy_offset = 0, gz_offset = 0;

float roll = 0, pitch = 0, yaw = 0;
unsigned long lastTime;
float dt;

void setup() {
  Wire.begin();
  Serial.begin(9600);

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); // Power management
  Wire.write(0);
  Wire.endTransmission(true);

  Serial.println("=== MPU-6050 Calibration ===");
  Serial.println("Place the sensor still and press any key + ENTER to start...");
  while (!Serial.available());  // Wait for user input
  while (Serial.available()) Serial.read();  // Clear input buffer

  calibrateGyro();
  Serial.println("Calibration complete!");

  lastTime = millis();
}

void loop() {
  readMPU6050();

  unsigned long now = millis();
  dt = (now - lastTime) / 1000.0;
  lastTime = now;

  float gyroZ = (gz - gz_offset) / 131.0;
  yaw += gyroZ * dt;

  // Convert int16_t to float
  float ax_f = (float)ax;
  float ay_f = (float)ay;
  float az_f = (float)az;

  // Avoid division by zero
  float denominator = sqrt(ay_f * ay_f + az_f * az_f);
  if (denominator < 0.0001) denominator = 0.0001;

  // Compute angles in degrees
  roll = atan2(ay_f, az_f) * 180.0 / PI;
  pitch = atan2(-ax_f, denominator) * 180.0 / PI;

  // Print angles
  Serial.print("Roll: "); Serial.print(roll, 2);
  Serial.print(" | Pitch: "); Serial.print(pitch, 2);
  Serial.print(" | Yaw: "); Serial.println(yaw, 2);

  delay(100);
}

void readMPU6050() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);

  ax = Wire.read() << 8 | Wire.read();
  ay = Wire.read() << 8 | Wire.read();
  az = Wire.read() << 8 | Wire.read();
  Wire.read(); Wire.read(); // Skip temperature
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
```
</details>
<hr>

#### Observaciones

- **Interruptor de alimentación**: Es importante implementar un switch para evitar el consumo constante de las baterías, permitiendo encender y apagar el sistema según sea conveniente
- **Sistema de fijación**: Las fijaciones a presión son adecuadas para el prototipo actual, pero una implementación modular podría ser una mejora a considerar para el prototipo final, facilitando el desarme y mantenimiento

### Avance 3

La carpeta [**avance_3**](avance_3) ya incorpora los últimos avances del curso, donde se incorpora y se optimiza todo para lograr el objetivo, que es la construcción de este robot auto-balanción. Dentro de ello, se incortpora los códigos necesarios para la incoropracióAquí, adicionalmente se incorpora un vídeo que muestra el proceso de producción de la carcasa a través de la impresora 3D.n del PId, además de la construcción de la carcasa, finalizando finalmente con el prototipo.

#### Contenido del avance

- **Diseño**: Dado por una falla de la placa arduino utilizada previamente, se opta por cambiarla a por otra que corresponde a un **Arduino Mega**, como el que se visualiza en la imagen posterior. Además que se incorpora finalmente la carcasa de nuestro personaje al prototipo anterior, pues más que eso no se realizan cambios significativos más que relacionados a la tolerancia u otros propios de la impresión o detalles de ajuste.

<img src="img/mega.webp" alt="Arduino Mega" width="400"> <img src="img/31.png" alt="Prototipo sin Carcasa" width="400"> <img src="img/32.png" alt="Prototipo con Carcasa" width="400">

Aquí, adicionalmente se incorpora un vídeo que muestra el proceso de producción de la carcasa a través de la impresora 3D.

<img src="img/video(2).gif" alt="Producción de la Carcasa" width="400"> 

- **Código**: Se incorpora un código para el PID, donde se utiliza un código generico y se adaptan los valores de $K_i$ en función de nuestro proyecto. Realmente sólo se va probando  estos valores hasta llegar a un resultado óptimo de nuestro modelo.Cómo se visualiza en el código, los $K_i$ serían $K_p =90$, $K_d =1.8$ y $K_i =0$.

<hr>
<details>
  <summary> <b>Código</b> </summary>

```cpp
//Self Balancing Robot
#include <PID_v1.h>
#include <LMotorController.h>
#include <I2Cdev.h>
#include <MPU6050_6Axis_MotionApps20.h>

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
 #include "Wire.h"
#endif

#define MIN_ABS_SPEED 30

MPU6050 mpu;

// MPU control/status vars
bool dmpReady = false; // set true if DMP init was successful
uint8_t mpuIntStatus; // holds actual interrupt status byte from MPU
uint8_t devStatus; // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize; // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount; // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q; // [w, x, y, z] quaternion container
VectorFloat gravity; // [x, y, z] gravity vector
float ypr[3]; // [yaw, pitch, roll] yaw/pitch/roll container and gravity vector

//PID
double originalSetpoint = 240.0;
double setpoint = originalSetpoint;
double movingAngleOffset = 0.1;
double input, output;

//adjust these values to fit your own design
double Kp = 90;   
double Kd = 1.8;
double Ki = 0;
PID pid(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

double motorSpeedFactorLeft = 0.8;
double motorSpeedFactorRight = 0.8;

//MOTOR CONTROLLER
int ENA = 11;
int IN1 = 7;
int IN2 = 6;
int IN3 = 5;
int IN4 = 4;
int ENB = 10;
LMotorController motorController(ENA, IN1, IN2, ENB, IN3, IN4, motorSpeedFactorLeft, motorSpeedFactorRight);

volatile bool mpuInterrupt = false; // indicates whether MPU interrupt pin has gone high
void dmpDataReady()
{
 mpuInterrupt = true;
}


void setup()
{
 // join I2C bus (I2Cdev library doesn't do this automatically)
 #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
 Wire.begin();
 TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
 #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
 Fastwire::setup(400, true);
 #endif

 mpu.initialize();

 devStatus = mpu.dmpInitialize();

 // supply your own gyro offsets here, scaled for min sensitivity
 mpu.setXGyroOffset(0);
 mpu.setYGyroOffset(0);
 mpu.setZGyroOffset(0);
 mpu.setZAccelOffset(0); // 1688 factory default for my test chip

 // make sure it worked (returns 0 if so)
 if (devStatus == 0)
 {
 // turn on the DMP, now that it's ready
 mpu.setDMPEnabled(true);

 // enable Arduino interrupt detection
 attachInterrupt(0, dmpDataReady, RISING);
 mpuIntStatus = mpu.getIntStatus();

 // set our DMP Ready flag so the main loop() function knows it's okay to use it
 dmpReady = true;

 // get expected DMP packet size for later comparison
 packetSize = mpu.dmpGetFIFOPacketSize();
 
 //setup PID
 pid.SetMode(AUTOMATIC);
 pid.SetSampleTime(10);
 pid.SetOutputLimits(-255, 255); 
 }
 else
 {
 // ERROR!
 // 1 = initial memory load failed
 // 2 = DMP configuration updates failed
 // (if it's going to break, usually the code will be 1)
 Serial.print(F("DMP Initialization failed (code "));
 Serial.print(devStatus);
 Serial.println(F(")"));
 }
}


void loop()
{
 // if programming failed, don't try to do anything
 if (!dmpReady) return;

 // wait for MPU interrupt or extra packet(s) available
 while (!mpuInterrupt && fifoCount < packetSize)
 {
 //no mpu data - performing PID calculations and output to motors 
 pid.Compute();
 motorController.move(output, MIN_ABS_SPEED);
 
 }

 // reset interrupt flag and get INT_STATUS byte
 mpuInterrupt = false;
 mpuIntStatus = mpu.getIntStatus();

 // get current FIFO count
 fifoCount = mpu.getFIFOCount();

 // check for overflow (this should never happen unless our code is too inefficient)
 if ((mpuIntStatus & 0x10) || fifoCount == 1024)
 {
 // reset so we can continue cleanly
 mpu.resetFIFO();
 Serial.println(F("FIFO overflow!"));

 // otherwise, check for DMP data ready interrupt (this should happen frequently)
 }
 else if (mpuIntStatus & 0x02)
 {
 // wait for correct available data length, should be a VERY short wait
 while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

 // read a packet from FIFO
 mpu.getFIFOBytes(fifoBuffer, packetSize);
 
 // track FIFO count here in case there is > 1 packet available
 // (this lets us immediately read more without waiting for an interrupt)
 fifoCount -= packetSize;

 mpu.dmpGetQuaternion(&q, fifoBuffer);
 mpu.dmpGetGravity(&gravity, &q);
 mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
 input = ypr[1] * 180/M_PI + 180;
 }
}
```


</details>
<hr>

## Prototipo

Bueno, como se mencionó al inicio del documento, acá se reordenan los documentos utilizados y obtenidos para que el usuario pueda utilizarlos o visualizar a libre disposición. Se presenta a continuación el resultadado del proceso, con su respectivo CAD e imagen real, los resultados en general se encuentran en la carpeta  [**Prototipo**](prototipo), donde se encuentran los cads del modelo, el código y los componentes electricos. Y además una carpeta donde se encuentra todo el material audivisual, tales como imagenes y fotos, en la carpeta [**Imagenes**](img)

<img src="img/1.jpeg" alt="Foto 1" width="250"> <img src="img/2.jpeg" alt="Foto 2" width="250"> <img src="img/3.jpeg" alt="Foto 3" width="250">
<img src="img/31.png" alt="Cad 1" width="300"> <img src="img/32.png" alt="Cad 2" width="300">

El código del robot para el controlador Arduino, el cual se encuentra en la carpeta [**Código**](prototipo/codigo.ino), donde el archivo se llama literalmente "código". Este incorpora todo lo aprendido en el proceso de avances, tanto como el funcionamiento de las ruedas dado unos motores DC, la estabilización con el giroscopio y el equilibrio incorporado gracias al PID.

<hr>
<details>
<summary> <b>Código</b> </summary>
  
```cpp
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
```
</details>
<hr>

Bueno, al final se tiene el Diagrama de Conexiones del proyecto en la carpeta [**Prototipo**](prototipo) en formato .pdf, que representa el esquemq de las conexiones del proyecto, dónde se específica particularmente el cableado.

## Conclusión

El desarrollo de este robot auto-balancín permitió validar la aplicación práctica de la teoría de control en un sistema mecatrónico real. A pesar de los desafíos encontrados, como la necesidad de reemplazar el microcontrolador por uno de mayor capacidad (Arduino Mega) y el proceso iterativo de sintonización del PID, se logró un robot auto-balancin capaz de mantener el equilibrio de forma autónoma.

El diseño inspirado en el personaje Guido aportó un valor estético diferenciador sin comprometer la funcionalidad mecánica. Como trabajo futuro, se sugiere la implementación de un sistema de alimentación más robusto (BMS) y la optimización del código para mejorar la velocidad de respuesta ante perturbaciones externas.
