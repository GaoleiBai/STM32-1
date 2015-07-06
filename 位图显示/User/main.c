/**
  ******************************************************************************
  * @file    main.c
  * @author  LXFY
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   Һ����ʾBMPͼƬ
  ******************************************************************************
  */
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_ili9341_lcd.h"
#include "bsp_sdfs_app.h"
#include "bsp_bmp.h"

/*
 * Ҫ��ͼƬ��ʾ�ɹ�
 * ����ֿ⿽����sd���ϣ�Ȼ���sd���嵽������Ŀ�����
 */
int main(void)
{
   /* USART1 config */
		//USART1_Config();
		//printf("\r\n USART testing...... \r\n");
	
		LCD_Init();	
		LCD_Clear(0, 0, 240, 320, BACKGROUND);		
		
		/* ��ʼ��sd���ļ�ϵͳ����Ϊ���ֵ��ֿ������sd������ */
		Sd_fs_init();	
	
		/* ����Lcd Gram ɨ�跽��Ϊ: ���Ͻ� -> ���½�*/
		//Lcd_GramScan( 1 );
		LCD_DispStr(5, 5, (uint8_t *)"fatfs init success", RED);
		LCD_DispStr(5, 25, (uint8_t *)"ensure sdcard has been inserted", RED);
	
	  LCD_DispStrCH(50, 50, (uint8_t *)"λͼ��ʾ", RED);
		/* ��ʾBMPͼƬ */
		Lcd_show_bmp(0, 0,"/lxfy.bmp");  
		while(1);
}