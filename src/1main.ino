#include <Arduino.h>
// ------ Драйвер ------
#define HIGH_FREQUENCY 1    // 0 - 490 Гц, 1 - 7.8 кГц, 2 - 31.4 кГц, 3 - ручная настройка
#define PWM_FREQUENCY 15000 // частота ШИМ на настройке №3, Герц
#define DRIVER_DIRECTION 0  // 0 - обычный (мосфеты), 1 - реверс (LED amplifier)

#define USE_LOG 1
#define R13 10.0
#define R14 0.670

// Включить поддержку BT 1
#define USE_BT 0

// Включить поддержку IR 1
#define USE_IR 1

#if (USE_IR == 1)
#define IR_PIN 2 // указываем вывод, к которому подключен приемник

#include "IRLremote.h"
CHashIR IRLremote;
uint32_t IRdata;
#define BUILTIN 13 // светодиод для мигания с пульта
#endif

// ------ Кнопка -------
#define USE_BTN 1           // 1 - использовать кнопку, 0 - нет
// #define BTN_MODE 0          // режим работы кнопки: 0 - переключение пресетов, 1 - переключение цветов
//
// кнопка 4, 5- парные, 6- Отдельная
#define BTN_1 6
#define BTN_2 4
#define BTN_3 5

// --------- Цвет ---------
#define MIN_PWM 0           // минимальный сигнал PWM
// #define GAMMA_BRIGHT 1      // гамма-коррекция яркости
// #define LUT_R 1.0           // коэффициент LUT матрицы красного цвета (0.0 - 1.0)
// #define LUT_G 1.0           // коэффициент LUT матрицы зелёного цвета (0.0 - 1.0)
// #define LUT_B 1.0           // коэффициент LUT матрицы синего цвета (0.0 - 1.0)

// драйвер
#define PIN_R 3
#define PIN_G 9
#define PIN_B 10
#define PIN_W 11


#define LED_PIN 13 // светодиод
//Колличество режимов
#define N_eff 4
#define N_contr 4
//#define EPROM_CONTR 98 // для очистки памяти поменять на другое



//#include <EEPROMex.h>
#include <GyverRGB.h>
GRGB diode(PIN_R, PIN_G, PIN_B);  // куда подключены цвета (R, G, B)

#include <GyverButton.h>
GButton btn(BTN_1);
GButton btn2(BTN_2);
GButton btn3(BTN_3);


int8_t eff=0 ; // режим вывода
byte contr=1 ; // режим управления энкодором, что меняем
int  Brightness = 250; // яркость белого канала
int  BrightnessRGB =250 ;
byte  H = 150;
byte  S = 200;
int  V = 230;
byte  H_min=0;
byte  H_max=250;
byte  S_min=150;
byte  S_max=255;
int Temp=1010;
float Tcollor_min=10;
float Tcollor_max=100;
// настройки режимов
float speedK_min=10 ;// длительность цикла мС
float speedK_max=100;
byte  R=200;
byte  G=50;
byte  B=70;
uint32_t Timer=0, TimerR=0, TimerG=0, TimerB=0;
float speedTemp=500; // 100 - 1000

int Color=0 ;

bool napr=true ;
bool naprS=true ;

bool naprSp=false;
bool hdiod=true;
bool eeprom_wr=false;
byte P_svdiod=0;
bool btnControl = true;
bool LEDon = true;
byte xx=1;

void setup() {
  #if (USE_IR == 1)
 IRLremote.begin(IR_PIN); // запускаем прием
 
  pinMode(BUILTIN, OUTPUT);
#endif
  analogReference(INTERNAL);
  //analogReference(EXTERNAL);
   if (USE_LOG) Serial.begin(9600);
  // инициализируем светодиод и показиваем что питание есть
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  // put your setup code here, to run once:
  //pinMode(PIN_R, OUTPUT);
  //pinMode(PIN_G, OUTPUT);
  //pinMode(PIN_B, OUTPUT);
  pinMode(PIN_W, OUTPUT);
  //diode.setMinPWM(MIN_PWM);

// btn.setStepTimeout(150);
btn.setClickTimeout(500);
btn2.setClickTimeout(500);
btn3.setClickTimeout(500);  

 // ------ ЛЕНТА -------
  // выставляем режим и частоту ШИМ
  if (HIGH_FREQUENCY == 1) {
    TCCR1B |= _BV(WGM12);
    TCCR1B = TCCR1B & 0b11111000 | 0x02;
    TCCR2A |= _BV(WGM20) | _BV(WGM21);
    TCCR2B = TCCR2B & 0b11111000 | 0x02;
  } else if (HIGH_FREQUENCY == 2) {
    TCCR1B &= ~_BV(WGM12);
    TCCR1B = TCCR1B & 0b11111000 | 0x01;
    TCCR2A |= _BV(WGM20);
    TCCR2B = TCCR2B & 0b11111000 | 0x01;
  } else if (HIGH_FREQUENCY == 3) {
    diode.highFrequency(PWM_FREQUENCY);
  }
#if (USE_LOG == 1)
Serial.println("Start devis");
#endif
 
}

void loop() {
  
 if (btnControl ) controlTick();    // отработка управления если не блокировано ВТ
 if (LEDon ) effectsTick(); else {
    digitalWrite(PIN_R, LOW);
    digitalWrite(PIN_G, LOW);
    digitalWrite(PIN_B, LOW);
    digitalWrite(PIN_W, LOW); }    // вывод режимов если не выключено
#if (USE_BT == 1)
bluetoothTick();
#endif
sv_diod();
#if (USE_LOG == 1)
LogTick();
#endif
  #if (USE_IR == 1)
IRtick();
#endif
}