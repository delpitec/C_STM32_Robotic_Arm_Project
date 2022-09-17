#include "RobotFunctions.h"

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void FindHomePosition(Axis axis){
	SetOutputBTS2960(axis.shield, axis.minSpeed, axis.firstMove);
	while (HAL_GPIO_ReadPin(axis.HomePort, axis.HomePin)){
		PrintParametersOverSerial();
	}

	StopBTS2960(axis.shield);
    HAL_Delay(1500);

    *axis.position = 0;

    SetOutputBTS2960(axis.shield, axis.minSpeed, !axis.firstMove);
    while (!HAL_GPIO_ReadPin(axis.HomePort, axis.HomePin)){
		PrintParametersOverSerial();
	}

    StopBTS2960(axis.shield);
    HAL_Delay(1000);

}

void MoveToPosition(Axis axis, unsigned int setPoint){

	long int error = *axis.position - setPoint;

	if (error < 0){
		SetOutputBTS2960(axis.shield, axis.minSpeed, !axis.firstMove);
		while (*axis.position < setPoint){
			PrintParametersOverSerial();
		}
		StopBTS2960(axis.shield);
	}
	else if (error > 0){
		SetOutputBTS2960(axis.shield, axis.minSpeed, axis.firstMove);
		while (*axis.position > setPoint){
			PrintParametersOverSerial();
		}
		StopBTS2960(axis.shield);
	}
	else{
		;
	}
}

void PrintTestPID(int var1, int var2, int var3, int var4, int var5){
    static char UartTX[100] = {0};
    const char CLRSCR[] = "\033[0H\033[0J";  // Clear terminal

	//HAL_UART_Transmit(&huart1, (unsigned char *)CLRSCR, strlen((const char *)CLRSCR), 100);

	sprintf((char *)UartTX,
	  	   "EN1: % 06d | "
	  	   "ERR: % 04d | "
		   "PID: % 04d | "
		   "  P: % 04d | "
		   "  I: % 04d | "
		   "TIM: % 04d\n\r",
			count_1,
			var1,
			var2,
			var3,
			var4,
			var5
	);

	HAL_UART_Transmit(&huart1, (unsigned char *)UartTX, strlen((const char *)UartTX), 500);
	HAL_Delay(100);

}


void MoveToPositionPID(Axis axis, unsigned int setPoint){

	// Check if setPoint is normilized
	if (setPoint > 1000){
		return;
	}

	static unsigned long timeStamp = 0;
	static long int lastPosition = 0;
	static float kp = 0.6;
	static float ki = 1.0;
	static float kd = 0.0;
	static float P = 0.0;
	static float I = 0.0;
	static float D = 0.0;
	static int PID = 0.0;

	float error;
	float deltaTime;

	// normalized error (0 to 1000)
	error = setPoint - map(*axis.position, 0, 60000, 0, 1000);


	deltaTime = (HAL_GetTick() - timeStamp)/1000.0;
	timeStamp = HAL_GetTick();

	P = error * kp;
	I = (I + (error * ki)) * deltaTime;
	D = (lastPosition - *axis.position) * kd * deltaTime;

	lastPosition = *axis.position;

	PID = P + I + D;

	// Anti wideup
	if (PID >= 1000){
		PID = I = 1000;
	}
	else if (PID <= 0){
		PID = I = 0;
	}

	PrintTestPID(error, PID, P, I, deltaTime);

	if (PID >= 1000 || PID <= 0){
		while (1);
	}
/*
	if(PID > 0){
		SetOutputBTS2960(axis.shield, PID, !axis.firstMove);
	}
	else
		SetOutputBTS2960(axis.shield, PID, axis.firstMove);
*/


}


void PrintParametersOverSerial(void){
    static char UartTX[100] = {0};
    const char CLRSCR[] = "\033[0H\033[0J";  // Clear terminal

	//HAL_UART_Transmit(&huart1, (unsigned char *)CLRSCR, strlen((const char *)CLRSCR), 100);

	sprintf((char *)UartTX,
	  	   "\n\rS1: % 06d H1: %d\n\r"
	  	   "S2: % 06d H2: %d\n\r"
		   "S3: % 06d H3: %d\n\r"
		   "S4: % 06d H4: %d\n\r",
			count_1, HAL_GPIO_ReadPin(IN_AXIS_1_HOME_GPIO_Port, IN_AXIS_1_HOME_Pin),
			count_2, HAL_GPIO_ReadPin(IN_AXIS_2_HOME_GPIO_Port, IN_AXIS_2_HOME_Pin),
			count_3, HAL_GPIO_ReadPin(IN_AXIS_3_HOME_GPIO_Port, IN_AXIS_3_HOME_Pin),
			count_4, HAL_GPIO_ReadPin(IN_AXIS_4_HOME_GPIO_Port, IN_AXIS_4_HOME_Pin)
	);

	HAL_UART_Transmit(&huart1, (unsigned char *)UartTX, strlen((const char *)UartTX), 500);
	HAL_Delay(100);

}

void PrintParametersOverSerialWithOneRandomVar(int var){
    static char UartTX[100] = {0};
    const char CLRSCR[] = "\033[0H\033[0J";  // Clear terminal

	HAL_UART_Transmit(&huart1, (unsigned char *)CLRSCR, strlen((const char *)CLRSCR), 100);

	sprintf((char *)UartTX,
	  	   "\n\rS1: % 06d H1: %d\n\r"
	  	   "S2: % 06d H2: %d\n\r"
		   "S3: % 06d H3: %d\n\r"
		   "S4: % 06d H4: %d\n\r"
		   "VA: % 06d \n\r",
			count_1, HAL_GPIO_ReadPin(IN_AXIS_1_HOME_GPIO_Port, IN_AXIS_1_HOME_Pin),
			count_2, HAL_GPIO_ReadPin(IN_AXIS_2_HOME_GPIO_Port, IN_AXIS_2_HOME_Pin),
			count_3, HAL_GPIO_ReadPin(IN_AXIS_3_HOME_GPIO_Port, IN_AXIS_3_HOME_Pin),
			count_4, HAL_GPIO_ReadPin(IN_AXIS_4_HOME_GPIO_Port, IN_AXIS_4_HOME_Pin),
			var
	);

	HAL_UART_Transmit(&huart1, (unsigned char *)UartTX, strlen((const char *)UartTX), 500);
	HAL_Delay(100);

}


