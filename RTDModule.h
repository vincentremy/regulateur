/*
  RTDSensor.h - Library for openenergymonitor
  Created by Trystan Lea, May 16 2010
  Licenced under GPL
*/

#ifndef RTDModule_h
#define RTDModule_h

#include "Arduino.h"

class RTDModule
{
  public:
    RTDModule(double _filterVal = 0.90 );
    void setPins(int _analogInPin);
    void calibration(double _calA,double _calB);
    double getTemperatureSmooth(void);
    double getTemperature(void);
    void updateDigitalLowPass(void);
    int getADC();

  private:

    int analogInPin;
    double scale;
    double offset;
    double smoothedTemperature;
    double filterVal;

};

#endif
