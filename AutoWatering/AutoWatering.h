/*
  
  Auto watering kit from DFRobot:http://www.dfrobot.com/index.php?route=product/product&filter_name=auto%20watering&product_id=641#.UUAW7xwqAZ4

  Functions:
  1.Power a pump to water flowers according to the humidity and temperature
  2.Use the DHT11 Sensor to test the ambient humidity and temperature
  3.Use the Moisture Sensor to test the moisture of the soil
  
  AutoWatering.cpp - Library for Auto Flower Watering Kit
  Modified in March 12th, 2013
  v0.1
*/

#ifndef AutoWatering_h
#define AutoWatering_h
#include <avr/eeprom.h>
#include <arduino.h>

#define addr  0

class AutoWatering
{
  public:
  uint8_t value,SUM;
  int getTemperature();          //Obtain the Temperasture from DHT11 Sensor
  int getHumidity();            //Obtain the Humidity from DHT11 Sensor
  int MoistureSensor();        //Obtain the Soil Moisture from the Moisture Sensor 
  int CarbonRod();            //Obtain the Soil Moisture from the Carbon
  int  ADJ_humMax();         //Humidity ADJ is used to adjust the maximum value of the soil moisture
  void pumpOff();           //Shut down the pump
  void pumpTestOn();       //Power on the pump for testing whether it can work properly
  void Initialization();  //Initialization for the auto watering kit
};
#endif
 