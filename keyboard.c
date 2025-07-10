#include <IRremote.h>
#include <keyboard.h>

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;
void IRemoteInit(void)
{
    irrecv.enableIRIn(); // Start the receiver
}
// ConvRemoteValueToKey
eRemoteIR ConvRemoteValueToKey(decode_results *results)
{
    switch(results->value)
    {

    case 0xFFA25D:
        return START_RM;
    case 0xFF629D:
        return MODE_RM;
    case 0xFFE21D:
        return HP_RM;
    case 0xFFC23D:
        return FORWARD_RM;
    case 0xFF22DD:
        return PLAY_RM;
    case 0xFF02FD:
        return REWARD_RM;
    case 0xFFE01F:
        return EQ_RM;
    case 0xFFA857:
        return MINUS_RM;
    case 0xFF906F:
        return PLUS_RM;
    case 0xFF6897:
        return ZERO_RM;
    case 0xFF30CF:
        return ONE_RM;
    case 0xFF18E7:
        return TWO_RM;
    case 0xFF7A85:
        return THREE_RM;
    case 0xFF10EF:
        return FOUR_RM;
    case 0xFF38C7:
        return FIVE_RM;

    default:
        return LAST_RM_ITEM;
    }
}
