#define pinoAnalog A0

int ValAnalogIn;

void setup() {
  Serial.begin(9600);
  Serial.println("Monitoramento de Umidade do Solo");
}

void loop() {
  ValAnalogIn = analogRead(pinoAnalog);
  int Porcento = map(ValAnalogIn, 300, 1023, 100, 0); // Ajuste baseado em testes

  Serial.print("Umidade do Solo: ");
  Serial.print(Porcento);
  Serial.println("%");

  delay(1000);
}
