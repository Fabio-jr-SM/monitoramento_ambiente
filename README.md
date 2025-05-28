# 📘 Documentação Técnica: Monitoramento Ambiental com Arduino

## 🌿 Visão Geral

Este projeto realiza o monitoramento de condições ambientais utilizando sensores conectados a um Arduino UNO. Os dados coletados são exibidos em tempo real no Monitor Serial e em um display LCD I2C 20x4, proporcionando uma interface visual amigável.

---

## 🔌 Componentes Utilizados

Este projeto utiliza sensores simples e um display LCD para monitorar condições ambientais como umidade do solo, temperatura, umidade do ar e qualidade do ar.

| Imagem                                                                                                   | Componente                    | Função                                                         | Pinos no Arduino                              | Observações                                                 |
| -------------------------------------------------------------------------------------------------------- | ----------------------------- | -------------------------------------------------------------- | --------------------------------------------- | ----------------------------------------------------------- |
| <img src="https://github.com/user-attachments/assets/a0a8b7a8-1795-45eb-ad19-486ca0c444ae" width="120"/> | **Sensor de Umidade do Solo** | Mede a umidade do solo através da resistência entre as hastes. | A0 (Sinal), 7 (VCC via controle digital), GND | Desligar o VCC via pino 7 para preservar o sensor.          |
| <img src="https://github.com/user-attachments/assets/79055b04-e2ba-49e0-a960-eff3f5c36c9f" width="120"/> | **Sensor DHT22 (AM2302)**     | Mede temperatura e umidade do ar com alta precisão.            | Digital 5, VCC, GND                           | Usa a biblioteca DHTlib. Sensor digital.                    |
| <img src="https://github.com/user-attachments/assets/55136a28-0f18-437d-8f2e-2347a0fea058" width="120"/> | **Sensor MQ135**              | Detecta gases como amônia, CO₂ e fumaça.                       | A1 (Sinal), VCC, GND                          | Para leituras precisas, recomenda-se calibração.            |
| <img src="https://github.com/user-attachments/assets/2774e623-511c-40a3-bb8a-3956ad71b69a" width="120"/> | **Arduino UNO**               | Controla o funcionamento do sistema e processa os dados.       | Vários                                        | Base do sistema, alimentado via USB ou fonte externa.       |
| <img src="https://github.com/user-attachments/assets/0254cd31-f44e-499a-90d9-77d4a0412482" width="120"/> | **Display LCD I2C 20x4**      | Exibe os dados lidos dos sensores de forma clara.              | SDA (A4), SCL (A5), VCC, GND                  | Comunicação I2C: usa apenas 2 pinos. Endereço padrão: 0x27. |

---

## 🛠️ Esquema de Conexões

| Componente                    | Pino Arduino       |
| ----------------------------- | ------------------ |
| Sensor de Umidade do Solo     | A0                 |
| DHT22                         | 5                  |
| MQ135                         | A1                 |
| Alimentação do Sensor de Solo | 7 (digital)        |
| LCD I2C 20x4                  | SDA (A4), SCL (A5) |

---

## 📦 Instalação das Bibliotecas

Para o funcionamento correto do projeto, é necessário instalar as seguintes bibliotecas na Arduino IDE:

1. **DHTlib**: Para comunicação com o sensor DHT22.

   * Vá em **Sketch > Incluir Biblioteca > Gerenciar Bibliotecas...**
   * Procure por **DHTlib** e instale a biblioteca criada por Rob Tillaart.

2. **LiquidCrystal\_I2C**: Para controle do display LCD via I2C.

   * Disponível em: [Instructables - How to Use I2C Serial LCD 20X4](https://www.instructables.com/How-to-Use-I2C-Serial-LCD-20X4-Yellow-Backlight/)

---

## 🚀 Como Usar

1. Monte o circuito conectando os sensores e o display LCD conforme o esquema de conexões acima.
2. Carregue o código fornecido na placa Arduino UNO através da Arduino IDE.
3. Abra o **Monitor Serial** com baudrate de 9600 para visualizar os dados em tempo real.
4. Os dados também serão exibidos no display LCD, atualizados a cada 2 segundos.([fermarc.com][3])

---

## 🖥️ Saída Esperada no Monitor Serial

```
===== Monitoramento Ambiental =====
Umidade do solo: 42%
Umidade do ar: 58.2%
Temperatura: 26.4 °C
Qualidade do ar (MQ135) - Valor bruto: 187 - Classificação: Boa
====================================
```

---

## 📌 Observações

* **Calibração do MQ135**: A classificação da qualidade do ar é aproximada e pode variar conforme o ambiente. Para medições precisas, é necessário calibrar o sensor com gases específicos.
* **Umidade do Solo**: Os valores podem variar com o tipo de solo. Ajuste a função `map()` no código conforme necessário.
* **Alimentação do Sensor de Solo**: O pino 7 é utilizado para controlar a alimentação do sensor de umidade do solo, desligando-o quando não está em uso para economizar energia e prolongar sua vida útil.
