/**
  ******************************************************************************
  * @file    main.c
  * @author  LXFY
  * @version V1.0
  * @date    2013-07-08
  * @brief   usb mass storage USB�������洢ʵ�� 
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "bsp_sdio_sdcard.h"
#include "bsp_usart1.h"	
#include "hw_config.h" 
#include "usb_lib.h"
#include "usb_pwr.h"
#include "bsp_led.h"  

void USB_Delay(__IO uint32_t nCount)
{
	for(; nCount != 0; nCount--);
}

int main(void)
{
	 /* USART1 config */
	USART1_Config();
	
  LED_GPIO_Config();
  
	/*��ʼ��SD��*/
	Set_System();
  	printf("\n initializing sd card \n");
	/*����USBʱ��Ϊ48M*/
	Set_USBClock();
 	
	/*����USB�ж�(����SDIO�ж�)*/
	USB_Interrupts_Config();
 
	/*USB��ʼ��*/
 	USB_Init();
    printf("\n initializing USB, please wait.\n");
 	while (bDeviceState != CONFIGURED);	 //�ȴ��������
	   
	printf("\r\n USB storage mounted. Excited!\r\n");
	 
  while (1)
  {
    LED1_TOGGLE;
    USB_Delay(0x0FFFFF);
  }
}

/* -------------------------------------end of file -------------------------------------------- */
