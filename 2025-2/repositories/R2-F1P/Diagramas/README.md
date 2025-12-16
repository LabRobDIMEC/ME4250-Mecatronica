# Diagramas del proyecto

Esta carpeta contiene:

## Diagrama esquemático electrónico
Incluye:
- Conexión del Arduino UNO  
- Controlador A4988/Easydriver  
- Sensor MPU6050  
- PCB personalizada  
- Distribución de alimentación de 12V  

Formato: `.pdf` y `.png`

---

## Diagrama de control automático
Diagrama de flujo del sistema de control:

1. Lectura IMU (acelerómetro + giroscopio)  
2. Filtro complementario  
3. Cálculo del error angular  
4. PID → salida de control  
5. Ajuste de velocidad de motores  
6. Retroalimentación hacia la IMU  

Este diagrama describe la lógica interna del robot.
