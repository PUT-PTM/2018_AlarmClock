
Cel projektu:
Zaprezentowany projekt ma na celu imitować pracę budzika, w tym: odliczać godzinę, ustawiać ją oraz uruchamiać alarm z opcją wyłączenia go. 

Opis projektu:
Na mikrokontrolerze STM32F411 został skompilowany program w języku C. Steruje on wyświetlaniem godziny na poczwórnym wyświetlaczu 8-segmentowym, ustawianiu cyfr za pomocą płytki z 8 przełącznikami typu tact-swich oraz uruchamianiem alarmu z udziałem płytki wyposażonej w głośnik z torem wzmacniacza.
 
Potrzebne elementy: 
1. STM32F411
2. Płytka z 8 przełącznikami typu tact-swich
3. Poczwórny wyświetlacz 8-segmentowy
4. Moduł z głośnikiem do testowania przetworników A/C i C/A - LM386M
5. Kabelki

Podłączenie:
1. Wyświetlacz 8-segmentowy --> STM32F411: 
   VCC --> VCC 3V |
   4   --> GPIOD3 |
   3   --> GPIOD2 |
   2   --> GPIOD1 |
   1   --> GPIOD0 |
   a   --> GPIOE4 |
   b   --> GPIOE5 |
   c   --> GPIOE6 |
   d   --> GPIOE7 |
   e   --> GPIOE8 |
   f   --> GPIOE9 |
   g   --> GPIOE10 |
   h   --> GPIOE11 |
   
2. Matryca 2x4 tact switch --> STM32F411: 
   G  --> GND |
   K0 --> GPIOB0 |
   K1 --> GPIOB1 |
   K2 --> GPIOB2 |
   
3. LM386M --> STM32F411: 
   5V   --> VCC 5V |
   VCC  --> VCC 3V |
   GND  --> GND |
   ADC1 --> GPIOA1 |
   AIN  --> GPIOA4 |

Kompilacja: 
Program main.c należy skompilować przy użyciu System Workbench for STM32 oraz dołączyć plik Audio2.h

Użycie: 
1. Uruchomić płytkę podłączając ją do zasilania
2. Ustawić godzinę za pomocą przycisków (K2 - zmiana cyfry, K1 - zmiana segmentu, K0 - wyjście z trybu ustawiania godziny)
3. Według uznania ustawić budzik (K2, K1 - jak powyżej, K0 - wejście do trybu oraz wyjście z trybu ustawiania budzika)
4. Alarm wyłączamy przy użyciu przycisku USER

Autorzy: 
1. Katarzyna Dykiert,
katarzyna.dykiert@student.put.poznan.pl
2. Małgorzata Hanyż, 
malgorzata.hanyz@student.put.poznan.pl
