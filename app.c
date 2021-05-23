#include "Main.h"
#include "Port.h"
#include "Common.h"
#include "LED.h"
#include "sevenSeg.h"
#include "switch.h"

#define SYSTEM_TICKS			(10)
#define TOP_FLOOR					(4)
#define GND_FLOOR					(0)
#define MAX_PERSONS				(4)
#define MIN_PERSONS				(1)
#define EMPTY							(0)

void main()
{
		/* GLOBAL variables used in the application (initial states of the system) */
		unsigned char i = 0;
		unsigned int system_ticks = 0;
		unsigned char UP_Flag = FALSE;
		unsigned char DOWN_Flag = FALSE;
		unsigned char OPEN_Flag = TRUE;
		unsigned char currentFloor = GND_FLOOR;
		unsigned char comingFloor = GND_FLOOR;
		unsigned char requestedFloors[] = {FALSE, FALSE, FALSE, FALSE, FALSE};
		unsigned char firstTime = TRUE;
		unsigned char persons = EMPTY;

    // diable the watch dog
    WDTCN = 0x0DE;
    WDTCN = 0x0AD;

    OSCICN = 0x014; // 2MH clock

    // config cross bar
    XBR0 = 0x00;
    XBR1 = 0x00;
    XBR2 = 0x040; // Cross bar enabled , weak Pull-up enabled

		/* initializing all the hardware dependencies */
		SWITCH_Init(UP);
		SWITCH_Init(DOWN);
		SWITCH_Init(GROUND);
		SWITCH_Init(FLOOR1);
		SWITCH_Init(FLOOR2);
		SWITCH_Init(FLOOR3);
		SWITCH_Init(FLOOR4);
		SWITCH_Init(OPEN);
		SWITCH_Init(INCREASE);
		SWITCH_Init(DECREASE);
		LED_Init(MOTOR, LED_OFF);
		LED_Init(MOVING, LED_OFF);
		LED_Init(OPEN_LED, LED_ON);
		LED_Init(ALARM, LED_OFF);
    sevenSeg_init();

		sevenSeg_write(i % 10);
		i++;

    while (1)
    {

			if(firstTime == TRUE){
					/* first time to execute this code the elevator is on GROUND */
					/* opening the door for 2 seconds */
					LED_SetState(MOTOR, LED_ON);
					Delay_MS(2 * SECOND_DELAY);
					/* turning open Led ON */
					LED_SetState(OPEN_LED, LED_ON);
					system_ticks = 0;
					/* wait 5 seconds (while checking the UP button request) */
					while(system_ticks != 5 * SYSTEM_TICKS)
					{
							if(SWITCH_Read(UP) == PRESSED)
							{
								UP_Flag = TRUE;
							}
							if(SWITCH_Read(INCREASE) == PRESSED){persons++;}
							while(SWITCH_Read(INCREASE) == PRESSED);

							if(SWITCH_Read(DECREASE) == PRESSED){persons > MIN_PERSONS?persons-- : MIN_PERSONS;}
							while(SWITCH_Read(DECREASE) == PRESSED);

							if(persons > MAX_PERSONS)
							{
								LED_SetState(ALARM, LED_ON);
							}
							else{
								system_ticks++;
							}
							Delay_MS(SECOND_DELAY/SYSTEM_TICKS);
					}
						LED_SetState(OPEN_LED, LED_OFF);
		}


				system_ticks = 0;
				while(system_ticks != 1 * SYSTEM_TICKS)
				{
						system_ticks++;
						if(SWITCH_Read(UP) == PRESSED)
						{
							i = 0;
						}
		        Delay_MS(SECOND_DELAY/SYSTEM_TICKS);
				}
    }
}
