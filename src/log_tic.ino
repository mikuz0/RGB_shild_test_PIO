#if (USE_LOG == 1)
void LogTick()
{
    float Up=0;
    static long Tu=0;
    if ((Tu+1000)< millis()) {
    for ( byte i=1; i<=100; i++) { Up=Up+(float)analogRead(A0);}
  Up=Up*1.1/1024/100*(R13+R14)/R14;
  Serial.print(BrightnessRGB);
    Serial.print(";");
     Serial.print(Brightness);
  Serial.print(";");
Serial.println(Up);
Up=0;
Tu=millis();
    }
}

#endif