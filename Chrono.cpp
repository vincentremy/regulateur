#include "Chrono.h"

Chrono::Chrono()
{
    chronoStop();//ctor
}

Chrono::~Chrono()
{
    //dtor
}
/*************************************************************************
 * Public function. See header file for details.
 ************************************************************************/
void Chrono::chronoStart (void)
{
	m_isStarted = true;
	m_startTime = millis();
}

/*************************************************************************
 * Public function. See header file for details.
 ************************************************************************/
void Chrono::chronoStop (void)
{
	m_isStarted = false;
}


/*************************************************************************
 * Public function. See header file for details.
 ************************************************************************/
unsigned long Chrono::chronoRead (void)
{
	unsigned long Result;

  /* This could overflow after 46 days of non-stop functioning
   * Look at header file for explanations.
   */
	Result = millis() - m_startTime;


  /* If more than 46 days of non-stop operation is required
   * try this:
   * if ( TIME_GetNow () < pChrono->StartTime );
   * {
   *   Result = (0xFFFFFFFF - pChrono->StartTime) + TIME_GetNow () + 1;
   * }
   * else
   *   // Standard case (no overflow)
   *   Result = TIME_GetNow () - pChrono->StartTime;
   * This
   */
	return Result;
}
