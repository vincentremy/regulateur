#include <arduino.h>
#include "pitches.h"


/* Cue Star Wars - Darth Vader theme, opening notes! */

int melody_nak[] = {NOTE_G5, NOTE_G5, NOTE_G5, NOTE_DS5, NOTE_AS5, NOTE_G5, NOTE_DS5, NOTE_AS5, NOTE_G5};
int noteDurations_nak[] = { 330, 330, 330, 250, 120, 330, 250, 120, 500 };

//int melody_ack[] = { NOTE_D6, NOTE_A6, NOTE_C7, NOTE_A6 };
//int noteDurations_ack[] = { 120, 500, 120, 500 };
int melody_ack[] = { NOTE_D6 };
int noteDurations_ack[] = {120};


int melody_off[] = { NOTE_A6, NOTE_A5, NOTE_A3 };
int noteDurations_off[] = {330, 330, 330};


void toneManual(int pin, int frequency, int duration)
{
    unsigned long period = 1000000/frequency;
    unsigned long length;
    boolean state = false;

    for (length = 0; length < (long) duration * 1000; length += period)
    {
        state = !state;
        digitalWrite(pin, state);
        /* The 50uS correspond to the time the rest of the loop body takes.     * It seems about right, but has not been tuned precisely for     * a 16MHz ATMega. */		delayMicroseconds(period - 50);
    }
}

void playMelody(int *melody, int *noteDurations, int notes)
{
    int i;
    for (i = 0; i < notes; i++)
    {
        toneManual(3, melody[i], noteDurations[i]);
        delay(noteDurations[i] * 6/10);
    }
}
void playMelodyAck()
{
    playMelody(melody_ack, noteDurations_ack, sizeof(melody_ack)/sizeof(melody_ack[0]));
}

void playMelodyNak()
{
    playMelody(melody_nak, noteDurations_nak, sizeof(melody_nak)/sizeof(melody_nak[0]));
}

void playMelodyOff()
{
    playMelody(melody_off, noteDurations_off, sizeof(melody_off)/sizeof(melody_off[0]));
}
