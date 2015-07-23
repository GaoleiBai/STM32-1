/**
  ******************************************************************************
  * @file    main.c
  * @author  fire & LXFY
  * @version V1.0
  * @date    2015-07-14
  * @brief   Һ������
  ******************************************************************************
  */ 
 
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_ili9341_lcd.h"
#include "bsp_SysTick.h"
#include "bsp_touch.h"
#include "bsp_sdfs_app.h"
#include "bsp_spi_flash.h"
#include "bsp_usart1.h"
#include "bsp_led.h"
#include "bsp_key.h"

#define CLI() __set_PRIMASK(1)
#define SEI() __set_PRIMASK(0)

extern volatile unsigned char touch_flag;

/**
  * @brief  ������
  * @param  ȡ���˴���������  
  * @retval ��
  */
int main(void)
{	
  //char name=0;
  uint8_t k;
	
  /* ϵͳ��ʱ�� 1us ��ʱ��ʼ�� */
  SysTick_Init();
  LCD_Init();	
  /* GRAMɨ�跽��Ϊ���½�->���Ͻ� */
  Lcd_GramScan(2);
  LCD_Clear(0, 0, 320, 240, BACKGROUND);
  /*------------------------------------------------------------------------------------------------------*/
  		/* ��ʼ��sd��*/
		Sd_fs_init();	
		/* ��ʼ������ */
        //USART1_Config();
        /* ������IO���жϳ�ʼ�� */
        Touch_Init();
        /* ��ʼ���ⲿFLASH */
        SPI_FLASH_Init();
/*==========================================��ʼ�����=================================================*/
//��ʼУ��

		while(Touch_Calibrate() !=0);
		//#endif
        
  /* ����ȡɫ���ʼ�� */
  Palette_Init();
  
	while( 1 )
  {
    if(touch_flag == 1)			/*������ʰ�����*/
    {
      /*��ȡ�������*/
      if(Get_touch_point(&display, Read_2046_2(), &touch_para ) !=DISABLE)      
      {	
        Palette_draw_point(display.x,display.y);	
      }
    }
  }
}

/* ------------------------------------------end of file---------------------------------------- */

