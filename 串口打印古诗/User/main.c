/**
  ******************************************************************************
  * @file    main.c
  * @author  LXFY
  * @version V1.0
  * @date    20150702
  * @brief   ͨ���������ƴ��������ʫ<�����ϳ������>-��ʱ��
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_key.h"
#include "stm32f10x_it.h"

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
  
void Delay(__IO uint32_t nCount)	 
{
	for(; nCount != 0; nCount--);
}
int main(void)
{
	//int flag=0;
    USART1_Config();
	NVIC_Configuration();
    while(1){
        if((Key_Scan(GPIOA,GPIO_Pin_0)== KEY_ON)){
        printf("\r\n ˮ�������緽��, \r\n");
        }
        Delay(0xFFFFF);
        if((Key_Scan(GPIOA,GPIO_Pin_0)== KEY_ON)){
        printf("\r\n ɽɫ�՝�������. \r\n");
        }
        Delay(0xFFFFF);
        if((Key_Scan(GPIOA,GPIO_Pin_0)== KEY_ON)){
        printf("\r\n ��������������, \r\n");
        }
        Delay(0xFFFFF);
        if((Key_Scan(GPIOA,GPIO_Pin_0)== KEY_ON)){
        printf("\r\n ��ױŨĨ������. \r\n");
        Delay(0xFFFFF);
        }
        
    }
}
/*********************************************END OF FILE**********************/























