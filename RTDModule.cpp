/*
  RTDSensor.cpp - Library for openenergymonitor
  Created by Trystan Lea, April 27 2010
  Licenced under GPL
*/
#include "Arduino.h"
#include "RTDModule.h"

//-----------------------------------------------------------------------
// Set module pins
//-----------------------------------------------------------------------
 RTDModule::RTDModule(double _filterVal)
{
   filterVal = _filterVal;
}

//-----------------------------------------------------------------------
// Set module pins
//-----------------------------------------------------------------------
void RTDModule::setPins(int _analogInPin)
{
   analogInPin = _analogInPin;
}

//-----------------------------------------------------------------------
// Set calibration values
//
// Calibration needs to be set for RTD input
//-----------------------------------------------------------------------
void RTDModule::calibration(double _calA,double _calB)
{
   scale = _calA;
   offset = _calB;
}

//-----------------------------------------------------------------------
// Read smoothed temperature
//-----------------------------------------------------------------------
double RTDModule::getTemperatureSmooth(void)
{
    return smoothedTemperature;
}
//-----------------------------------------------------------------------
// Update smoothed temperature
//-----------------------------------------------------------------------
void RTDModule::updateDigitalLowPass(void)
{
  smoothedTemperature = (getTemperature() * (1 - filterVal)) + (smoothedTemperature * filterVal);
}
//-----------------------------------------------------------------------
// Read temperature
//-----------------------------------------------------------------------
double RTDModule::getTemperature(void)
{
   double temperature = scale * analogRead(analogInPin) + offset;
   return temperature;
}

//-----------------------------------------------------------------------
// RAW analogread
//-----------------------------------------------------------------------
int RTDModule::getADC() { return analogRead(analogInPin); }
//-----------------------------------------------------------------------

