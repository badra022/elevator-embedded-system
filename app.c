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
#define FLOORS_NUMBER			(5)


void loadElevator_Task(unsigned char *requestedFloors, unsigned char *persons)
{
	unsigned int system_ticks = 0;
	/* opening the door for 2 seconds */
	LED_SetState(MOTOR, LED_ON);
	Delay_MS(2 * SECOND_DELAY);
	LED_SetState(MOTOR, LED_OFF);
	/* turning open Led ON */
	LED_SetState(OPEN_LED, LED_ON);
	system_ticks = 0;
	/* wait 5 seconds (while checking the UP button request) */
	while(system_ticks != 5 * SYSTEM_TICKS)
	{
			/* check some buttons while waiting */
			if(SWITCH_Read(UP) == PRESSED)
			{
				requestedFloors[5] = TRUE;
			}
			if(SWITCH_Read(DOWN) == PRESSED)
			{
				requestedFloors[0] = TRUE;
			}
			if(SWITCH_Read(INCREASE) == PRESSED){(*persons)++;}
			while(SWITCH_Read(INCREASE) == PRESSED);

			if(SWITCH_Read(DECREASE) == PRESSED){persons > MIN_PERSONS?(*persons)-- : MIN_PERSONS;}
			while(SWITCH_Read(DECREASE) == PRESSED);

			if(*persons > MAX_PERSONS)
			{
				LED_SetState(ALARM, LED_ON);
			}
			else{
				system_ticks++;
			}

			if(SWITCH_Read(BLOCK_DOOR) == PRESSED || SWITCH_Read(OPEN) == PRESSED || *persons == 0)
			{
				system_ticks = 0; /* Reload the 5 second delay */
			}
			Delay_MS(SECOND_DELAY/SYSTEM_TICKS);
	}
		LED_SetState(OPEN_LED, LED_OFF);
		/* closing the door of the elevator after the 5 seconds delay */
		LED_SetState(MOTOR, LED_ON);
		Delay_MS(2 * SECOND_DELAY);
		LED_SetState(MOTOR, LED_OFF);

}

/* a 5 seconds Routine for selecting the floors they want the elevator to go to ( they can Reopen the door for 5 seconds if thety want) */
Return_state selectFloors_Task(unsigned char *requestedFloors)
{
	unsigned int system_ticks = 0;
	while(system_ticks != 5 * SYSTEM_TICKS)
	{
		system_ticks++;
		if(SWITCH_Read(OPEN) == PRESSED)
		{
			return FAILURE;
		}
		if(SWITCH_Read(GROUND) == PRESSED || SWITCH_Read(DOWN) == PRESSED)
		{
			requestedFloors[0] = TRUE;
		}
		else if(SWITCH_Read(FLOOR1) == PRESSED)
				{
					requestedFloors[1] = TRUE;
				}
		else if(SWITCH_Read(FLOOR2) == PRESSED)
				{
					requestedFloors[2] = TRUE;
				}
		else if(SWITCH_Read(FLOOR3) == PRESSED)
				{
					requestedFloors[3] = TRUE;
				}
		else if(SWITCH_Read(FLOOR4) == PRESSED || SWITCH_Read(UP) == PRESSED)
				{
					requestedFloors[4] = TRUE;
				}

		Delay_MS(SECOND_DELAY/SYSTEM_TICKS);
	}
	return SUCCESS;
}

/* process of moving the elevator from the currentFloor to the comingFloor (checking the Up and Down Flags through the process)*/
void moveElevator_Task(unsigned char *currentFloor, unsigned char *comingFloor)
{
	
}




void main()
{
		/* GLOBAL variables used in the application (initial states of the system) */
		unsigned char i = 0;
		unsigned int system_ticks = 0;
		unsigned char currentFloor = GND_FLOOR;
		unsigned char comingFloor = GND_FLOOR;
		unsigned char requestedFloors[] = {FALSE, FALSE, FALSE, FALSE, FALSE};
		unsigned char persons = EMPTY;
		unsigned char dummyVar = 0;

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
		SWITCH_Init(BLOCK_DOOR);
		LED_Init(MOTOR, LED_OFF);
		LED_Init(MOVING, LED_OFF);
		LED_Init(OPEN_LED, LED_ON);
		LED_Init(ALARM, LED_OFF);
    sevenSeg_init();

    while (1)
    {
				loadElevator_Task(requestedFloors, &persons);

				/* if the users pressed OPEN button, this statement will be FALSE */
				if(selectFloors_Task(requestedFloors) == SUCCESS)
				{
					/* check if the user selected some floors or Not */
					comingFloor = (comingFloor + 1)% FLOORS_NUMBER;
					while(comingFloor != currentFloor && requestedFloors[comingFloor] == FALSE){
						comingFloor = (comingFloor + 1)% FLOORS_NUMBER;
					}
					if(comingFloor != currentFloor){
						/* there's some Floors to visit */
						moveElevator_Task(&currentFloor, &comingFloor);
					}
					else
					{
						/* there's no selected floors remained and No Up or Down Requests */
						/* Do Nothing Here */
					}
				}
    }
}
