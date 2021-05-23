#include "Main.h"
#include "Port.h"
#include "Common.h"
#include "sevenSeg.h"

char numbers[] = {0x0C0, 0x0F9, 0x0A4, 0x0B0, 0x99, 0x92, 0x82, 0x0F8, 0x80, 0x90};

void sevenSeg_init(void)
{
    GPIO_InitPort(SEVEN_SEGMENT_DIR_PORT, GPIO_OUT);
    GPIO_WritePort(SEVEN_SEGMENT_DATA_PORT, numbers[0]);
}

void sevenSeg_write(unsigned char number_index)
{
    GPIO_WritePort(SEVEN_SEGMENT_DATA_PORT, numbers[number_index]);
}
