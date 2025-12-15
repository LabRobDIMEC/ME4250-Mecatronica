#-----------------------------**WORK IN PROGRESS**------------------------------#

# 🤖 ME4250 - Curso de Mecatrónica

¡Bienvenido al repositorio central del curso de Mecatrónica **ME4250**!

Este espacio recopila el conocimiento, los códigos y la documentación generada a lo largo de los semestres. Aquí encontrarás tanto los desafíos técnicos como los proyectos finales desarrollados por los estudiantes, sirviendo como una base de conocimiento colaborativa.

---

## 📚 Ejes del Curso

El curso se estructura sobre **cuatro pilares fundamentales** que permiten la integración completa de sistemas mecatrónicos:

1.  **Microcontroladores:** El cerebro del sistema (Arduino, ESP32, STM32, etc.).
2.  **Actuadores:** Elementos que generan movimiento y acción física.
3.  **Sensores:** La percepción del entorno y recolección de datos.
4.  **Control PID:** La lógica matemática para gobernar el sistema con precisión.

---

## 🚀 Metodología: Aprendizaje Incremental

La particularidad de este curso es que **el aprendizaje es progresivo**. El proyecto principal no se realiza al final, sino que se construye a lo largo del semestre a medida que se profundiza en la materia.

Para dominar cada uno de los ejes temáticos, el curso cuenta con **3 Desafíos o Plataformas** específicas antes de la integración final:

### 1. Actuadores: Control de Motores ⚙️
En este desafío nos enfocamos en el movimiento. Se trabaja con distintos tipos de motores (DC, Stepper, Servos) y drivers para entender las curvas de potencia, precisión y torque.
* *Ubicación: Carpeta `/Desafios/Actuadores`*

### 2. Sensores: Color Sorting (Clasificación) 🎨
Aquí el foco es la percepción. Se implementan sistemas capaces de detectar y diferenciar objetos basados en colores, integrando lógica de decisión en tiempo real.
* *Ubicación: Carpeta `/Desafios/Sensores`*

### 3. Control: Ball and Beam ⚖️
El desafío definitivo de control. Se utiliza una plataforma de "Bola y Viga" para implementar y sintonizar lazos de control **PID**, logrando estabilizar un sistema inherentemente inestable.
* *Ubicación: Carpeta `/Desafios/PID`*

---

## 📂 Estructura del Repositorio

Este repositorio está organizado para facilitar la navegación entre los desafíos técnicos y los proyectos finales de cada generación.

```text
ME4250-Mecatronica/
│
├── 📂 Desafios/                # Código base y ejemplos de las 3 plataformas
│   ├── 01_Actuadores_Motores
│   ├── 02_Sensores_Sorting
│   └── 03_Control_BallAndBeam
│
├── 📂 Proyectos_Otoño_2025/    # Temática: Carros Balancines (Péndulo Invertido)
│   ├── M0-V
│   ├── Circus
│   ├── Man On Wire
│   └── Pengusurf Club
│
├── 📂 Proyectos_Semestre_X/    # Próximos proyectos
│
└── README.md
