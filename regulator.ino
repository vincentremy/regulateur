//----------------------------------------------------------------------------
// Regulator module
// Last revision 30 Jan 2014
// Licence: GNU GPL
//----------------------------------------------------------------------------
#include <stdio.h>
#include <Arduino.h>
#include <Servo.h>
#include <Flash.h>

#include "log.h"
#include "monitor.h"
#include "RTDTrigger.h"
#include "Scheduler.h"
#include "melody.h"
#include "keyboard.h"

Servo myservo;  // create servo object to control a servo
byte fan_pin = 6;
Scheduler scheduler = Scheduler();      //create a scheduler

RTDTrigger rtdA0 = RTDTrigger(10.0);
RTDTrigger rtdA1 = RTDTrigger(0.5);

TokenTimer_t disableTemperatureReading;

double targetTemperature;


#define SCALE_LM35 (1.1/1024*100) // = 0,01v per ¡ãc


// create a FILE structure to reference our UART output function
static FILE uartout = {0} ;

// Set valve opening %
#define VALVE_FULL_OPEN 100
#define VALVE_CLOSE 0

#define VALVE_CLOSE_ANGLE 150
#define VALVE_FULL_OPEN_ANGLE 60

void SetValveOpening(byte val)
{
    byte angle;
    if(val >= 100)
    {
        val = 100;
    }
    if(val < 0)
    {
        val = 0;
    }
    angle = ((VALVE_CLOSE_ANGLE-VALVE_FULL_OPEN_ANGLE)*val)/100 + VALVE_FULL_OPEN_ANGLE;
    myservo.attach(4);   // attaches the servo on pin 4 to the servo object
    scheduler.TimerStart(disableTemperatureReading,10000);
    myservo.write(angle);
    delay(500);
    myservo.detach();
}

void AnalyseKeyboardRequest(eRemoteIR cmd)
{
    switch(cmd)
    {
    case START_RM:
        // reset state machine
        break;
    case MODE_RM:
        // Chargement bois
        break;
    case HP_RM:
        // Stop FAN
        break;
    case PLAY_RM:
        // FAN on
        break;
    case REWARD_RM:
        //FAN --;
        break;
    case FORWARD_RM:
        // FAN ++
        break;


    case ZERO_RM:
    case ONE_RM:
    case TWO_RM:
    case THREE_RM:
    case FOUR_RM:
    case FIVE_RM:
    {
        targetTemperature = 20 + ((double)cmd - (double)ZERO_RM);
        Serial << F("Target temperature:") << targetTemperature << F("C\r\n");
    }
    break;
    default:
        break;
    }

}

// Dumps out the decode_results structure.
// Call this after IRrecv::decode()
// void * to work around compiler issue
//void dump(void *v) {
//  decode_results *results = (decode_results *)v
void decodeRemote(decode_results *results)
{
    //Serial << F("Raw:");
    //Serial.println(results->value, HEX);
    switch(results->decode_type)
    {
    case NEC:
    {
        eRemoteIR ir = ConvRemoteValueToKey(results);
        LogPrintf(STANDARD_LOG,"Ir:%d\n",ir);
        if(ir >= START_RM && ir < LAST_RM_ITEM)
        {
            playMelodyAck();
            AnalyseKeyboardRequest(ir);

        }
        else
        {
            //playMelodyNak();
            //playMelodyOff();
        }
    }
    break;
    default:
        LogPrintf(STANDARD_LOG,"Unknown encoding:\n");
        break;
    }

}


// create a output function
// This works because Serial.write, although of
// type virtual, already exists.
static int uart_putchar (char c, FILE *stream)
{
    if(c == '\n')
    {
        Serial.write('\r');
    }
    Serial.write(c);
    return 0 ;
}

void PublishEvent(TokenTimer_t tk)
{

    Serial << "timer elapsed " << millis() << F(" ms") << F(",token=") << tk << F("\n\r") ;

}
//--------------------------------------------------------------
// Setup
//----------------------------------------------------------------------------
void setup()
{
    Serial.begin(9600/*115200*/);
    // fill in the UART file descriptor with pointer to writer.
    fdev_setup_stream (&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);

    // The uart is the standard output device STDOUT.
    stdout = &uartout ;


    rtdA0.setPins(A0);                                // A0 is analog input
    //rtd.calibration(scaler, offset )
    rtdA0.calibration(0.34615, -20.3845);
    rtdA1.setPins(A1);                                // A1 is analog input
    rtdA1.calibration(SCALE_LM35, -2.0);
    analogReference(INTERNAL);                        //Set reference to 1.1V ready for RTD measurements

    InitMonitor();
    IRemoteInit();
    pinMode(6, OUTPUT);	 // Fan
    pinMode(3, OUTPUT);	 //buzzer

    scheduler.schedule(PublishEvent, millis);
    disableTemperatureReading = scheduler.GetTimerToken();
}

//----------------------------------------------------------------------------
// Main loop
//----------------------------------------------------------------------------

void loop()
{
    scheduler.update();
    //Update temperatures and pass through digital low pass filter
    if(scheduler.IsTimerStarted(disableTemperatureReading) == false)
    {
        rtdA0.UpdateTrigger();
        rtdA1.UpdateTrigger();
    }

    if(rtdA0.isTriggered() == true)
    {
        LogPrintf(STANDARD_LOG,"filt. pt1000:");
        Serial << rtdA0.GetTrigTemperature();
        Serial << F(" A0 raw:");
        Serial.println(rtdA0.getTemperature());
    }

    if(rtdA1.isTriggered() == true)
    {
        LogPrintf(STANDARD_LOG,"filt. lm35:");
        Serial << rtdA1.GetTrigTemperature();
        Serial << F(" A1 raw:");
        Serial.println(rtdA1.getTemperature());
    }

//    if (Serial.available() > 0) {
//        printf("test:%c\n",Serial.read());
//    }
    MonitorHandling();

    if (irrecv.decode(&results))
    {
        //Serial.println(results.value, HEX);
        decodeRemote(&results);
        irrecv.resume(); // Receive the next value
    }


}
//----------------------------------------------------------------------------

