#include "RobotFunctions.h"

void PrintSpeed(int mapE1){
    static char UartTX[200] = {0};
    //const char CLRSCR[] = "\033[0H\033[0J";  // Clear terminal

	//HAL_UART_Transmit(&huart1, (unsigned char *)CLRSCR, strlen((const char *)CLRSCR), 100);

	sprintf((char *)UartTX,
	  	   "\n\rE1S: % 06d | mapE1S: % 06d\n\r"
		   "E2S: % 06d\n\r"
		   "E3S: % 06d\n\r"
		   "E4S: % 06d\n\r",
			enc_1_speed, mapE1,
			enc_2_speed,
			enc_3_speed,
			enc_4_speed
	);

	HAL_UART_Transmit(&huart1, (unsigned char *)UartTX, strlen((const char *)UartTX), 500);
	HAL_Delay(100);

}

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

	int mappedSpeed = map(*axis->speed, axis->pidSpeed.minProcessVariable, axis->pidSpeed.maxProcessVariable, -1000, 1000);
	pidOutput = PIDController(&axis->pidSpeed, mappedSpeed, pidOutput);

	PrintSpeed(mappedSpeed);

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








