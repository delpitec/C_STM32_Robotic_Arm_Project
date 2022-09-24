#include "RobotFunctions.h"

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
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

// Valores de 0 até MAX count_x
void MoveToPositionPID(Axis axis, unsigned int setPoint){

	static unsigned int  lastPosition = 0;
	static unsigned long timeStamp = 0;
	static int P_error = 0;
	static int I_error = 0;
	static int D_error = 0;

	const float kp = 0.7;
	const float ki = 0.65;
	const float kd = 0.0;

	int output = 0;
	int PID = 0;
	int error = 0;
	float elapsedTime = 0.0;

	// set error (normalized = 0 to 1000)
	error = map(setPoint, 0, 60000, 0, 1000) - map(*axis.position, 0, 60000, 0, 1000);


	lastPosition = *axis.position;

	// Time variables refresh
	elapsedTime = (HAL_GetTick() - timeStamp)/1000.0;
	timeStamp = HAL_GetTick();

	// Refresh PID var errors
	P_error = error;
	I_error = I_error + (error * elapsedTime);
	D_error = (lastPosition - *axis.position) / elapsedTime;

	// Anti wideup (max +/- 1000)
	if (I_error > 1000){
		I_error = 1000;
	}
	else if (I_error < -1000){
		I_error = -1000;
	}
	else{
		;
	}

	// Refresh PID controller
	PID = kp * P_error + ki * I_error + kd * D_error;

	// Anti wideup (max +/- 1000)
	if (PID > 1000){
		PID = 1000;
	}
	else if (PID < -1000){
		PID = -1000;
	}
	else {
		;
	}

	// Normilized output
	if (PID > 0){
		output = PID/12;
		SetOutputBTS2960(axis.shield, output, !axis.firstMove);
	}
	else {
		output = (-1)*(PID/12);
		SetOutputBTS2960(axis.shield, output, axis.firstMove);
	}

	PrintParametersOverSerial(error, PID, P_error,I_error, D_error);
}

void PrintParametersOverSerial(int err, int pid, int p,int i, int d){
    static char UartTX[120] = {0};
    const char CLRSCR[] = "\033[0H\033[0J";  // Clear terminal

	HAL_UART_Transmit(&huart1, (unsigned char *)CLRSCR, strlen((const char *)CLRSCR), 100);

	sprintf((char *)UartTX,
	  	   "\n\r S1: % 06d\n\r"
	  	   " S2: % 06d\n\r"
		   " S3: % 06d\n\r"
		   " S4: % 06d\n\r"
		   " ER: % 06d\n\r"
		   "PID: % 05d\n\r"
		   "  P: % 05d\n\r"
		   "  I: % 05d\n\r"
		   "  D: % 05d\n\r",
			count_1,
			count_2,
			count_3,
			count_4,
			err,
			pid,
			p,
			i,
			d
	);

	HAL_UART_Transmit(&huart1, (unsigned char *)UartTX, strlen((const char *)UartTX), 500);
	HAL_Delay(100);

}




