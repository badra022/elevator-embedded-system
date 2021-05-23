#include "Main.h"
#include "Port.h"
#include "Common.h"
#include "Led.h"


void LED_Init(tLED led, tLED_State state)
{
    /* Add your code here! */
    /* Configure led pins as output */
    switch (led)
    {
        case MOTOR:
            GPIO_InitPortPin(MOTOR_PORT_CR, MOTOR_PIN, GPIO_OUT);
            break;
        case MOVING:
            GPIO_InitPortPin(MOVING_PORT_CR, MOVING_PIN, GPIO_OUT);
            break;
        case OPEN_LED:
            GPIO_InitPortPin(OPEN_LED_PORT_CR, OPEN_LED_PIN, GPIO_OUT);
            break;
        case ALARM:
            GPIO_InitPortPin(ALARM_PORT_CR, ALARM_PIN, GPIO_OUT);
            break;
        default:
            /* Should not come here */
            break;
    }
    /* Set led state */
    LED_SetState(led, state);
    /* End of your code */

}

void LED_Toggle(tLED led)
{
    /* Add your code here! */
    /* Toggle led */
    if (LED_GetState(led) == LED_ON)
    {
        LED_SetState(led, LED_OFF);
    } else
    {
        LED_SetState(led, LED_ON);
    }

    /* Delay to show toggling effect */
    // Delay_MS(LED_DELAY_MS);
    /* End of your code */
}


void LED_SetState(tLED led, tLED_State state)
{
    /* Add your code here! */
    /* Set led state */
    switch (led)
    {
        case MOTOR:
            GPIO_WritePortPin(MOTOR_PORT_DR, MOTOR_PIN, state);
            break;
        case MOVING:
            GPIO_WritePortPin(MOVING_PORT_DR, MOVING_PIN, state);
            break;
        case OPEN_LED:
            GPIO_WritePortPin(OPEN_LED_PORT_DR, OPEN_LED_PIN, state);
            break;
        case ALARM:
            GPIO_WritePortPin(ALARM_PORT_DR, ALARM_PIN, state);
            break;
        default:
            /* Should not come here */
            break;
    }
    /* End of your code */
}

tLED_State LED_GetState(tLED led)
{
    tLED_State ret = LED_OFF;

    /* Add your code here! */
    /* Set led state */
    switch (led)
    {
        case MOTOR:
            ret = GPIO_ReadPortPin(MOTOR_PORT_DR, MOTOR_PIN);
            break;
        case MOVING:
            ret = GPIO_ReadPortPin(MOVING_PORT_DR, MOVING_PIN);
            break;
        case OPEN_LED:
            ret = GPIO_ReadPortPin(OPEN_LED_PORT_DR, OPEN_LED_PIN);
            break;
        case ALARM:
            ret = GPIO_ReadPortPin(ALARM_PORT_DR, ALARM_PIN);
            break;
        default:
            /* Should not come here */
            break;
    }
    /* End of your code */
    return ret;
}
