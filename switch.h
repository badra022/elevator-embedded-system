#ifndef __LED_H__
#define __LED_H__

#define LED_DELAY_MS (1000)

typedef enum
{
  UP,
  DOWN,
  GROUND,
  FLOOR1,
  FLOOR2,
  FLOOR3,
  FLOOR4
}tSwitch;

typedef enum

{
   LED_OFF,
   LED_ON
}tLED_State;


void LED_Init(tLED led, tLED_State state);
void LED_SetState(tLED led, tLED_State state);
tLED_State LED_GetState(tLED led);
void LED_Toggle(tLED led);

#endif // __LED_H__
