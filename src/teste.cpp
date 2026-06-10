#include <ESP32Servo.h>

Servo servos[6];

int pinos[6] = {13, 12, 14, 27, 26 ,25};

//Algumas letras so para testar

//Letra A
int letraA[6] = {1,0,0,0,0,0};

//Letra B
int letraB[6] = {1,1,0,0,0,0};

int alfabeto[27][6] = {
  {1,0,0,0,0,0}, // A
  {1,1,0,0,0,0}, // B
  {1,0,0,1,0,0}, // C
  {1,0,0,1,1,0}, // D
  {1,0,0,0,1,0}, // E
  {1,1,0,1,0,0}, // F
  {1,1,0,1,1,0}, // G
  {1,1,0,0,1,0}, // H
  {0,1,0,0,1,0}, // I
  {1,0,0,1,1,0}, // J
  {1,0,1,0,0,0}, // K
  {1,1,1,0,0,0}, // L
  {1,0,1,1,0,0}, // M
  {1,0,1,1,1,0}, // N
  {1,0,1,0,1,0}, // O
  {1,1,1,1,0,0}, // P
  {1,1,1,1,1,0}, // Q
  {1,1,1,0,1,0}, // R
  {0,1,1,1,0,0}, // S
  {0,1,1,1,1,0}, // T
  {1,0,1,0,0,1}, // U
  {1,1,1,0,0,1}, // V
  {0,1,0,1,1,1}, // W
  {1,0,1,1,0,1}, // X
  {1,0,1,1,1,1}, // Y
  {1,0,1,0,1,1}  // Z
};

void mostrarLetra(int letra[6]);


void setup() {
  for (int i = 0; i < 6; i++) {
    servos[i].attach(pinos[i]); //Attach the Servo variable to a pin.
  }
}

void loop() {
  mostrarLetra(letraA);
  delay(2000);

  mostrarLetra(letraB);
  delay(2000);
}

void mostrarLetra(int letra[6])
{
  for(int i = 0; i < 6; i++)
  {
    if(letra[i] == 1)
      servos[i].write(50);
    else
      servos[i].write(0);
  }
}
