#include <dht.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>

// LCD I2C
LiquidCrystal_I2C lcd(0x27, 20, 4);

#define pinoUmidadeSolo A0  // Sensor de umidade do solo
#define pino5V 7            // Alimentação do sensor de solo
#define pinoDHT 5           // Pino de dados do DHT22
#define mq135Pin A1         // Sensor de qualidade do ar MQ135

dht DHT;
int ValAnalogIn;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

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
  float umidadeAr = 0;
  float temperatura = 0;
  if (chk == DHTLIB_OK) {
    umidadeAr = DHT.humidity;
    temperatura = DHT.temperature;

    Serial.print("Umidade do ar: ");
    Serial.print(umidadeAr);
    Serial.println("%");

    Serial.print("Temperatura: ");
    Serial.print(temperatura);
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

  // --- Atualiza o LCD ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Solo: ");
  lcd.print(umidadeSolo);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Ar: ");
  lcd.print(umidadeAr, 1);
  lcd.print("% ");
  lcd.print(temperatura, 1);
  lcd.print((char)223); // símbolo de grau
  lcd.print("C");

  lcd.setCursor(0, 2);
  lcd.print("Qualid. Ar: ");

  lcd.setCursor(0, 3);
  lcd.print(qualidadeDoAr);

  delay(2000); // Aguarda 2 segundos antes da próxima leitura
}
