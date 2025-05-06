## 🌱 Projeto: Monitoramento Ambiental com Arduino

Este projeto realiza o monitoramento de condições ambientais utilizando sensores simples conectados a um Arduino. Os dados são exibidos no Monitor Serial para observação em tempo real.

### 🔌 Sensores utilizados

| Sensor                    | Função                               | Pino Arduino |
| ------------------------- | ------------------------------------ | ------------ |
| Sensor de Umidade do Solo | Mede a umidade do solo               | A0           |
| DHT22                     | Mede a umidade do ar e temperatura   | 5            |
| MQ135                     | Mede a qualidade do ar               | A1           |
| Fonte 5V via pino         | Alimenta o sensor de umidade do solo | 7            |

---

### 🔧 Requisitos

* Arduino UNO (ou compatível)
* Sensor de umidade do solo
* Sensor DHT22
* Sensor MQ135
* Cabos jumpers
* Biblioteca `dht.h` (DHTlib)

---

### 📦 Instalação da biblioteca DHT

1. Abra o Arduino IDE
2. Vá em **Sketch > Incluir Biblioteca > Gerenciar Bibliotecas...**
3. Procure por `DHTlib`
4. Instale a biblioteca criada por Rob Tillaart

---

### 🚀 Como usar

1. Conecte os sensores conforme os pinos definidos no código.
2. Faça o upload do código para a placa Arduino.
3. Abra o **Monitor Serial** com baudrate 9600.
4. Visualize os dados atualizados a cada 2 segundos.

---

### 🖥️ Saída esperada no Monitor Serial

```
===== Monitoramento Ambiental =====
Umidade do solo: 42%
Umidade do ar: 58.2%
Temperatura: 26.4 °C
Qualidade do ar (MQ135) - Valor bruto: 187 - Classificação: Boa
====================================
```

---

### 📌 Observações

* A escala de qualidade do ar do MQ135 é **aproximada** e pode variar de acordo com o ambiente. Para medições mais precisas, é necessário calibrar o sensor com gases específicos.
* Os valores de umidade do solo variam com o tipo do solo e devem ser ajustados se necessário (`map()`).
* O pino 7 é utilizado como uma fonte controlada de 5V para economizar energia e prolongar a vida útil do sensor de umidade do solo.

---
