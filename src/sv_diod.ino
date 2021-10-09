 /*
функция мигания светодиодом
должна выываться в главном цикле и работает условно в фоне
передача параметров мигания происходит через глабальную переменнную P_svdiod
Необходимы следующие режимы:
0. режим станова- когда органы управления не используются в течении 10 секунд, светодиод- погашен
    при переходе в этот режим настройки сохраняются в память, если есть разрешение
1. режим демонстрации периода speedT. 
    Включается при активации органов управления. На время speedT включает светодиод, 
    затем на время speedT- выключает. По оканчанию 10 секунд переходит в режим 0 (останов) 
2. режим демонстраци достижения предела регулирования. 
    (максимальное или минимальное значение яркости и возможно другое) 
    мигание светодиодом с периодом 0.4 С, в течении 2 С. Затем переход в режим 1(показ speedT)
3. режим демонстрации "проталкивания". Мигаем с периодом 0.2С, в течении 0.5С, затем погашен на 0.5С,
    в течении 2С. Затем переходим в режим 1.
4. режим номера эффекта и номера параметра. P_svdiod=20+Х. мигает Х раз. 
*/
void sv_diod()
{
    static float T_re=0; //Общее время текущего режима
    static float T_bl=0; //полпериода мигания
    static bool akt=true;
    static long Timersv=0; // для периода моргания
    static long Timer_r=0; // для длительности первого режима
    static long Timer_r2=0; // для третьего режима
    static byte X ; // осталось мигнуть... раз
switch (P_svdiod)
{
    case 0:
    digitalWrite(LED_PIN, 0);
    akt=false;
    hdiod=false;
    btnControl = true;
    
    
    break;
case 1:
    T_re=10000;
    T_bl=speedTemp;
    Timer_r=millis();
    P_svdiod=11; // параметры режима установлены, переходим к миганию
    akt=true;
    hdiod=true;
    break;
    case 2:
    T_re=2000;
    T_bl=100; 
    Timer_r=millis();
    P_svdiod=12; // параметры режима установлены, переходим к миганию  
    akt=true;
    break;
    case 3:
    T_re=3000;
    T_bl=50;
    Timer_r=millis();
    Timer_r2=Timer_r;
    P_svdiod=13; // параметры режима установлены, переходим к миганию
    akt=true;
    
    break;
} 
if (P_svdiod > 10 && akt && P_svdiod < 20)
{
 if ((millis()-Timersv)>T_bl){   

digitalWrite(LED_PIN, hdiod);
hdiod=! hdiod;
Timersv=millis();
 }; //end millis
}// end if P_svdiod
switch (P_svdiod)
{
case 11 :
if ((millis()-Timer_r)>T_re){
P_svdiod=0;
akt=false;
};
    break;

case 12 :
if ((millis()-Timer_r)>T_re){
P_svdiod=1;
};
    break;

case 13 :
if ((millis()-Timer_r)>T_re){
P_svdiod=1;
} else { 
if ((millis()-Timer_r2)>500){
akt=!akt ;
Timer_r2=millis();
}
 };

    break;
}
if (P_svdiod > 20)
{
X=(P_svdiod-20)*2;
P_svdiod=20; T_bl=500; Timersv = millis(); hdiod=true;
};
if (P_svdiod == 20 && (millis()-Timersv)>T_bl && X>0)
{
digitalWrite(LED_PIN, hdiod);
hdiod=! hdiod;
Timersv=millis();
X--;
}
}