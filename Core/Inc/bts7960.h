#ifndef INC_BTS7960_H_
#define INC_BTS7960_H_

#include "main.h"

typedef struct BTS{
	__IO uint32_t *ShieldPWMRegAddres;
	GPIO_TypeDef  *ShieldPortLeft;
	uint16_t      ShieldPinLeft;
	GPIO_TypeDef  *ShieldPortRight;
	uint16_t      ShieldPinRight;
}BTS2960;

typedef enum{
	CLOCKWISE,
	COUNTERCLOCKWISE,
}MotorRotation;


void InitBTS2960(BTS2960 *shieldName, __IO uint32_t *shieldPWM,
				 GPIO_TypeDef *shieldPortLeft, uint16_t shieldPinLeft,
				 GPIO_TypeDef *shieldPortRight, uint16_t shieldPinRight);

void SetOutputBTS2960(BTS2960 shieldName, uint16_t value, MotorRotation rotation);

void StartRampBTS2960(BTS2960 shieldName, uint16_t value, MotorRotation rotation, uint16_t millisecondsStep);

void StopBTS2960(BTS2960 shieldName);

#endif /* INC_BTS7960_H_ */
