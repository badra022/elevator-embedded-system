#ifndef __SWITCH_H__
#define __SWITCH_H__

#define PULL_UP_MODE

typedef enum
{
  UP,
  DOWN,
  GROUND,
  FLOOR1,
  FLOOR2,
  FLOOR3,
  FLOOR4,
  OPEN,
  INCREASE,
  DECREASE
}tSwitch;

#ifdef PULL_UP_MODE
typedef enum
{
  PRESSED,
  NOT_PRESSED
}tSwitch_state;
#elif /* PULL_DOWN_MODE */
typedef enum
{
  NOT_PRESSED,
  PRESSED
}tSwitch_state;
#endif

void SWITCH_Init(tSwitch switch_number);
tSwitch_state SWITCH_Read(tSwitch switch_number);


#endif // __SWITCH_H__
