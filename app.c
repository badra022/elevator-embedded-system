#include "Main.h"
#include "Port.h"
#include "Common.h"
#include "LED.h"

void main()
{
    
    // diable the watch dog
    WDTCN = 0x0DE;
    WDTCN = 0x0AD;

    OSCICN = 0x014; // 2MH clock

    // config cross bar
    XBR0 = 0x00;
    XBR1 = 0x00;
    XBR2 = 0x040; // Cross bar enabled , weak Pull-up enabled
    
    LED_Init(LED_0, LED_OFF);
    LED_Init(LED_1, LED_ON);
    LED_Init(LED_2, LED_OFF);
    LED_Init(LED_3, LED_ON);

    while (1)
    {
        LED_Toggle(LED_0);
        LED_Toggle(LED_1);
        LED_Toggle(LED_2);
        LED_Toggle(LED_3);
        Delay_MS(LED_DELAY_MS);
    }
}