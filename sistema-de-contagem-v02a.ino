/*
 * people-counting-system-v0-2a.ino
 *
 * Algorithm created on September 11, 2025.
 *
 * Author: João Henrique (GitHub: joaohgp-dev)
 *
 * Description: This algorithm counts and prints on an SPI display the number of people in a defined space using ultrasonic sensors.
 *
 */

#include <SPI.h> // Importa a biblioteca SPI
#include <TFT.h> // Importa a biblioteca TFT
#include <Ultrasonic.h> // Importa a biblioteca Ultrasonic

// Instânciando constantes dos pinos
// Constantes de pinos do HC-SR04 (lado da sala)
const uint8_t SENS_SALA_TRIG_PIN = 2; // Define o pino 'Trig' do HC-SR04(sala) como 2
const uint8_t SENS_SALA_ECHO_PIN = 3; // Define o pino 'Echo' do HC-SR04(sala) como 3

// Constantes de pinos do HC-SR04 (lado do corredor)
const uint8_t SENS_CORRE_TRIG_PIN = 4; // Define o pino 'Trig' do HC-SR04(corredor) como 4
const uint8_t SENS_CORRE_ECHO_PIN = 5; // Define o pino 'Echo' do HC-SR04(corredor) como 5

// Constantes de pinos do display
const uint8_t CS = 10; // Define o pino 'CS' do display como 10
const uint8_t DC = 9; // Define o pino 'DC' do display como 9
const uint8_t RESET = 8; // Define o pino 'RESET' do display como 8

// Constantes do programa
const uint8_t LIMITE_DISTANCIA = 150; // Define o valor limite de distância para considerar uma presença

// Instânciando variáveis
// Variáveis do HC-SR04 (lado da sala)
bool presencaNaSala; // Define a variável responsável por armazenar a presença de uma pessoa no HC-SR04 da sala

// Variáveis do HC-SR04 (lado do corredor)
bool presencaNoCorre; // Define a variável responsável por armazenar a presença de uma pessoa no HC-SR04 do corredor

// Variáveis do programa
uint8_t contador = 0; // Inicia a variável 'contador' responsável por armazenar o a quantidade de pessoas na sala com o valor 0

// Instânciando objetos
// Instânciando HC-SR04 (lado da sala)
Ultrasonic ultrasonicSala(SENS_SALA_TRIG_PIN, SENS_SALA_ECHO_PIN); // Instância o objeto do HC-SR04 (lado da sala)

// Instânciando HC-SR04 (lado do corredor)
Ultrasonic ultrasonicCorre(SENS_CORRE_TRIG_PIN, SENS_CORRE_ECHO_PIN); // Instância o objeto do HC-SR04 (lado do corredor)

// Instânciando display SPI
TFT screen = TFT(CS, DC, RESET); // Instância o objeto do display SPI

// Código executado
// Executa o bloco de código uma vez no início do programa
void setup() {
  iniciarDisplay(); // Inicia e prepara o display
}

// Executa o bloco de código repetidamente após o 'setup()'
void loop() {
// leituraDosSensores(); // Atualiza o valor das variáveis 'presencaNaSala' e 'presencaNoCorre'
// atualizarDisplay(); // Atualiza o valor da contagem na tela
}

void iniciarDisplay() {
  screen.begin(); // Inicia o display
  screen.background(0, 0, 0); // Define a cor do fundo da tela como preto
  screen.stroke(255, 255, 255); // Define a cor do texto e linhas como branco
  screen.text("Quantidade de alunos", 10, 10); // Imprime o texto nas coordenadas (10, 10)
  screen.text("na sala:", 10, 20); // Imprime o texto nas coordenadas (10, 20)
}

// void leituraDosSensores() {
//   digitalWrite(SENS_SALA_TRIG_PIN, HIGH);
//   digitalWrite(SENS_CORRE_TRIG_PIN, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(SENS_SALA_TRIG_PIN, LOW);
//   digitalWrite(SENS_CORRE_TRIG_PIN, LOW);
//   delayMicroseconds(2);
//   presencaNaSala = ultrasonicSala.read(CM);
//   presencaNaCorre = ultrasonicCorre.read(CM);
// }

void atualizarDisplay() {
  screen.stroke(255, 255, 255); // Define a cor do texto e linhas como branco
  screen.text(String(contador).c_str(), 60, 20); // Imprime o valor do contador na tela nas coordenadas (60, 20)
  delay(1000); // Pausa a execução por 1 segundo
  screen.stroke(0, 0, 0); // Define a cor do texto e linhas como preto
  screen.text(String(contador).c_str(), 60, 20); // Imprime o valor do contador na tela nas coordenadas (60, 20)
}