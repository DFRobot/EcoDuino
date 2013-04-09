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

#include <avr/eeprom.h>
#include "AutoWatering.h"
#include <DHT.h>

#define MoiPIN 2   //Moisture Sensor connected to A2
#define DHTPIN 9  //DHT11 sensor connected to D9

//Uncomment whatever type you're using!
  #define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

int dat[]={0x55,0xaa,0x00,0x00,0x00};

int AutoWatering::getTemperature() //Obtain the Temperasture from DHT11 Sensor
{    
	int temperature;
	temperature = dht.readTemperature();	
	return temperature;	
}

int AutoWatering::getHumidity()  //Obtain the Humidity from DHT11 Sensor
{
    int humidity;
	humidity = dht.readHumidity();	
	return humidity;
}

int AutoWatering::MoistureSensor() //Obtain the Soil Moisture from the Moisture Sensor 
{
   int moisture_dat;
   moisture_dat=analogRead(MoiPIN);   //Moisture sensor connected to A2
   if(moisture_dat<500)moisture_dat=moisture_dat/5;
   else moisture_dat=100;
   return moisture_dat;
}

int AutoWatering::CarbonRod()   //Obtain the Soil Moisture from the Carbon
{
   int humidity_dat;
   digitalWrite(2,LOW);
   digitalWrite(3,HIGH);
   delay(500);
   digitalWrite(2,HIGH);
   digitalWrite(3,LOW);
   humidity_dat=analogRead(0);     //CarbonRod connected to A0
   if(humidity_dat<500)humidity_dat=humidity_dat/5;
   else humidity_dat=100;
   Serial.print("Soil Moisture is:" );
   Serial.println(humidity_dat);  
   return humidity_dat;
}

int AutoWatering::ADJ_humMax() //Humidity ADJ is used to adjust the maximum value of the soil moisture
{
   int dat;
   dat=analogRead(1);             //humidity max connected to A1
   dat=map(dat, 0, 1023, 0, 100);
   Serial.print("Humidity-Max is:" );
   Serial.println(dat);
   return dat;
}


void AutoWatering::pumpOff()  //Shut down the pump
{
  Serial.println("The pump is shut down now!");
  digitalWrite(5,LOW);
  digitalWrite(6,LOW); 
  digitalWrite(7,LOW);
  digitalWrite(4,LOW);  
}

void AutoWatering::pumpTestOn() //Power on the pump for testing whether it can work properly
{
  Serial.print("The Pump can work properly!");
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);  
}

void AutoWatering::Initialization() //Initialization for the auto watering kit
{
    pinMode(2,OUTPUT);
    pinMode(3,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(7,OUTPUT);
    digitalWrite(6,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(7,LOW);
    dht.begin();
}

