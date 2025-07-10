/*
||
|| @file Scheduler.h
|| @version 1.0
|| @author Alexander Brevig/V.Remy
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Provide an easy way of scheduling timer event by means of a function call
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

#ifndef SCHEDULER_H
#define SCHEDULER_H

#ifndef VR_SIM
#include <arduino.h>
#define bool boolean
#endif // VR_SIM


typedef unsigned short TokenTimer_t;
//provide a typedef for a void function pointer
typedef void (*function)(TokenTimer_t);
typedef unsigned long (*functionTime)(void);

typedef struct
{
	unsigned long StartTime;
	unsigned long delay;
	bool IsStarted;
	bool Elapsed;
	bool Allocated;
} TimerStruct_t;

class Scheduler {
	public:
		Scheduler();
		Scheduler(int nbtoken);
		void update();
		void schedule(function userAction, functionTime userTime);
		TokenTimer_t GetTimerToken(void);
		bool TimerStart(TokenTimer_t tokenTimer,unsigned long delay);
		void TimerStop (TokenTimer_t tokenTimer);
		bool IsTimerStarted (TokenTimer_t tokenTimer);
		bool IsTimerElapsed(TokenTimer_t tokenTimer);
		void SetTimerElapsed (TokenTimer_t tokenTimer);

	private:
	    static const unsigned char POOL_OF_TIMERS = 4;
	    TimerStruct_t poolOfTimers[POOL_OF_TIMERS];
		function action;
		functionTime millis;
		unsigned char currentSize;
};

#endif

