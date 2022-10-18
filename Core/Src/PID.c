#include "PID.h"

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void PrintParametersOverSerial(int err, int pid, int p,int i, int d){
    static char UartTX[200] = {0};
    //const char CLRSCR[] = "\033[0H\033[0J";  // Clear terminal

	//HAL_UART_Transmit(&huart1, (unsigned char *)CLRSCR, strlen((const char *)CLRSCR), 100);

	sprintf((char *)UartTX,
	  	   "\n\rE1P:% 06d "
	  	   "E2P:% 06d "
		   "E3P:% 06d "
		   "E4P:% 06d "
		   /*"E1S: % 06d\n\r"
		   "E2S: % 06d\n\r"
		   "E3S: % 06d\n\r"
		   "E4S: % 06d\n\r"
		   */"ER:% 06d\n\r "
		   "PID: % 05d "
		   "  P: % 05d "
		   "  I: % 05d "
		   "  D: % 05d \n\r",
			enc_1,
			enc_2,
			enc_3,
			enc_4,
			/*enc_1_speed,
			enc_2_speed,
			enc_3_speed,
			enc_4_speed,
			*/err,
			pid,
			p,
			i,
			d
	);

	HAL_UART_Transmit(&huart1, (unsigned char *)UartTX, strlen((const char *)UartTX), 500);
	HAL_Delay(100);

}

int PIDController(PID *pid, unsigned int position, unsigned int setPoint){

	static unsigned int  lastPosition = 0;
	static unsigned long timeStamp = 0;

	int PID = 0;
	int error = 0;
	unsigned int currentPosition = map(position, pid->minProcessVariableValue, pid->maxProcessVariableValue, pid->minNormilizedValue, pid->maxNormilizedValue);
	float elapsedTime = 0.0;

	// set error (normalized = 0 to 1000)
	error = map(setPoint, pid->minSetPointValue, pid->maxSetPointValue, pid->minNormilizedValue, pid->maxNormilizedValue) - currentPosition;

	// Time variables refresh
	elapsedTime = (HAL_GetTick() - timeStamp)/1000.0;
	timeStamp = HAL_GetTick();

	// Refresh PID var errors
	pid->P_error = error;
	pid->I_error = (pid->I_error + (error * elapsedTime));
	pid->D_error = (int)((currentPosition - lastPosition)) / elapsedTime;

	// Anti wideup (max +/- 1000)
	if (pid->I_error > 1000){
		pid->I_error = 1000;
	}
	else if (pid->I_error < -1000){
		pid->I_error = -1000;
	}
	else{
		;
	}

	// Refresh PID controller
	PID = pid->kp * pid->P_error + pid->ki * pid->I_error + pid->kd * pid->D_error;

	// next loop variable refresh
	lastPosition = currentPosition;

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

	PrintParametersOverSerial(error, PID, pid->P_error ,pid->I_error, pid->D_error);

	return PID;
}
