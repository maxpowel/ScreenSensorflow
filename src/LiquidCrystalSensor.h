#include "Sensor.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


#ifndef LIQUIDCRYSTALI2C_SENSOR_H
#define LIQUIDCRYSTALI2C_SENSOR_H


class LiquidCrystalSensor: public Sensor {
public:
  LiquidCrystalSensor(int address=0x27, int columns=20, int rows=4, String name = "");
  const char* getName();
  float* getValues(unsigned int quantities, unsigned int * readValues);
  static const char* getType();
  static Sensor* fromConfig(void *);

  void statusIdle();
  void statusLoading();
  void statusDenied();
  void statusGranted(char *name);
  LiquidCrystal_I2C *screen_;
private:
  int status;
  char name_[10];
  float values_[4];
  
};


#endif //LIQUIDCRYSTALI2C_SENSOR_H