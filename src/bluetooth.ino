
#if (USE_BT == 1)
#define PARSE_AMOUNT 10    // максимальное количество значений в массиве, который хотим получить
#define header '$'        // стартовый символ
#define divider ','       // разделительный символ
#define ending ';'        // завершающий символ
int intData[PARSE_AMOUNT];     // массив численных значений после парсинга
boolean recievedFlag;
String request = "1234567891011121314151617181920";
boolean getStarted;
byte index;
String string_convert = "";

/*
void sendSettings() {
  
  
  request = String("S");
 if (xx==1) { request += String(xx); 
    request += String(Brightness);
  }
  
  switch (eff)
  {
  case 0 :
      switch (xx)
      {
      case 2 :
        request += String(xx);
        request += String(V);
        
        break;
      
      default:
      xx=8;
        break;
      }
    
    //request += String(" "); 
    //request += String(speedK_min);
    //request += String(" "); 
    //request += String(speedK_max);
    //request += String(" "); 
    //request += String(H_min );
    //request += String(" "); 
    //request += String(H_max);
    //request += String(" ");
    //request += String(S_min);
    //request += String(" "); 
    //request += String(S_max);
     
    break;
  case 1:
    request += String(BrightnessRGB );
    request += String(" "); 
    request += String(Tcollor_min );
    request += String(" "); 
    request += String(Tcollor_max);
    request += String(" ");
    request += String(speedK_min);
    request += String(" "); 
    request += String(speedK_max);
    break;
  case 2:
    request += String(BrightnessRGB );
    request += String(" ");
    request += String(speedR);
    request += String(" ");
    request += String(speedG);
    request += String(" "); 
    request += String(speedB); 
    
    break;
  case 3:
    request += String(BrightnessRGB );
    request += String(" "); 
    request += String(speedK_min);
    request += String(" "); 
    request += String(speedK_max);
    break;
  case 4:
    request += String(BrightnessRGB );
    request += String(" "); 
    request += String(speedTemp);
    break;
  case 5 :
    request += String(H);
    request += String(" "); 
    request += String(S);
    request += String(" "); 
    request += String(V);
        break;
  case 6:
    request += String(BrightnessRGB );
    request += String(" "); 
    request += String(R);
    request += String(" "); 
    request += String(G);
    request += String(" "); 
    request += String(B);
    
    break;
  case 7:
    request += String(BrightnessRGB );
    request += String(" ");
    request += String(Temp); 
    break;
  case 8:
   request += String(BrightnessRGB );
  request += String(" ");
  request += String(Color);  
    break;
  default:
  eff=0;
    break;
  }
  xx=xx+1;
  if (xx==9) {request += String(xx); xx=1 ;}
      request += String("F");
       Serial.println(request);
       Serial.println(xx);
      
    
}
*/
void sendSettings() {
  
  
  request = String("S");
 if (xx==1) { request += String(xx); request += String(Brightness); };
        switch (xx)
      {
        case 1:
        // no remove
        break;
      case 2 :
        request += String(xx);
        request += String(V);
        break;
      
      default:
      xx=8;
        break;
      }
      xx=xx+1;
  if (xx==9) {request += String(xx); xx=1 ; }
      request += String("F");
       Serial.println(request);
          
}


void bluetoothTick() {
  parsing();               // функция парсинга
  if (recievedFlag) {     // если получены данные
    recievedFlag = false;
    /*for (byte i = 0; i < 7; i++) {
      Serial.print(intData[i]);
      Serial.print(" ");
      } Serial.println(" ");*/
    switch (intData[0]) {
      case 0:   // запрос онлайна
        request = "OK";
        // request += String(batPerc); видимо состояние батареи, нам не надо
        Serial.print(request);
        break;
      case 1:   // запрос состояния (настройки)
        sendSettings();
        
       // btnControl = false; // видимо блокировка контроля с кнопок, возможно убрать?
        //P_svdiod=1;
        break;
      case 2:   // применить настройки
      Brightness= (byte) intData[1] ;
          switch (eff)
  {
  case 0 :
    V= (byte) intData[2];
    //speedK_min=intData[3];
    //speedK_max = intData[4];
    //H_min = intData[5];
    //H_max = intData[6];
    //S_min = intData[7];
    //S_max = intData[8];
     
    break;
  case 1:
    BrightnessRGB = intData[2];
    ///Tcollor_min = intData[3];
    //Tcollor_max = intData[4];
    //speedK_min = intData[5];
    //speedK_max = intData[6];
    break;
  case 2:
    BrightnessRGB = intData[2];
    speedR = (float)5*intData[3];
    speedG = (float)5*intData[4];
    speedB = (float)5*intData[5]; 
    
    break;
  case 3:
    BrightnessRGB = intData[2];
    //speedK_min =intData[3];
    //speedK_max = intData[4];
    break;
  case 4:
    BrightnessRGB = intData[2];
    //speedTemp = intData[3];
    break;
  case 5 :
    H = intData[3];
    S = intData[4];
    V = intData[2];
        break;
  case 6:
    BrightnessRGB = intData[2];
    R = intData[3];
    G = intData[4];
    B = intData[5];
    
    break;
  case 7:
    BrightnessRGB = intData[2];
    Temp = 39*intData[3]; // mashtab 256
    break;
  case 8:
   BrightnessRGB =  intData[2]; // mashtab 256
   Color = 6*intData[3];  
    break;
  default:
  eff=0;
    break;
  } ;
  
        break;
      case 3:   // дополнительные настроки
        
       // NULL
        break;
      case 4:   // смена режима
        eff = intData[1]-1;// index in mit invertor 1...
        P_svdiod=1;
        // sendSettings();
        btnControl = false;
        
        
        break;
      case 5:   // вкл/выкл
        if (intData[1]) LEDon = true;
        else LEDon=false;
        btnControl = false;
        P_svdiod=1;
        break;
    }
  }
}

void parsing() {
  if (Serial.available() > 0) {
    char incomingByte = Serial.read();      // обязательно ЧИТАЕМ входящий символ
    if (getStarted) {                         // если приняли начальный символ (парсинг разрешён)
      if (incomingByte != divider && incomingByte != ending) {   // если это не пробел И не конец
        string_convert += incomingByte;       // складываем в строку
      } else {                                // если это пробел или ; конец пакета
        intData[index] = string_convert.toInt();  // преобразуем строку в int и кладём в массив
        string_convert = "";                  // очищаем строку
        index++;                              // переходим к парсингу следующего элемента массива
      }
    }
    if (incomingByte == header) {             // если это $
      getStarted = true;                      // поднимаем флаг, что можно парсить
      index = 0;                              // сбрасываем индекс
      string_convert = "";                    // очищаем строку
    }
    if (incomingByte == ending) {             // если таки приняли ; - конец парсинга
      getStarted = false;                     //  не сохранять принятые символы т.к. конец приема
      recievedFlag = true;                    // флаг данные приняты, можно обрабатывать
    }
  }
}
#else
void bluetoothTick() {}
#endif
