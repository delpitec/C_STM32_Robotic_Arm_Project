#ifndef INC_ROBOTFUNCTIONS_H_
#define INC_ROBOTFUNCTIONS_H_

#include <stdint.h> // uint8_t ....
#include <stdio.h>  // sprintf()
#include <string.h> // tratamento de string
#include "main.h"
#include "bts7960.h"

typedef struct AXIS{
	BTS2960 shield;
	unsigned int position;

}Axis;

void PrintParametersOverSerial(void);

void FindHomePosition(Axis axis);

#endif /* INC_ROBOTFUNCTIONS_H_ */
