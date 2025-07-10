/*
||
|| @file Scheduler.h
|| @version 1.1
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Provide an easy way of scheduling function calls
|| #
||
|| @license
|| | This library is free software; you can redistribute it and/or
|| | modify it under the terms of the GNU Lesser General Public
|| | License as published by the Free Software Foundation; version
|| | 2.1 of the License.
|| |
|| | This library is distributed in the hope that it will be useful,
|| | but WITHOUT ANY WARRANTY; without even the implied warranty of
|| | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
|| | Lesser General Public License for more details.
|| |
|| | You should have received a copy of the GNU Lesser General Public
|| | License along with this library; if not, write to the Free Software
|| | Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
|| #
||
*/

#include "Scheduler.h"
#include <stdlib.h>

Scheduler::Scheduler()
{
    action = NULL;
    currentSize = 0;

}

TokenTimer_t Scheduler::GetTimerToken (void)
{
    TokenTimer_t i;
    for(i=0; i < POOL_OF_TIMERS; i++)
    {
        if(poolOfTimers[i].Allocated == false)
        {
            poolOfTimers[i].Allocated = true;
            currentSize++;
            return i;
        }
    }
    // SetPSKError(PSK_SOFTWARE_ERROR,__LINE__, __FILE__);  /* to do with a function pt */
    return 0; /* no more token in the pool, raise error */
}

bool Scheduler::TimerStart (TokenTimer_t tokenTimer, unsigned long delay)
{

    if(poolOfTimers[tokenTimer].Allocated == false)
    {
        return false; // error
    };
    poolOfTimers[tokenTimer].IsStarted = true;
    poolOfTimers[tokenTimer].Elapsed = false;
    poolOfTimers[tokenTimer].StartTime = millis();
    poolOfTimers[tokenTimer].delay = delay;
    return true;

}
void Scheduler::TimerStop (TokenTimer_t tokenTimer)
{
    poolOfTimers[tokenTimer].IsStarted = false;
    poolOfTimers[tokenTimer].Elapsed = false;
}


bool Scheduler::IsTimerStarted (TokenTimer_t tokenTimer)
{
    return poolOfTimers[tokenTimer].IsStarted;
}

/*************************************************************************
 * Public function. See header file for details.
 ************************************************************************/
bool Scheduler::IsTimerElapsed(TokenTimer_t tokenTimer)
{
    return poolOfTimers[tokenTimer].Elapsed;
}

/*************************************************************************
 * Public function. See header file for details.
 ************************************************************************/
void Scheduler::SetTimerElapsed (TokenTimer_t tokenTimer)
{
    poolOfTimers[tokenTimer].Elapsed = true;
}

//Check to see if it's time to call any of the function
void Scheduler::update()
{

    //flush/update all
    for (TokenTimer_t i=0; i<currentSize; i++)
    {
        //it is time to call the function associated with action
        if(poolOfTimers[i].IsStarted == true && poolOfTimers[i].Allocated == true && poolOfTimers[i].Elapsed == false)
        {
            if ((millis() - poolOfTimers[i].StartTime) > poolOfTimers[i].delay)
            {
                action(i); //call function
                poolOfTimers[i].IsStarted = false; // reset the timer
                poolOfTimers[i].Elapsed = true;

            }
        }

    }
}

//Schedule a functioncall
void Scheduler::schedule(function userAction, functionTime userTime)
{

    action = userAction;
    millis = userTime;

}



