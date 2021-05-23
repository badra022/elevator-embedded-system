#include "Main.h"
#include "Port.h"
#include "Common.h"
#include "switch.h"

void SWITCH_Init(tSwitch switch_number)
{
  /* Configure switch pins as digital inputs */
  switch (switch_number)
  {
      case UP:
          GPIO_InitPortPin(UP_SWITCH_PORT_CR, UP_SWITCH_PIN, GPIO_IN);
          GPIO_WritePortPin(UP_SWITCH_PORT_DR, UP_SWITCH_PIN, HIGH);
          break;
      case DOWN:
          GPIO_InitPortPin(DOWN_SWITCH_PORT_CR, DOWN_SWITCH_PIN, GPIO_IN);
          GPIO_WritePortPin(DOWN_SWITCH_PORT_DR, DOWN_SWITCH_PIN, HIGH);
          break;
      case FLOOR1:
          GPIO_InitPortPin(FLOOR_1_SWITCH_PORT_CR, FLOOR_1_SWITCH_PIN, GPIO_IN);
          GPIO_WritePortPin(FLOOR_1_SWITCH_PORT_DR, FLOOR_1_SWITCH_PIN, HIGH);
          break;
      case FLOOR2:
          GPIO_InitPortPin(FLOOR_2_SWITCH_PORT_CR, FLOOR_2_SWITCH_PIN, GPIO_IN);
          GPIO_WritePortPin(FLOOR_2_SWITCH_PORT_DR, FLOOR_2_SWITCH_PIN, HIGH);
          break;
      case FLOOR3:
          GPIO_InitPortPin(FLOOR_3_SWITCH_PORT_CR, FLOOR_3_SWITCH_PIN, GPIO_IN);
          GPIO_WritePortPin(FLOOR_3_SWITCH_PORT_DR, FLOOR_3_SWITCH_PIN, HIGH);
          break;
      case FLOOR4:
          GPIO_InitPortPin(FLOOR_4_SWITCH_PORT_CR, FLOOR_4_SWITCH_PIN, GPIO_IN);
          GPIO_WritePortPin(FLOOR_4_SWITCH_PORT_DR, FLOOR_4_SWITCH_PIN, HIGH);
          break;
      case GROUND:
          GPIO_InitPortPin(FLOOR_0_SWITCH_PORT_CR, FLOOR_0_SWITCH_PIN, GPIO_IN);
          GPIO_WritePortPin(FLOOR_0_SWITCH_PORT_DR, FLOOR_0_SWITCH_PIN, HIGH);
          break;
      case OPEN:
          GPIO_InitPortPin(OPEN_SWITCH_PORT_CR, OPEN_SWITCH_PIN, GPIO_IN);
          GPIO_WritePortPin(OPEN_SWITCH_PORT_DR, OPEN_SWITCH_PIN, HIGH);
          break;
      case INCREASE:
          GPIO_InitPortPin(INCREASE_SWITCH_PORT_CR, INCREASE_SWITCH_PIN, GPIO_IN);
          GPIO_WritePortPin(INCREASE_SWITCH_PORT_DR, INCREASE_SWITCH_PIN, HIGH);
          break;
      case DECREASE:
          GPIO_InitPortPin(DECREASE_SWITCH_PORT_CR, DECREASE_SWITCH_PIN, GPIO_IN);
          GPIO_WritePortPin(DECREASE_SWITCH_PORT_DR, DECREASE_SWITCH_PIN, HIGH);
          break;
      default:
          /* Should not come here */
          break;
  }
}

tSwitch_state SWITCH_Read(tSwitch switch_number)
{
    tSwitch_state ret = NOT_PRESSED;

    /* read specific switch state */
    switch (switch_number)
    {
        case UP:
            ret = GPIO_ReadPortPin(UP_SWITCH_PORT_DR, UP_SWITCH_PIN);
            break;
        case DOWN:
            ret = GPIO_ReadPortPin(DOWN_SWITCH_PORT_DR, DOWN_SWITCH_PIN);
            break;
        case FLOOR1:
            ret = GPIO_ReadPortPin(FLOOR_1_SWITCH_PORT_DR, FLOOR_1_SWITCH_PIN);
            break;
        case FLOOR2:
            ret = GPIO_ReadPortPin(FLOOR_2_SWITCH_PORT_DR, FLOOR_2_SWITCH_PIN);
            break;
        case FLOOR3:
            ret = GPIO_ReadPortPin(FLOOR_3_SWITCH_PORT_DR, FLOOR_3_SWITCH_PIN);
            break;
        case FLOOR4:
            ret = GPIO_ReadPortPin(FLOOR_4_SWITCH_PORT_DR, FLOOR_4_SWITCH_PIN);
            break;
        case GROUND:
            ret = GPIO_ReadPortPin(FLOOR_0_SWITCH_PORT_DR, FLOOR_0_SWITCH_PIN);
            break;
        case INCREASE:
            ret = GPIO_ReadPortPin(INCREASE_SWITCH_PORT_DR, INCREASE_SWITCH_PIN);
            break;
        case DECREASE:
            ret = GPIO_ReadPortPin(DECREASE_SWITCH_PORT_DR, DECREASE_SWITCH_PIN);
            break;
        default:
            /* Should not come here */
            break;
    }
    return ret;
}
