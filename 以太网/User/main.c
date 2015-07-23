/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   enc28j60+lwip����.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f10x.h"

#include "err.h"
#include "etharp.h"

#include "netconfig.h"
#include "bsp_usart1.h"
#include "bsp_SysTick.h" 
#include "spi.h"
#include "bsp_led.h"

#include "cmd.h"
#include "httpd.h"

/*****************************************************************************************************************************/
    
__IO uint32_t LocalTime = 0; 
/* this variable is used to create a time reference incremented by 10ms */ 
	
int main(void)
{
	/*��ʼ������*/
  USART1_Config();

	/*��ʼ�� ��̫��SPI�ӿ�*/
	ENC_SPI_Init();

	/*��ʼ��systick�����ڶ�ʱ��ѯ������LWIP�ṩ��ʱ*/
	SysTick_Init();		

	/*��ʼ��LEDʹ�õĶ˿�*/
	LED_GPIO_Config();
	 
	printf("\r\n*************STM32_enc8j60+lwip��ֲʵ��*************\r\n");
	  
  	/* ��ʼ��LWIPЭ��ջ*/
	LwIP_Init();
    
    printf("LWIP mounted.IP addr is\n");
    //printf("My IP:&s",ipaddr.addr);
	/*��ʼ��web server ��ʾ��ҳ����*/
	
    httpd_init();
  
  /* ��ʼ��telnet   Զ�̿��� ���� */   
  CMD_init();

  /* Infinite loop */
  while ( 1 )
	{	
		/*��ѯ*/  
		LwIP_Periodic_Handle(LocalTime);		          	  
  }
}