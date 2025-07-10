#ifndef CHRONO_H
#define CHRONO_H
#include <arduino.h>

class Chrono
{
    public:
        Chrono();
        ~Chrono();
        boolean isStarted() { return m_isStarted; }
        void chronoStart(void);
        void chronoStop(void);
        unsigned long chronoRead(void);
    protected:
    private:
        unsigned long m_startTime;
        boolean m_isStarted;
};

#endif // CHRONO_H
