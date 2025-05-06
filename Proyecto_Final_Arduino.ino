#include <SoftwareSerial.h>

// Bluetooth: RX en 8, TX en 7 (sin conflicto con motores)
SoftwareSerial BT(8, 7); // RX, TX

// Motores
int motorL1 = 5;  // IN1 (izquierdo)
int motorL2 = 6;  // IN2 (izquierdo)
int motorR1 = 9;  // IN3 (derecho)
int motorR2 = 10; // IN4 (derecho)

char dataFromApp = 'S';  // Comando inicial (detener)

void setup() {
  Serial.begin(9600);  // Monitor serie (opcional)
  BT.begin(9600);      // Bluetooth HC-05

  // Configura los pines de los motores como salida
  pinMode(motorL1, OUTPUT);  
  pinMode(motorL2, OUTPUT);
  pinMode(motorR1, OUTPUT);
  pinMode(motorR2, OUTPUT);  

  Serial.println("Carro listo. Esperando comandos...");
}

void loop() {
  // Leer datos del Bluetooth
  if (BT.available()) {
    dataFromApp = BT.read();  // Lee el comando enviado desde la app o PC
    Serial.print("Comando recibido: ");
    Serial.println(dataFromApp);
  }

  // Ejecutar acción según comando recibido
  switch (dataFromApp) {
    case 'U': up(); break;       // Comando para avanzar
    case 'D': down(); break;     // Comando para retroceder
    case 'L': left(); break;     // Comando para girar a la izquierda
    case 'R': right(); break;    // Comando para girar a la derecha
    case 'S': stop(); break;     // Comando para detenerse
    default: stop(); break;      // Si el comando es desconocido, se detiene
  }

  delay(20);  // Pequeña espera para evitar sobrecargar el procesador
}

// Función para avanzar
void up() {
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, HIGH);
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, HIGH);    
}

// Función para retroceder
void down() {
  digitalWrite(motorL1, HIGH);
  digitalWrite(motorL2, LOW);
  digitalWrite(motorR1, HIGH);
  digitalWrite(motorR2, LOW);
}

// Función para girar a la derecha
void right() {
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, HIGH);
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, LOW);
}

// Función para girar a la izquierda
void left() {
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, LOW);
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, HIGH);
}

// Función para detenerse
void stop() {
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, LOW);
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, LOW); 
}
