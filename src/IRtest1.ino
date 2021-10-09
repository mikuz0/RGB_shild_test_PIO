


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
case 0xE207E1AD:
#if (USE_LOG == 1)
Serial.println("CH+");
#endif
digitalWrite(BUILTIN, HIGH); 
break;
case 0x4E5BA3AD :
#if (USE_LOG == 1)
Serial.println("CH-");
#endif
digitalWrite(BUILTIN, LOW); 
break;
}

}
} 
#endif
