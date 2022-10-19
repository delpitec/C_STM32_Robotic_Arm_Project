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

	int mappedSetPoint = map(setPoint, axis->pidPos.minProcessVariable, axis->pidPos.maxProcessVariable, axis->pidPos.minNormilized, axis->pidPos.maxNormilized);
	int mappedAxisPosition = map(*axis->position, axis->pidPos.minProcessVariable, axis->pidPos.maxProcessVariable, axis->pidPos.minNormilized, axis->pidPos.maxNormilized);
	pidOutput = PIDController(&axis->pidPos, mappedAxisPosition, mappedSetPoint);

	//int mappedSpeed = map(*axis->speed, axis->pidSpeed.minProcessVariable, axis->pidSpeed.maxProcessVariable, -1000, 1000);
	//pidOutput = PIDController(&axis->pidPos, mappedSpeed, pidOutput);

	// Normilized output
	if (pidOutput > 0){
		output = pidOutput/12;
		SetOutputBTS2960(axis->shield, output, !axis->firstMove);
	}
	else {
		output = ((-1)*(pidOutput))/12;
		SetOutputBTS2960(axis->shield, output, axis->firstMove);
	}

}








