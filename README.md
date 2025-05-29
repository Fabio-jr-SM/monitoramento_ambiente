
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

2. **LiquidCrystal_I2C**: Para controle do display LCD via I2C.

   * Disponível em: [Instructables - How to Use I2C Serial LCD 20X4](https://www.instructables.com/How-to-Use-I2C-Serial-LCD-20X4-Yellow-Backlight/)

---

## 🚀 Como Usar

1. Monte o circuito conectando os sensores e o display LCD conforme o esquema de conexões acima.
2. Carregue o código fornecido na placa Arduino UNO através da Arduino IDE.
3. Abra o **Monitor Serial** com baudrate de 9600 para visualizar os dados em tempo real.
4. Os dados também serão exibidos no display LCD, atualizados a cada 2 segundos.

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

---

## ⚙️ Funcionamento dos Componentes

### 🔸 Sensor de Umidade do Solo

Este sensor funciona medindo a **resistência elétrica** entre duas hastes metálicas inseridas no solo. Quando o solo está seco, a resistência entre as hastes é alta; quando está úmido, a resistência é baixa, permitindo maior passagem de corrente elétrica.

- **Tipo:** Sensor resistivo analógico
- **Saída:** Tensão proporcional à umidade
- **Considerações:**  
  - Sensores resistivos se desgastam com o tempo devido à oxidação.  
  - A alimentação controlada pelo pino digital 7 ajuda a prolongar sua vida útil.

---

### 🔸 Sensor DHT22 (AM2302)

O DHT22 é um sensor digital que combina um termistor e um sensor capacitivo de umidade. Ele possui um chip embutido que realiza as conversões analógicas para digitais e envia os dados já prontos via protocolo de 1 fio (one-wire).

- **Medições:**  
  - Temperatura (−40 a +80 °C com precisão de ±0,5 °C)  
  - Umidade relativa (0–100% com precisão de ±2–5%)
- **Intervalo de leitura:** 2 segundos
- **Saída:** Digital (formato binário específico)

---

### 🔸 Sensor MQ135

Este sensor detecta gases no ambiente com base em um elemento sensor aquecido que altera sua resistência em contato com gases como CO₂, amônia, álcool, benzeno e fumaça. A resistência do sensor varia conforme a concentração do gás, gerando uma saída analógica.

- **Gases detectáveis:** CO₂, amônia (NH₃), álcool, benzeno, fumaça e outros poluentes
- **Tensão de operação:** 5V
- **Saída:** Analógica (varia com concentração de gases)
- **Considerações:**  
  - Requer **pré-aquecimento** de alguns minutos para estabilizar.  
  - Para maior precisão, deve-se calibrar com concentrações conhecidas dos gases.

---

### 🔸 Arduino UNO

O Arduino UNO é a unidade de controle central do projeto. Baseado no microcontrolador ATmega328P, ele lê os sensores, processa os dados e atualiza a interface visual (display LCD) e o Monitor Serial.

- **Microcontrolador:** ATmega328P
- **Tensão de operação:** 5V
- **Portas disponíveis:**  
  - 14 digitais (6 com PWM)  
  - 6 analógicas (A0–A5)  
- **Comunicação:** USB, UART, I2C, SPI

---

### 🔸 Display LCD I2C 20x4

O display LCD 20x4 permite a exibição de até 4 linhas com 20 caracteres cada. Ele é adaptado com um **módulo I2C**, que reduz os pinos de controle de 16 para apenas 2 (SDA e SCL), facilitando a conexão com o Arduino.

- **Interface:** I2C (padrão: SDA em A4, SCL em A5 no Arduino UNO)
- **Endereço I2C padrão:** `0x27` ou `0x3F` (pode variar)
- **Vantagens:**  
  - Ocupa poucos pinos  
  - Ideal para projetos com múltiplos sensores  
  - Fácil de integrar com a biblioteca `LiquidCrystal_I2C`
