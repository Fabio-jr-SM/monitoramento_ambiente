int mq135Pin = A1; // Pino analógico onde o sensor está conectado

void setup() {
  Serial.begin(9600); // Inicia a comunicação serial
}

void loop() {
  int valorSensor = analogRead(mq135Pin); // Lê o valor do sensor (0 a 1023)

  // Converte para uma escala de qualidade do ar (quanto maior, pior)
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

  Serial.print("Valor bruto: ");
  Serial.print(valorSensor);
  Serial.print(" - Qualidade do ar: ");
  Serial.println(qualidadeDoAr);

  delay(2000); // Aguarda 2 segundos para nova leitura
}
