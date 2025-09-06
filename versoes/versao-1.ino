long readUltrasonicDistance(int triggerPin, int echoPin){
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

int range = 150;
bool ativo(long sensor){
  return sensor > 0 && sensor <= range;
}

int ledEntrada = 12;
int ledSaida = 13;
long S1 = 0;
long S2 = 0;
bool S1ativo = false;
bool S2ativo = false;

long auxTempo = 0;

// Ações
bool entrada = false;
bool saida = false;

int primeiro = 0;
int segundo = 0;

int alunos = 0;

void setup() {
  pinMode(ledEntrada, OUTPUT); // <-- Sinalização Entrada
  pinMode(ledSaida, OUTPUT); // <-- Sinalização Saída
  Serial.begin(9600);
}

void loop() {
  // Atualiza sensores
  leituraSensores();

  Serial.print(primeiro);
  Serial.print(segundo);

  acao(primeiro, segundo);
  sinalizarLed(entrada, saida);

  Serial.print(alunos);

  //resetOrdem();
  delay(2000);
}

// Atualiza status dos sensores e define primeiro/segundo
void leituraSensores(){
  S1 = 0.01723 * readUltrasonicDistance(7, 7);
  S2 = 0.01723 * readUltrasonicDistance(8, 8);

  S1ativo = ativo(S1);
  S2ativo = ativo(S2);
  
  // Define primeiro
  if(S1ativo && primeiro == 0) primeiro = 1;
  if(S2ativo && primeiro == 0) primeiro = 2;

  // Define segundo
  if(S2ativo && primeiro == 1) segundo = 2;
  if(S1ativo && primeiro == 2) segundo = 1;
}

bool acao(int primeiro, int segundo){
  if(primeiro == 1){
    alunos ++;
    return entrada = true;
  }
  if(primeiro == 2){
    alunos--;
    return saida = true;
  }
}

// Acende LEDs
void sinalizarLed(bool entrada, bool saida){
  if(auxTempo == 0){
    auxTempo = millis();
  }

  digitalWrite(ledEntrada, entrada ? HIGH : LOW);
  digitalWrite(ledSaida, saida ? HIGH : LOW);

  reset();

  if(millis() >= auxTempo + 400){
    digitalWrite(ledEntrada, LOW);
    digitalWrite(ledSaida, LOW);
    auxTempo = 0;
  }
}

void reset(){
  primeiro = 0;
  segundo = 0;
  entrada = false;
  saida = false;
}
