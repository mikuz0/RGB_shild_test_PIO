/*
Эффекты и режимы.
Режимы только для проверки правильности функционирования каналов.

       0. Режим HSV с качанием по тону и насыщености. Регулировка яркости совместно 
       1. Режим R. Регулировка яркости.
       2. Режим G. Регулировка яркости.
       3. Режим B. Регулировка яркости.
       4. Режим W. Регулировка яркости.
      .
*/

void effectsTick()

   {
      float K;
      K = (Tcollor_max-Tcollor_min)/256;
 switch (eff) {

  case 0:  
    if ((millis()-Timer)>speedTemp){
      if (napr) {H=H+1;} else {H=H-1 ;};
      if (H > H_max) {napr=false; H=H_max;} ;
      if (H < H_min) {napr=true; H=H_min;};

      if (naprS) {S=S+2;} else {S=S-2 ;};
      if (S > S_max) {naprS=false; S=S_max;} ;
      if (S < S_min) {naprS=true; S=S_min;};

      if (naprSp) {speedTemp=speedTemp+0.05;} else {speedTemp=speedTemp-0.05 ;};
      if (speedTemp > speedK_max) {naprSp=false; speedTemp=speedK_max;} ;
      if (speedTemp < speedK_min) {naprSp=true; speedTemp=speedK_min;};

   Timer=millis();
  };
   diode.setBrightness(BrightnessRGB); 
   diode.setHSV(H, S, V);
   analogWrite(PIN_W, Brightness);
   break;
case 1:
   R=255;
   G=0;
   B=0;
      diode.setBrightness(BrightnessRGB); 
      diode.setRGB(R, G, B); 
      analogWrite(PIN_W, 0);
   break;
   case 2:

      R=0;
      G=255;
      B=0;
      diode.setBrightness(BrightnessRGB); 
      diode.setRGB(R, G, B);
      analogWrite(PIN_W, 0);
   break;
   
   case 3:
   R=0;
   G=0;
   B=255;
      diode.setBrightness(BrightnessRGB); 
      diode.setRGB(R, G, B);
      analogWrite(PIN_W, 0);
   break;

   case 4:
      R=1;
      G=1;
      B=1;
      diode.setBrightness(0); 
      diode.setRGB(R, G, B);
      analogWrite(PIN_W, Brightness);
     
   break;
}
  


   }
   
      