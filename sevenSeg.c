#include "Main.h"
#include "Port.h"
#include "Common.h"
#include "sevenSeg_private.h"
#include "sevenSeg.h"

void sevenSeg_init(void)
{
    GPIO_InitPort(SEVEN_SEGMENT_DIR_PORT, GPIO_OUT);
    GPIO_WritePort(SEVEN_SEGMENT_DATA_PORT, numbers[0]);
}

void sevenSeg_write(unsigned char number_index)
{
    GPIO_WritePort(SEVEN_SEGMENT_DATA_PORT, numbers[number_index]);
}
