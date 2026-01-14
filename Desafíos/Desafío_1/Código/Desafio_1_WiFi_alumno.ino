#include <WiFi.h>
#include <WebServer.h>

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

// ================= WiFi =================
// Insertar el nombre de su red WiFi
const char* ssid = "";
const char* password = "";

// Servidor web en el puerto 80
WebServer server(80);

// ================= HTML (WASD + Flechas) =================
const char* html = R"rawliteral(
<!DOCTYPE html>
<html>
<head><meta name="viewport" content="width=device-width, initial-scale=1", meta charset="UTF-8">
<style>
 body{font-family:system-ui,Segoe UI,Roboto,Arial;margin:16px}
 button{padding:16px 18px;font-size:18px;margin:8px;border-radius:10px}
 .grid{display:grid;gap:8px;grid-template-columns:repeat(3,120px);justify-content:center;margin-top:16px}
 .kbd{padding:2px 6px;border:1px solid #ddd;border-radius:6px;background:#f7f7f7}
</style>
</head>
<body>
<h2>Desafío 1: "Fats & Rats"</h2>
<h3>Mecatrónica ME4250</h3>
<p>Usa <span class="kbd">W</span> <span class="kbd">A</span> <span class="kbd">S</span> <span class="kbd">D</span> o las flechas. <span class="kbd">Space</span> = Stop</p>

<div class="grid">
 <div></div>
 <button onclick="send('forward')">⏩ Adelante</button>
 <div></div>

 <button onclick="send('left')">⬅️ Izquierda</button>
 <button onclick="send('stop')">⏹ Stop</button>
 <button onclick="send('right')">➡️ Derecha</button>

 <div></div>
 <button onclick="send('backward')">⏪ Atrás</button>
 <div></div>
</div>

<p>Velocidad: <span id="v">180</span>
 <input id="spd" type="range" min="0" max="255" value="180" oninput="chgSpeed(this.value)">
</p>

<hr> <div class="grid" style="grid-template-columns: repeat(2, 1fr);">
    <button onclick="send('function1')">💡 Función 1</button>
    <button onclick="send('function2')">⚙️ Función 2</button>
</div>

<script>
 const v = document.getElementById('v');
 function send(cmd){ fetch('/' + cmd).catch(()=>{}); }
 function chgSpeed(val){ v.textContent = val; fetch('/speed?val=' + val).catch(()=>{}); }

 // Teclado: WASD y flechas
 const mapDown = {
  'w':'forward','W':'forward','ArrowUp':'forward',
  's':'backward','S':'backward','ArrowDown':'backward',
  'a':'left','A':'left','ArrowLeft':'left',
  'd':'right','D':'right','ArrowRight':'right',
  ' ':'stop'
 };
 const pressed = new Set();
 window.addEventListener('keydown',(e)=>{
  if(!(e.key in mapDown)) return;
  if(!pressed.has(e.key)){
   pressed.add(e.key);
   send(mapDown[e.key]);
  }
  e.preventDefault();
 },{passive:false});
 window.addEventListener('keyup',(e)=>{
  if(!(e.key in mapDown)) return;
  pressed.delete(e.key);
  if(e.key !== ' '){ send('stop'); }
  e.preventDefault();
 },{passive:false});
</script>
</body>
</html>
)rawliteral";

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

void motorsLeft() {// gira sobre eje: A atrás, B adelante

}

void motorsRight() {// gira sobre eje: A adelante, B atrás

}

// ================= Funciones extras =================

void function1() {
 // **AQUÍ VA EL CÓDIGO PARA LA FUNCIÓN 1**
 ledsOff(); // Detener LED
 Serial.println("Ejecutando Función 1");
}


void function2() {
 // **AQUÍ VA EL CÓDIGO PARA LA FUNCIÓN 2**
 motorsStop(); // Ejemplo: detener motores
 Serial.println("Ejecutando Función 2");
}

// ================= Setup =================
void setup() {
 Serial.begin(115200);

// definir el tipo de señal para los pines del driver y los leds


 digitalWrite(STBY, HIGH); // habilitar driver

// Configurar PWM en ESP32

 ledcSetup(pwmChannelA, pwmFreq, pwmResolution);
 ledcAttachPin(PWMA, pwmChannelA);
 ledcSetup(pwmChannelB, pwmFreq, pwmResolution);
 ledcAttachPin(PWMB, pwmChannelB);

 motorsStop();

// Conexión WiFi (a tu router)
 WiFi.begin(ssid, password);
 Serial.print("Conectando a WiFi");
 while (WiFi.status() != WL_CONNECTED) {
  delay(400);
  Serial.print(".");
 }
 Serial.println("\nConectado. IP: ");
 Serial.println(WiFi.localIP());

// Rutas HTTP
 server.on("/", [](){ server.send(200, "text/html", html); });

 server.on("/forward", [](){ motorsForward(); server.send(200,"text/plain","Forward"); });
 server.on("/backward", [](){ motorsBackward(); server.send(200,"text/plain","Backward"); });
 server.on("/left", [](){ motorsLeft(); server.send(200,"text/plain","Left"); });
 server.on("/right", [](){ motorsRight(); server.send(200,"text/plain","Right"); });
 server.on("/stop", [](){ motorsStop(); server.send(200,"text/plain","Stop"); });

 // **Nuevas rutas para las funciones 1 y 2**
 server.on("/function1", [](){ function1(); server.send(200,"text/plain","Function 1 executed"); });
 server.on("/function2", [](){ function2(); server.send(200,"text/plain","Function 2 executed"); });

// Cambiar velocidad desde el slider
 server.on("/speed", [](){
  if (server.hasArg("val")) {
   motorSpeed = constrain(server.arg("val").toInt(), 0, 255);
  }
  server.send(200, "text/plain", String(motorSpeed));
 });

 server.begin();
 Serial.println("Servidor HTTP listo.");
}

// ================= Loop =================
void loop() {
 server.handleClient();
}