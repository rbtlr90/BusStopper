/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Social networks:            http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  =>
  =>          USB HOWTO: http://tiny.cc/BlynkUSB
  =>

  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT DebugSerial


// You could use a spare Hardware Serial on boards that have it (like Mega)
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(4, 5); // RX, TX
#include <BlynkSimpleStream.h>

WidgetLCD lcd(V2);

float a = 36.1024866;
float b = 129.3915631;
float latitude = 0;
float longitude = 0;
float volume=1200;
float len = 3000;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "AUTHCODE";


void notifyOnButtonPress()
{
  // Invert state, since button is "Active LOW"
  if(digitalRead(2)){
        if(len<1){
          len=1;
         }
         if (volume<1){
          volume=1;
          }
        
         tone(9,volume, len);
       if(0.0008 >= sqrt((latitude*latitude) + (longitude*longitude))) {
        lcd.print(0,0,"Bus is near");
         digitalWrite(7, HIGH);
           if(0.0002 >= sqrt((latitude*latitude) + (longitude*longitude))){
            lcd.print(0,0,"Bus is close enough");
           digitalWrite(8, HIGH);
           }
           
       }
       else {
         lcd.print(0,0,"Bus is too far");
       }
    }
  else{
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      lcd.clear();
      noTone(9);
    Blynk.notify("Yaaay... button is pressed!");
    }
    
}

BLYNK_WRITE(V1) {
  GpsParam gps(param);
  latitude = gps.getLat() - a;
  longitude = gps.getLon() - b;
  volume = 1200 - ((sqrt((latitude*latitude) + (longitude*longitude)))*900000);
  len = 3000 - ((sqrt((latitude*latitude) + (longitude*longitude)))*1000000*2);
}



void setup()
{
  // Debug console
  DebugSerial.begin(9600);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  lcd.clear();
  pinMode(7, OUTPUT);
  attachInterrupt(0, notifyOnButtonPress, CHANGE);

  Blynk.begin(Serial, auth);
}
void loop()
{
  Blynk.run();
}
