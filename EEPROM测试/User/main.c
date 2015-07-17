/**
  ******************************************************************************
  * @file    main.c
  * @author  fire & LXFY
  * @version V1.0
  * @date    2015-07-16
  * @brief   I2C EEPROM(AT24C02)���ԣ�������Ϣͨ��USART1��ӡ�ڵ��Եĳ����ն�
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsP_i2c_ee.h"
#include "bsP_led.h"
#include <string.h>

#define  EEP_Firstpage      0x00
u8 I2c_Buf_Write[256];
u8 I2c_Buf_Read[256];
void I2C_Test(void);

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
    /* ����1��ʼ�� */
	USART1_Config();
	
	printf("initialized USART. \r\n");
	//LED_GPIO_Config();

	/* I2C �����(AT24C02)ʼ�� */
	I2C_EE_Init();

	printf("initialized I2C. \r\n");
    
	I2C_Test();
  
  while (1)
  {      
  }
}

/**
  * @brief  I2C(AT24C02)��д����
  * @param  ��
  * @retval ��
  */
void I2C_Test(void)
{
	u16 i;

	printf("Data to write:\n\r");
    
	for ( i=0; i<=255; i++ ) //��仺��
  {   
    I2c_Buf_Write[i] = i;

    printf("0x%02X ", I2c_Buf_Write[i]);
    if(i%16 == 15)    
        printf("\n\r");    
   }

  //��I2c_Buf_Write��˳�����������д��EEPROM�� 
   //LED1(ON);
   printf("Now writing to Buffer EEPROM...");
	I2C_EE_BufferWrite( I2c_Buf_Write, EEP_Firstpage, 256);
	//LED1(OFF);
  
  printf("Done.\n\r");
   printf("Check data wo will read next.\n\n");
  //��EEPROM��������˳�򱣳ֵ�I2c_Buf_Read��
    //LED2(ON);
    printf("Now reading from Buffer EEPROM...");
	I2C_EE_BufferRead(I2c_Buf_Read, EEP_Firstpage, 256);
    printf("Done\n");
   //LED2(OFF);
   
  //��I2c_Buf_Read�е�����ͨ�����ڴ�ӡ
   printf("Data from EEPROM are:\n");
   for (i=0; i<256; i++)
	{	
		if(I2c_Buf_Read[i] != I2c_Buf_Write[i])
		{
			printf("0x%02X ", I2c_Buf_Read[i]);
			printf("ERROR!! different detected!\n\r");
			return;
		}
    printf("0x%02X ", I2c_Buf_Read[i]);
    if(i%16 == 15)    
        printf("\n\r");
    
	}
  printf("Complete, no any difference between tuo array.\n\r");
}
/*********************************************END OF FILE**********************/
