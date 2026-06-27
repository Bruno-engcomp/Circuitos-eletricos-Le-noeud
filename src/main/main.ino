#include <ESP32Servo.h>

// criando o array pra controlar os 6 servos da celula braille
Servo servos[6];

// definindo os pinos
int pinos[6] = {18, 5, 17, 25, 26, 27};
int buzzer = 4;
int microfone = 15;
int botao = 19;

// guarda a última letra recebida
char ultimaLetra = 'A';

// guarda o estado anterior do botão
bool ultimoEstadoBotao = HIGH;

// matriz braille
int alfabeto[26][6] = {
  {1,0,0,0,0,0},
  {1,1,0,0,0,0},
  {1,0,0,1,0,0},
  {1,0,0,1,1,0},
  {1,0,0,0,1,0},
  {1,1,0,1,0,0},
  {1,1,0,1,1,0},
  {1,1,0,0,1,0},
  {0,1,0,0,1,0},
  {0,1,0,1,1,0},
  {1,0,1,0,0,0},
  {1,1,1,0,0,0},
  {1,0,1,1,0,0},
  {1,0,1,1,1,0},
  {1,0,1,0,1,0},
  {1,1,1,1,0,0},
  {1,1,1,1,1,0},
  {1,1,1,0,1,0},
  {0,1,1,1,0,0},
  {0,1,1,1,1,0},
  {1,0,1,0,0,1},
  {1,1,1,0,0,1},
  {0,1,0,1,1,1},
  {1,0,1,1,0,1},
  {1,0,1,1,1,1},
  {1,0,1,0,1,1}
};

int transformarLetraEmIndex(char letra);
void mostrarLetra(int letra[6]);
void bipConfirmacao();

void setup() {

  Serial.begin(115200);

  Serial.println("Digite uma letra de A a Z.");
  Serial.println("Depois pressione o botão.");

  for (int i = 0; i < 6; i++) {
    servos[i].attach(pinos[i]);
    servos[i].write(0);
  }

  pinMode(buzzer, OUTPUT);
  pinMode(botao, INPUT_PULLUP);
}

void loop() {

  // Recebe letra pela Serial
  if (Serial.available()) {

    char letra = toupper(Serial.read());

    if (isAlpha(letra)) {

      ultimaLetra = letra;

      Serial.print("Letra armazenada: ");
      Serial.println(ultimaLetra);

      bipConfirmacao();
    }
  }

  // Detecta clique do botão
  bool estadoAtual = digitalRead(botao);

  if (ultimoEstadoBotao == HIGH && estadoAtual == LOW) {

    int indice = transformarLetraEmIndex(ultimaLetra);

    if (indice >= 0 && indice < 26) {

      Serial.print("Mostrando letra ");
      Serial.println(ultimaLetra);

      mostrarLetra(alfabeto[indice]);
    }

    delay(200); // debounce simples
  }

  ultimoEstadoBotao = estadoAtual;
}

void mostrarLetra(int letra[6]) {

  for (int i = 0; i < 6; i++) {

    if (letra[i] == 1) {

      servos[i].write(180);   // sobe o pino

    } else {

      servos[i].write(0);    // abaixa o pino
    }
  }
  delay(1000);
  for (int i = 0; i < 6; i++)
  {
    servos[i].write(0);
  }
}

int transformarLetraEmIndex(char letra) {
  return letra - 'A';
}

void bipConfirmacao() {
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
}