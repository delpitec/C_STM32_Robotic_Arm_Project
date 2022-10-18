/*
 * PID.h
 *
 *  Created on: Oct 1, 2022
 *      Author: Rafael
 */

#include "main.h"
#include <stdio.h>
#include <string.h>

#ifndef INC_PID_H_
#define INC_PID_H_

typedef struct PID{
	const float        kp;
	const float   	   ki;
	const float   	   kd;
	const unsigned int minNormilizedValue;
	const unsigned int maxNormilizedValue;
	const unsigned int minProcessVariableValue;
	const unsigned int maxProcessVariableValue;
	const unsigned int minSetPointValue;
	const unsigned int maxSetPointValue;
	int                P_error;
	int                I_error;
	int                D_error;
	unsigned int  	   lastProcessVariableValue;
	unsigned long 	   timeStamp;
}PID;

long map(long x, long in_min, long in_max, long out_min, long out_max);
void PrintParametersOverSerial(int err, int pid, int p,int i, int d);

int PIDController(PID *pid, unsigned int position, unsigned int setPoint);

#endif /* INC_PID_H_ */
