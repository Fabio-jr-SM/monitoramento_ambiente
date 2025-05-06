#define pinoAnalog A0  // Pino analógico do sensor de umidade
#define pino5V 7       // Pino que alimenta o sensor

int ValAnalogIn;       // Valor analógico lido do sensor

void setup() {
  Serial.begin(9600);             // Inicializa comunicação serial
  pinMode(pino5V, OUTPUT);        // Define pino de alimentação como saída
  digitalWrite(pino5V, LOW);      // Mantém o sensor desligado inicialmente
}

void loop() {
  // Liga o sensor por curto período
  digitalWrite(pino5V, HIGH);
  delay(10); // Aguarda estabilização

  // Faz leitura média de 10 amostras
  int soma = 0;
  for (int i = 0; i < 10; i++) {
    soma += analogRead(pinoAnalog);
    delay(10);
  }
  ValAnalogIn = soma / 10;

  // Desliga o sensor após leitura
  digitalWrite(pino5V, LOW);

  // Converte valor para porcentagem (ajustar se necessário)
  int Porcento = map(ValAnalogIn, 1023, 0, 0, 100);

  // Exibe valores no monitor serial
  Serial.print("Umidade do solo: ");
  Serial.print(Porcento);
  Serial.println("%");

  delay(1000); // Aguarda 1 segundo antes da próxima leitura
}
