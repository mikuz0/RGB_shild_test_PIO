// 
//
/*
Алгоритм работы управления
Кнопка
  - один клик переход по эффектам вперед (+1)
  - двойной клик перехад по эффектам назад (-1)
  При переходе в другой эффект контроль энкодера сбрасывается в единицу.
Энкодер
  - вращение регулирует текущий параметр, текущего эффекта
  - один клик переход по параметрам текущего эффекта вперед (+1)
  - двойной клик переход по параметрам текущего эффекта назад (-1)
  - Если период изменения Тмах становится меньше чем Тмин, то значение Тмин проталкивается вниз и ...

Передача параметров на мигание светодиодом происходит через переменную P_svdiod
*/
void controlTick()
{
  

    // кнопки
    btn.tick();
    
    if (btn.isSingle())   {  eff=eff+1; contr=1;
    if (eff>N_eff) {eff=0;};
      P_svdiod=eff+21 ;
      
     }; 

    if (btn.isDouble())   {  eff=eff-1; contr=1;
    if (eff<0 ) { eff=N_eff; };  
    P_svdiod=eff+21;
    
      };  
    if (btn.isHolded())   {     P_svdiod=3; };
 
btn2.tick();
   
if (btn2.isSingle())   { 
   P_svdiod=1;
switch (eff) {
  case 0:
        HSV_contr (true);
  break;
  case 1:
  case 2:
  case 3:
  case 4:
   RGBW_Contr(true);
  break;

};
eeprom_wr=true;
 };

 btn3.tick();
 if (btn3.isSingle()) {
      P_svdiod=1;
switch (eff) {
  case 0:
        HSV_contr ( false);
  break;

  case 1:
  case 2:
  case 3:
  case 4:
    RGBW_Contr(false);
  break;
   
}

    };


}



void HSV_contr( bool bm)
{
if (bm)
{
  Brightness=Brightness+50; 
  V=V+50;
}
else
{ 
    Brightness=Brightness-50; 
     V=V-50;
}
// проверяем корректность данных
if (Brightness > 254 ) {Brightness=254; P_svdiod=2;};
if (Brightness < 1 ) {Brightness=1; P_svdiod=2; };

if ( V > 254 ) {V=254; P_svdiod=2; };
if ( V < 1 ) {V=1; P_svdiod=2; };
}


void  RGBW_Contr( bool bm)
{
if (bm)
{
  Brightness=Brightness+50; 
 BrightnessRGB=BrightnessRGB+50;
}
else
{ 
    Brightness=Brightness-50; 
     BrightnessRGB=BrightnessRGB-50;
}
// проверяем корректность данных
if (Brightness > 254 ) {Brightness=254; P_svdiod=2;};
if (Brightness < 1 ) {Brightness=1; P_svdiod=2; };

if ( BrightnessRGB > 254 ) {BrightnessRGB=254; P_svdiod=2; };
if ( BrightnessRGB < 1 ) {BrightnessRGB=1; P_svdiod=2; };
}