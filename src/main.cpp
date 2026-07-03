s#include <ESP32Servo.h>

// criando o array pra controlar os 6 servos da celula braille
Servo servos[6];

// definindo os pinos de dados de cada servo no esp32
int pinos[6] = {27, 26, 25, 13, 12, 14};
// pino do buzzer para dar o aviso sonoro
int buzzer = 4;
// pino que vai ler o sinal do microfone no futuro (reservado)
int microfone = 15;
// pino do botao que a gente usa para testar manualmente
int botao = 33;

// matriz com o alfabeto braille completo de a a z.
int alfabeto[26][6] = {
  {1,0,0,0,0,0}, // letra a
  {1,1,0,0,0,0}, // letra b
  {1,0,0,1,0,0}, // letra c
  {1,0,0,1,1,0}, // letra d
  {1,0,0,0,1,0}, // letra e
  {1,1,0,1,0,0}, // letra f
  {1,1,0,1,1,0}, // letra g
  {1,1,0,0,1,0}, // letra h
  {0,1,0,0,1,0}, // letra i
  {1,0,0,1,1,0}, // letra j
  {1,0,1,0,0,0}, // letra k
  {1,1,1,0,0,0}, // letra l
  {1,0,1,1,0,0}, // letra m 
  {1,0,1,1,1,0}, // letra n
  {1,0,1,0,1,0}, // letra o
  {1,1,1,1,0,0}, // letra p
  {1,1,1,1,1,0}, // letra q
  {1,1,1,0,1,0}, // letra r
  {0,1,1,1,0,0}, // letra s 
  {0,1,1,1,1,0}, // letra t
  {1,0,1,0,0,1}, // letra u
  {1,1,1,0,0,1}, // letra v
  {0,1,0,1,1,1}, // letra w
  {1,0,1,1,0,1}, // letra x
  {1,0,1,1,1,1}, // letra y
  {1,0,1,0,1,1}  // letra z
};

// declarando as funcoes aqui em cima pro compilador saber que elas existem
int transformarLetraEmIndex(char letra);
void mostrarLetra(int letra[6]);
void bipConfirmacao();

void setup() {
  // abrindo a comunicacao serial na velocidade padrao
  Serial.begin(115200);
  Serial.println("--- modulo braille pronto para receber comando de voz ---");
  Serial.println("simule o comando de voz digitando uma letra (a-z) no terminal:");

  // mapeando e ligando cada um dos 6 servos no seu pino correspondente
  for (int i = 0; i < 6; i++) {
    servos[i].attach(pinos[i]);
  }

  // configurando o pino do buzzer como saida de sinal
  pinMode(buzzer, OUTPUT);
  // configurando o botao como entrada (caso queira usar pra testar)
  pinMode(botao, INPUT_PULLUP);
}

void loop() {
  // fica checando se o "reconhecedor de voz" mandou alguma letra pela serial
  if (Serial.available() > 0) {
    char letraRecebida = Serial.read();
    
    // ignora comandos de quebra de linha comuns de terminais (\n ou \r)
    if (isAlpha(letraRecebida)) {
      // transforma em maiuscula pra bater com o calculo da matriz
      char letraMaiuscula = toupper(letraRecebida);
      // calcula qual a linha dessa letra na matriz
      int index = transformarLetraEmIndex(letraMaiuscula);

      // se a letra for valida (de a a z), executa o comando
      if (index >= 0 && index <= 25) {
        Serial.print("[comando de voz recebido] exibindo em braille a letra: ");
        Serial.println(letraMaiuscula);
        
        // da o aviso sonoro de sucesso e move a celula braille
        bipConfirmacao();
        mostrarLetra(alfabeto[index]);
      }
    }
  }
}

// funcao que varre o array da letra e bota os motores na posicao certa
void mostrarLetra(int letra[6]) {
  for(int i = 0; i < 6; i++) {
    // se for 1 na matriz, o motor gira 50 graus pra subir o pino
    if(letra[i] == 1)
      servos[i].write(50);
    // se for 0, o motor volta pra 0 graus pro pino abaixar
    else
      servos[i].write(0);
  }
}

// faz a conta usando a tabela ascii pra transformar a letra no indice da matriz.
int transformarLetraEmIndex(char letra) {
  return letra - 65; 
}

// funcao basica pra dar um pulso de energia no buzzer e fazer ele apitar por 100ms
void bipConfirmacao() {
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
}