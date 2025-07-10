#include "RTDTrigger.h"
#include <math.h>
//#include <arduino.h>


RTDTrigger::RTDTrigger(double _temperatureTrigLevel)
{
    temperatureTrigLevel = _temperatureTrigLevel;
    m_isTriggered = false;
}

void RTDTrigger::UpdateTrigger(void)
{
    updateDigitalLowPass();
    if(fabs(getTemperatureSmooth() - previousTemperature) > temperatureTrigLevel)
    {
        previousTemperature = getTemperatureSmooth();
        m_isTriggered = true;
      //  Serial.println("trig !");
    }


}

boolean RTDTrigger::isTriggered(void)
{
    boolean tmp = m_isTriggered;
    m_isTriggered = false;
    return tmp;
}

double RTDTrigger::GetTrigTemperature(void)
{
    return previousTemperature;
}

