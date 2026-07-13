#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SDA_PIN 8
#define SCL_PIN 9

#define BOTAO 15

Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver(0x40);

// limites do servo (ajuste se necessário)
#define SERVO_MIN 120
#define SERVO_MAX 500

// ângulos
#define ANGULO_BAIXO 0
#define ANGULO_ALTO 50

// canais do PCA9685
const uint8_t canaisServos[6] = {0, 1, 2, 3, 4, 5};

// matriz Braille
const int alfabeto[26][6] = {
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

uint16_t anguloParaPWM(int angulo)
{
    return map(angulo, 0, 180, SERVO_MIN, SERVO_MAX);
}

void moverServo(uint8_t canal, int angulo)
{
    pca.setPWM(canal, 0, anguloParaPWM(angulo));
}

void mostrarLetra(const int letra[6])
{
    for (int i = 0; i < 6; i++)
    {
        if (letra[i])
            moverServo(canaisServos[i], ANGULO_ALTO);
        else
            moverServo(canaisServos[i], ANGULO_BAIXO);
    }
}

int transformarLetra(char c)
{
    c = toupper(c);

    if (c < 'A' || c > 'Z')
        return -1;

    return c - 'A';
}

void setup()
{
    Serial.begin(115200);

    Wire.begin(SDA_PIN, SCL_PIN);

    pca.begin();
    pca.setPWMFreq(50);

    pinMode(BOTAO, INPUT_PULLUP);

    delay(500);

    Serial.println();
    Serial.println("=================================");
    Serial.println("CELULA BRAILLE");
    Serial.println("Digite uma letra de A ate Z");
    Serial.println("=================================");

    for(int i=0;i<6;i++)
        moverServo(canaisServos[i], ANGULO_BAIXO);
}

void loop()
{
    if (Serial.available())
    {
        char letra = Serial.read();

        if (isalpha(letra))
        {
            int indice = transformarLetra(letra);

            if(indice >= 0)
            {
                Serial.print("Letra recebida: ");
                Serial.println((char)toupper(letra));

                mostrarLetra(alfabeto[indice]);
            }
        }
    }

    // botão para recolher todos os pinos
    if(digitalRead(BOTAO)==LOW)
    {
        delay(30);

        if(digitalRead(BOTAO)==LOW)
        {
            for(int i=0;i<6;i++)
                moverServo(canaisServos[i], ANGULO_BAIXO);

            Serial.println("Celula resetada.");

            while(digitalRead(BOTAO)==LOW);
        }
    }
}