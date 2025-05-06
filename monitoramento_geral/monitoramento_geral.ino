#include <dht.h>

#define pinoUmidadeSolo A0  // Sensor de umidade do solo
#define pino5V 7            // Alimentação do sensor de solo
#define pinoDHT 5           // Pino de dados do DHT22
#define mq135Pin A1         // Sensor de qualidade do ar MQ135

dht DHT;
int ValAnalogIn;

void setup() {
  Serial.begin(9600);
  pinMode(pino5V, OUTPUT);
  digitalWrite(pino5V, LOW); // Sensor de solo desligado inicialmente
}

void loop() {
  Serial.println("===== Monitoramento Ambiental =====");

  // --- Leitura da umidade do solo ---
  digitalWrite(pino5V, HIGH);
  delay(10); // Aguarda estabilização

  int soma = 0;
  for (int i = 0; i < 10; i++) {
    soma += analogRead(pinoUmidadeSolo);
    delay(10);
  }
  ValAnalogIn = soma / 10;
  digitalWrite(pino5V, LOW);

  int umidadeSolo = map(ValAnalogIn, 1023, 0, 0, 100);
  Serial.print("Umidade do solo: ");
  Serial.print(umidadeSolo);
  Serial.println("%");

  // --- Leitura do DHT22 ---
  int chk = DHT.read22(pinoDHT);
  if (chk == DHTLIB_OK) {
    Serial.print("Umidade do ar: ");
    Serial.print(DHT.humidity);
    Serial.println("%");

    Serial.print("Temperatura: ");
    Serial.print(DHT.temperature);
    Serial.println(" °C");
  } else {
    Serial.print("Erro ao ler DHT22: ");
    switch (chk) {
      case DHTLIB_ERROR_CHECKSUM: Serial.println("Erro de checksum"); break;
      case DHTLIB_ERROR_TIMEOUT: Serial.println("Erro de timeout"); break;
      default: Serial.println("Erro desconhecido"); break;
    }
  }

  // --- Leitura da qualidade do ar (MQ135) ---
  int valorSensor = analogRead(mq135Pin);
  String qualidadeDoAr;

  if (valorSensor < 100) {
    qualidadeDoAr = "Excelente";
  } else if (valorSensor < 200) {
    qualidadeDoAr = "Boa";
  } else if (valorSensor < 300) {
    qualidadeDoAr = "Moderada";
  } else if (valorSensor < 400) {
    qualidadeDoAr = "Ruim";
  } else {
    qualidadeDoAr = "Muito Ruim";
  }

  Serial.print("Qualidade do ar (MQ135) - Valor bruto: ");
  Serial.print(valorSensor);
  Serial.print(" - Classificação: ");
  Serial.println(qualidadeDoAr);

  Serial.println("====================================\n");
  delay(2000); // Aguarda 2 segundos antes da próxima leitura
}
