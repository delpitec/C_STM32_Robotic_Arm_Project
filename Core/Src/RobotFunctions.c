#include "RobotFunctions.h"

void FindHomePosition(Axis axis){

	while(1){
			SetOutputBTS2960(axis.shield, 60, CLOCKWISE);
			HAL_Delay(2000);
			StopBTS2960(axis.shield);
			HAL_Delay(2000);
			SetOutputBTS2960(axis.shield, 60, COUNTERCLOCKWISE);
			HAL_Delay(2000);
			StopBTS2960(axis.shield);
			HAL_Delay(2000);
	}

	SetOutputBTS2960(axis.shield, 60, CLOCKWISE);
	while (HAL_GPIO_ReadPin(IN_AXIS_1_HOME_GPIO_Port, IN_AXIS_1_HOME_Pin)){
		PrintParametersOverSerial();
	}

	StopBTS2960(axis.shield);
    HAL_Delay(1000);

    SetOutputBTS2960(axis.shield, 50, COUNTERCLOCKWISE);
    while (!HAL_GPIO_ReadPin(IN_AXIS_1_HOME_GPIO_Port, IN_AXIS_1_HOME_Pin)){
		PrintParametersOverSerial();
	}

    StopBTS2960(axis.shield);
    HAL_Delay(1000);

    axis.position = 0;
}

void PrintParametersOverSerial(void){
    static char UartTX[100] = {0};
    const char CLRSCR[] = "\033[0H\033[0J";  // Clear terminal

	HAL_UART_Transmit(&huart1, (unsigned char *)CLRSCR, strlen((const char *)CLRSCR), 100);

	sprintf((char *)UartTX,
	  	   "\n\rS1: %05d H1: %d\n\r"
	  	   "S2: % 05d H2: %d\n\r"
		   "S3: % 05d H3: %d\n\r"
		   "S4: % 05d H4: %d\n\r",
			count_1, HAL_GPIO_ReadPin(IN_AXIS_1_HOME_GPIO_Port, IN_AXIS_1_HOME_Pin),
			count_2, HAL_GPIO_ReadPin(IN_AXIS_2_HOME_GPIO_Port, IN_AXIS_2_HOME_Pin),
			count_3, HAL_GPIO_ReadPin(IN_AXIS_3_HOME_GPIO_Port, IN_AXIS_3_HOME_Pin),
			count_4, HAL_GPIO_ReadPin(IN_AXIS_4_HOME_GPIO_Port, IN_AXIS_4_HOME_Pin)
	);

	HAL_UART_Transmit(&huart1, (unsigned char *)UartTX, strlen((const char *)UartTX), 500);
	HAL_Delay(100);

}
