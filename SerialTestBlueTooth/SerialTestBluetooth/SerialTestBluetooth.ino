#include <SoftwareSerial.h>
SoftwareSerial EEBlue(10, 11); // RX | TX
char command; 
String string; 
boolean ledon = false;

void setup()
{
 
  Serial.begin(9600);
  EEBlue.begin(9600);  //Default Baud for comm, it may be different for your Module. 
  Serial.println("The bluetooth gates are open.\n Connect to HC-05 from any other bluetooth device with 1234 as pairing key!.");
 
}
 
void loop()
{
 
  // Feed any data from bluetooth to Terminal.
  if (EEBlue.available())
    Serial.write(EEBlue.read());
 
  // Feed all data from termial to bluetooth
  if (EEBlue.available() > 0) {
      string = "";} 
      while(EEBlue.available() > 0) { 
        command = ((byte)EEBlue.read()); 
        
        if(command == ':') { 
          break; 
          }else { 
            string += command; 
          }
           delay(1); 
        } 
        if(string == "TO") { 
              ledOn(); 
              ledon = true;
            } 
        if(string =="TF") { 
              ledOff(); 
              ledon = false; 
              Serial.println(string); 
              //debug 
        } 
        if ((string.toInt()>=0)&&(string.toInt()<=255)) { 
          if (ledon==true) { 
            analogWrite(LED_BUILTIN, string.toInt()); 
            Serial.println(string); //debug delay(10); 
          } 
        } 
    EEBlue.write(EEBlue.read());
}

void ledOn() {
  analogWrite(LED_BUILTIN, 255); delay(10);
} void ledOff() {
  analogWrite(LED_BUILTIN, 0);
  delay(10);
}
