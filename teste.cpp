#include <Servo.h>

Servo servos[6];

int pinos[6] = {13, 12, 14, 27, 26 ,25};

//Algumas letras so para testar

//Letra A
int letraA[6] = {1,0,0,0,0,0};

//Letra B
int letraB[6] = {1,1,0,0,0,0};




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
