


#if (USE_IR == 1)
void IRtick()
{
   
 

if ( IRLremote.available()) { // если данные пришли
 auto data = IRLremote.read();
    IRdata = data.command;
#if (USE_LOG == 1)
 Serial.println(IRdata, HEX);
  Serial.println("Next cycle");

 #endif
switch ( IRdata ) {
case BUTT_UP:
#if (USE_LOG == 1)
Serial.println("CH+");
#endif
digitalWrite(BUILTIN, HIGH); 
break;
case BUTT_DOWN :
#if (USE_LOG == 1)
Serial.println("CH-");
#endif
digitalWrite(BUILTIN, LOW); 
break;

case BUTT_0:
eff=0;
break;
case BUTT_1:
eff=1;
break;
case BUTT_2:
eff=2;
break;
case BUTT_3:
eff=3;
break;
case BUTT_4:
eff=4;
break;

}

}
} 
#endif
