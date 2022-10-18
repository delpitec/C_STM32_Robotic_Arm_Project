#include "RobotFunctions.h"
//
//long map(long x, long in_min, long in_max, long out_min, long out_max)
//{
//  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
//}

void FindHomePosition(Axis axis){
	SetOutputBTS2960(axis.shield, axis.minSpeed, axis.firstMove);
	while (HAL_GPIO_ReadPin(axis.HomePort, axis.HomePin)){
		;
	}

	StopBTS2960(axis.shield);
    HAL_Delay(1500);

    *axis.position = 0;

    SetOutputBTS2960(axis.shield, axis.minSpeed, !axis.firstMove);
    while (!HAL_GPIO_ReadPin(axis.HomePort, axis.HomePin)){
		;
	}

    StopBTS2960(axis.shield);
    HAL_Delay(1000);

}

void MoveToPosition(Axis axis, unsigned int setPoint){

	long int error = *axis.position - setPoint;

	if (error < 0){
		SetOutputBTS2960(axis.shield, axis.minSpeed, !axis.firstMove);
		while (*axis.position < setPoint){
			;
		}
		StopBTS2960(axis.shield);
	}
	else if (error > 0){
		SetOutputBTS2960(axis.shield, axis.minSpeed, axis.firstMove);
		while (*axis.position > setPoint){
			;
		}
		StopBTS2960(axis.shield);
	}
	else{
		;
	}
}

void MoveToPositionPID(Axis *axis, unsigned int setPoint){
	int pidOutput = 0;
	int output = 0;

	pidOutput = PIDController(&axis->pidPos, *axis->position, setPoint);

	//PidController(&axis.pid, pidOutput + 1000, enc_1_speed);

	// Normilized output
	if (pidOutput > 0){
		output = pidOutput/12;
		SetOutputBTS2960(axis->shield, output, !axis->firstMove);
	}
	else {
		output = pidOutput/12;
		SetOutputBTS2960(axis->shield, output, axis->firstMove);
	}

}








