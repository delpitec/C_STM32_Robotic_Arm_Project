#include "bts7960.h"

void InitBTS2960(BTS2960 *shieldName, __IO uint32_t *shieldPWMRegAddress,
				 GPIO_TypeDef *shieldPortLeft, uint16_t shieldPinLeft,
				 GPIO_TypeDef *shieldPortRight, uint16_t shieldPinRight){
	BTS2960 zero = {0};
	*shieldName = zero;

	shieldName->ShieldPWMRegAddres = shieldPWMRegAddress;
	shieldName->ShieldPortLeft = shieldPortLeft;
	shieldName->ShieldPinLeft = shieldPinLeft;
	shieldName->ShieldPortRight = shieldPortRight;
	shieldName->ShieldPinRight = shieldPinRight;
}

void SetOutputBTS2960(BTS2960 shieldName, uint16_t value, MotorRotation rotation){
		if(rotation == CLOCKWISE){
			HAL_GPIO_WritePin(shieldName.ShieldPortLeft, shieldName.ShieldPinLeft, 0);
			HAL_GPIO_WritePin(shieldName.ShieldPortRight, shieldName.ShieldPinRight, 1);
		}
		else if(rotation == COUNTERCLOCKWISE){
			HAL_GPIO_WritePin(shieldName.ShieldPortLeft, shieldName.ShieldPinLeft, 1);
			HAL_GPIO_WritePin(shieldName.ShieldPortRight, shieldName.ShieldPinRight, 0);
		}
		else{
			return;
		}
	*shieldName.ShieldPWMRegAddres = value;
}

void StartRampBTS2960(BTS2960 shieldName, uint16_t value, MotorRotation rotation, uint16_t millisecondsStep){

	if (*shieldName.ShieldPWMRegAddres == 0){
		if(rotation == CLOCKWISE){
			HAL_GPIO_WritePin(shieldName.ShieldPortLeft, shieldName.ShieldPinLeft, 0);
			HAL_GPIO_WritePin(shieldName.ShieldPortRight, shieldName.ShieldPinRight, 1);
		}
		else if(rotation == COUNTERCLOCKWISE){
			HAL_GPIO_WritePin(shieldName.ShieldPortLeft, shieldName.ShieldPinLeft, 1);
			HAL_GPIO_WritePin(shieldName.ShieldPortRight, shieldName.ShieldPinRight, 0);
		}
		else{
			return;
		}
		for (uint16_t i = 0; i < value; i++){
			*shieldName.ShieldPWMRegAddres = i;
			HAL_Delay(millisecondsStep);
		}
	}
}


void StopBTS2960(BTS2960 shieldName){
	*shieldName.ShieldPWMRegAddres = 0;
}
