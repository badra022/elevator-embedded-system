#ifndef __COMMON_H__
#define __COMMON_H__

void Delay_MS(int ms);

#define HIGH    (1u)
#define LOW     (0u)

#define TRUE    (1u)
#define FALSE   (0u)

#define SECOND_DELAY		(1000)

typedef enum
{
  FAILURE,
  SUCCESS
}Return_state;

typedef unsigned char uint8; 

#endif
