/**
  ******************************************************************************
  * @file    main.c
  * @author  LXFY
  * @version V1.0
  * @date    20150701
  * @brief   ͨ���������ƴ��������ʫ<�����ϳ������>
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
  
//д������ж�ʵ��
int main(void)
{
	//int flag=0;
    USART1_Config();
	NVIC_Configuration();
    while(1){
        if((Key_Scan(GPIOA,GPIO_Pin_0)== KEY_ON)&&flag==0){
        printf("\r\n ˮ�������緽��, \r\n");
        //flag++;
        } 
        if((Key_Scan(GPIOA,GPIO_Pin_0)== KEY_ON)&&flag==1){
        printf("\r\n ɽɫ�՝�������. \r\n");
        //flag++;
        }
        if((Key_Scan(GPIOA,GPIO_Pin_0)== KEY_ON)&&flag==2){
        printf("\r\n ��������������, \r\n");
        //flag++;
        }
        if((Key_Scan(GPIOA,GPIO_Pin_0)== KEY_ON)&&flag==3){
        printf("\r\n ��ױŨĨ������. \r\n");
        //flag=0;
        }
        
    }
	for(;;)
	{
		
	}
}
/*********************************************END OF FILE**********************/























