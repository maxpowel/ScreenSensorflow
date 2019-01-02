#include <Arduino.h>
#include <SensorflowListener.h>
#include <messenger/StreamMessenger.h>
#include <LiquidCrystalSensor.h>
#include <screen.h>
#include <screen.pb.h>

StreamMessenger sm(&Serial, 5);
SensorflowListener listener(&sm);

#define SCREEN_STATUS_COMMAND "scs"
#define SCREEN_GRANT_COMMAND "scg"

void setup() {

  Serial.begin(115200);
  
  Sensor *s;
  s = new LiquidCrystalSensor(0x27,20,4, "screen");
  listener.devices[s->getName()] = s;
  listener.commands[SCREEN_STATUS_COMMAND] = (AvailableCommand {&commandScreenStatus});
  listener.commands[SCREEN_GRANT_COMMAND] = (AvailableCommand {&commandScreenGranted});


  //status_idle();
  //status_loading();
  //status_denied();
  //status_granted("ALVARO");
  // lcd.write (byte (0));

  listener.online();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  listener.next(false);
  /*if (status == STATUS_IDLE) {
    lcd.setCursor(2, 2);
    lcd.print("-->> ");
    
    lcd.setCursor(12, 2);
    lcd.print(" <<--");
    
    delay(1000);
    
    lcd.setCursor(2, 2);
    lcd.print(" -->>");
    
    lcd.setCursor(12, 2);
    lcd.print("<<-- ");
    delay(1000);
  } else if (status == STATUS_LOADING) {
    lcd.setCursor(9, 1); 
    lcd.print("|");
    delay(100);
  
    
    lcd.setCursor(10, 2); 
    lcd.print("-");
    delay(200);
    
    lcd.setCursor(9, 3); 
    lcd.print("|");
    delay(200);
    
    lcd.setCursor(8, 2); 
    lcd.print("-");
    delay(200);
    
    lcd.setCursor(9, 2); 
    lcd.print("*");
    delay(200);
    
    lcd.setCursor(9, 1); 
    lcd.print(" ");
    lcd.setCursor(10, 2); 
    lcd.print(" ");
    lcd.setCursor(9, 3); 
    lcd.print(" ");
    lcd.setCursor(8, 2); 
    lcd.print(" ");
    lcd.setCursor(9, 2); 
    lcd.print(" ");
    delay(500);
    
  }*/
}