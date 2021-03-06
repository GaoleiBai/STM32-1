/**
  ******************************************************************************
  * @file    main.c
  * @author  LXFY
  * @version V1.0 BUILD 150629
  * @brief   按键实验
  ******************************************************************************
  * @attention
  * GitHub  :https://github.com/luoxufeiyan/STM32
  * Blog    :http://www.luoxufeiyan.com
  *
  ******************************************************************************
  */
 
#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_key.h"

/**
  * @brief  主函数
  * @param  �
  * @retval �
  */
int main(void)
{
	//配置LED
	LED_GPIO_Config();
	Key_GPIO_Config();
	LED2(ON);
	LED1(ON);
    while(1)
	{
		if(Key_Scan(GPIOA,GPIO_Pin_0)== KEY_ON)
			//GPIO_WriteBit(GPIOC,GPIO_Pin_3,(BitAction)((1-GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_3))));
			LED1_TOGGLE;
		if(Key_Scan(GPIOC,GPIO_Pin_13)== KEY_ON)
			//GPIO_WriteBit(GPIOC,GPIO_Pin_3,(BitAction)((1-GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_3))));
			LED2_TOGGLE;
	}
}
/*********************************************END OF FILE**********************/