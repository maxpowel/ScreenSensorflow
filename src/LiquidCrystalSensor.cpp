
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystalSensor.h>
#include <Arduino.h>

byte locker[8] = {
B00100,
B01010,
B01010,
B11111,
B10001,
B10101,
B10001,
B01110,
};

byte key[8] = {
B01110,
B10001,
B10001,
B01110,
B00100,
B00110,
B00100,
B00110,
};

#define STATUS_IDLE 0
#define STATUS_DENIED 1
#define STATUS_GRANTED 2
#define STATUS_LOADING 3


LiquidCrystalSensor::LiquidCrystalSensor(int address, int columns, int rows, String name){
    screen_ = new LiquidCrystal_I2C(0x27,20,4); 
    screen_->init();
    screen_->backlight();
    statusIdle();
  if(name.length() == 0){
    sprintf(name_, "LiquidCrystal_%d",address);
  } else {
    strcpy(name_, name.c_str());
  }
}

const char * LiquidCrystalSensor::getName(){
    return name_;
}

const char * LiquidCrystalSensor::getType(){
    return "LiquidCrystal";
}


float * LiquidCrystalSensor::getValues(unsigned int quantities, unsigned int * readValues){
  
  return values_;
}

Sensor * LiquidCrystalSensor::fromConfig(void *data){

}

void LiquidCrystalSensor::statusIdle() {
  screen_->clear();
  screen_->createChar (1,locker);
  screen_->createChar (2,key);
  screen_->setCursor(0, 0); 
  screen_->write (byte (1));
  screen_->print("  SYSTEM  LOCKED  ");
  screen_->write (byte (1));
  screen_->setCursor(0, 1);
  screen_->print("PLEASE PROVIDE YOUR");
  screen_->setCursor(8, 2);
  screen_->print("KEY");
  screen_->setCursor(9, 3);
  screen_->write (byte (2));
  status = STATUS_IDLE;
}

void LiquidCrystalSensor::statusLoading() {
  screen_->clear();
  screen_->setCursor(4, 0); 
  screen_->print("AUTHORIZING");
  
  status = STATUS_LOADING;
}

void LiquidCrystalSensor::statusDenied() {
  screen_->clear();
  screen_->setCursor(7, 1); 
  screen_->print("ACCESS");
  screen_->setCursor(7, 2); 
  screen_->print("DENIED");
  status = STATUS_DENIED;
}

void LiquidCrystalSensor::statusGranted(char *name) {
  screen_->clear();
  screen_->setCursor(3, 1); 
  screen_->print("W E L C O M E");
  screen_->setCursor(9 - strlen(name) / 2, 2); 
  screen_->print(name);
  status = STATUS_GRANTED;
}