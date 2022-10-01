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
	const float kd = 0.3;

	int output = 0;
	int PID_pos = 0;
	int PID_speed = 0;
	int error = 0;
	unsigned int currentPosition = map(*axis.position, 0, 60000, 0, 1000);
	float elapsedTime = 0.0;

	// set error (normalized = 0 to 1000)
	error = map(setPoint, 0, 60000, 0, 1000) - currentPosition;

	// Time variables refresh
	elapsedTime = (HAL_GetTick() - timeStamp)/1000.0;
	timeStamp = HAL_GetTick();

	// Refresh PID var errors
	P_error = error;
	I_error = I_error + (error * elapsedTime);
	D_error = (int)((currentPosition - lastPosition)) / elapsedTime;

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
	PID_pos = kp * P_error + ki * I_error + kd * D_error;

	// next loop variable refresh
	lastPosition = currentPosition;

	// Anti wideup (max +/- 1000)
	if (PID_pos > 1000){
		PID_pos = 1000;
	}
	else if (PID_pos < -1000){
		PID_pos = -1000;
	}
	else {
		;
	}

	// Normilized output
	if (PID_speed > 0){
		output = PID_speed/10;
		SetOutputBTS2960(axis.shield, output, !axis.firstMove);
	}
	else {
		output = (-1)*(PID_speed/10);
		SetOutputBTS2960(axis.shield, output, axis.firstMove);
	}

	PrintParametersOverSerial(error, PID_speed, P_error,I_error, D_error);
}

int SetSpeedPID(Axis axis, unsigned int setPoint){
	static unsigned int  lastSpeed = 0;
	static unsigned long timeStamp = 0;
	static int P_error = 0;
	static int I_error = 0;
	static int D_error = 0;

	const float kp = 0.7;
	const float ki = 0.65;
	const float kd = 0.3;

	int output = 0;
	int PID_speed = 0;
	int error = 0;
	unsigned int currentSpeed = map(*axis.position, 0, 32000, 0, 1000);
	float elapsedTime = 0.0;

	// set error (normalized = 0 to 1000)
	error = map(setPoint, 0, 60000, 0, 1000) - currentSpeed;

	// Time variables refresh
	elapsedTime = (HAL_GetTick() - timeStamp)/1000.0;
	timeStamp = HAL_GetTick();

	// Refresh PID var errors
	P_error = error;
	I_error = I_error + (error * elapsedTime);
	D_error = (int)((currentSpeed - lastSpeed)) / elapsedTime;

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
	PID_speed = kp * P_error + ki * I_error + kd * D_error;

	// next loop variable refresh
	lastSpeed = currentSpeed;

	// Anti wideup (max +/- 1000)
	if (PID_speed > 1000){
		PID_speed = 1000;
	}
	else if (PID_speed < -1000){
		PID_speed = -1000;
	}
	else {
		;
	}

	return PID_speed;
}

void PrintParametersOverSerial(int err, int pid, int p,int i, int d){
    static char UartTX[200] = {0};
    //const char CLRSCR[] = "\033[0H\033[0J";  // Clear terminal

	//HAL_UART_Transmit(&huart1, (unsigned char *)CLRSCR, strlen((const char *)CLRSCR), 100);

	sprintf((char *)UartTX,
	  	   "\n\rE1P: % 06d\n\r"
	  	   "E2P: % 06d\n\r"
		   "E3P: % 06d\n\r"
		   "E4P: % 06d\n\r"
		   "E1S: % 06d\n\r"
		   "E2S: % 06d\n\r"
		   "E3S: % 06d\n\r"
		   "E4S: % 06d\n\r"
		   " ER: % 06d\n\r"
		   "PID: % 05d\n\r"
		   "  P: % 05d\n\r"
		   "  I: % 05d\n\r"
		   "  D: % 05d\n\r",
			enc_1,
			enc_2,
			enc_3,
			enc_4,
			enc_1_speed,
			enc_2_speed,
			enc_3_speed,
			enc_4_speed,
			err,
			pid,
			p,
			i,
			d
	);

	HAL_UART_Transmit(&huart1, (unsigned char *)UartTX, strlen((const char *)UartTX), 500);
	HAL_Delay(100);

}




