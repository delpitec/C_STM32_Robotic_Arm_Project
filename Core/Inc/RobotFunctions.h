#ifndef INC_ROBOTFUNCTIONS_H_
#define INC_ROBOTFUNCTIONS_H_

#include <stdint.h> // uint8_t ....
#include <stdio.h>  // sprintf()
#include <string.h> // tratamento de string
#include "main.h"
#include "bts7960.h"
#include "PID.h"

typedef struct AXIS{
	BTS2960 shield;
	GPIO_TypeDef  *HomePort;
	uint16_t      HomePin;
	PID 		  pidPos;
	PID 		  pidSpeed;
	int           *speed;
	unsigned int  *position;
	unsigned char firstMove;
	unsigned int  minSpeed;
}Axis;

typedef struct SETPOINT{
	unsigned int Axis1;
	unsigned int Axis2;
	unsigned int Axis3;
	unsigned int Axis4;
}SetPoint;

void FindHomePosition(Axis axis);
void MoveToPosition(Axis axis, unsigned int setPoint);
void MoveToPositionPID(Axis *axis, unsigned int setPoint);



#endif /* INC_ROBOTFUNCTIONS_H_ */
