#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED
#include "IRremote.h"
typedef enum
{
    FIRST_RM_ITEM,
    START_RM = FIRST_RM_ITEM,
    MODE_RM,
    HP_RM,
    PLAY_RM,
    REWARD_RM,
    FORWARD_RM,
    EQ_RM,
    MINUS_RM,
    PLUS_RM,
    ZERO_RM,
    ONE_RM,
    TWO_RM,
    THREE_RM,
    FOUR_RM,
    FIVE_RM,
    LAST_RM_ITEM
} eRemoteIR;

extern IRrecv irrecv;
extern decode_results results;
void IRemoteInit(void);
eRemoteIR ConvRemoteValueToKey(decode_results *results);
#endif // KEYBOARD_H_INCLUDED
