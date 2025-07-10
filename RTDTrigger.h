#ifndef RTDTRIGGER_H
#define RTDTRIGGER_H

#include "RTDmodule.h"

class RTDTrigger : public RTDModule
{
public:
    RTDTrigger(double _temperatureTrigLevel = 1.0);
//   virtual ~RTDTrigger();
    void UpdateTrigger(void);
    double GetTrigTemperature(void);
    boolean isTriggered(void);

private:
    double temperatureTrigLevel;
    double previousTemperature;
    boolean m_isTriggered;
};

#endif // RTDTRIGGER_H
