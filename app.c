#include "Main.h"
#include "Port.h"
#include "Common.h"
#include "LED.h"
#include "sevenSeg.h"
#include "switch.h"

#define SYSTEM_TICKS			(10)

void main()
{
		unsigned char i = 0;
		unsigned int system_ticks = 0;

    // diable the watch dog
    WDTCN = 0x0DE;
    WDTCN = 0x0AD;

    OSCICN = 0x014; // 2MH clock

    // config cross bar
    XBR0 = 0x00;
    XBR1 = 0x00;
    XBR2 = 0x040; // Cross bar enabled , weak Pull-up enabled
		SWITCH_Init(UP);
    sevenSeg_init();

    while (1)
    {
				sevenSeg_write(i % 10);
				i++;

				system_ticks = 0;
				while(system_ticks != 1 * SYSTEM_TICKS)
				{
						system_ticks++;
						if(SWITCH_Read(UP) == PRESSED)
						{
							i = 0;
						}
		        Delay_MS(100);
				}
    }
}
