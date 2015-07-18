
/******************************************************
* ��������Touchl_Calibrate
* ����  ��������У������
* ����  : ��
* ���  ��0	---	У���ɹ�
					1	---	У��ʧ��
* ����  ����
* ע��  ����
*********************************************************/ 
int Touch_Calibrate(void)
{
    uint8_t i,k;
    u16 test_x=0, test_y=0;
    u16 gap_x=0, gap_y=0;
    Coordinate * Ptr;   
    
		Lcd_GramScan(2);
    for(i=0; i<4; i++)
    {        
        LCD_Clear(0, 0, 320, 240, BACKGROUND);        
        LCD_DispStr(110, 110, (uint8_t *)"Touch Calibrate......", BLUE);	         
        LCD_DisNum(160, 90, i+1, BLUE);
      
        /* �ʵ�����ʱ���б�Ҫ */        
		Delay_ms(500);   
        DrawCross(DisplaySample[i].x,DisplaySample[i].y);  //��ʾУ���õġ�ʮ����
        do
        {
            Ptr=Read_2046_2();  //��ȡTSC2046���ݵ�����ptr            
        }
        while( Ptr == (void*)0 );     //��ptrΪ��ʱ��ʾû�д��㱻����
        ScreenSample[i].x= Ptr->x; 	  //�Ѷ�ȡ��ԭʼ���ݴ�ŵ�ȫ�ֱ���ScreenSample�ṹ��
        ScreenSample[i].y= Ptr->y;

    }
		/* ��ԭʼ��������� ԭʼ�����������ת��ϵ���� */ 
    Cal_touch_para( &DisplaySample[0],&ScreenSample[0],&touch_para ) ;  	   
    
		/*ȡһ�������Xֵ*/
    test_x = ( (touch_para.An * ScreenSample[3].x) + 
               (touch_para.Bn * ScreenSample[3].y) + 
                touch_para.Cn 
             ) / touch_para.Divider ;			 
    
		/*ȡһ�������Yֵ*/
    test_y = ( (touch_para.Dn * ScreenSample[3].x) + 
               (touch_para.En * ScreenSample[3].y) + 
               touch_para.Fn 
             ) / touch_para.Divider ;
    
    /* ʵ���������������Ĳ� */
    gap_x = (test_x > DisplaySample[3].x)?(test_x - DisplaySample[3].x):(DisplaySample[3].x - test_x);
    gap_x = (test_y > DisplaySample[3].y)?(test_y - DisplaySample[3].y):(DisplaySample[3].y - test_y);
    

    //LCD_Rectangle(0,0,320,240,CAL_BACKGROUND_COLOR);
    LCD_Clear(0, 0, 320, 240, BACKGROUND);
    
    /* ����ͨ���޸�������ֵ�Ĵ�С���������� */
    if((gap_x>10)||(gap_y>10))
    {
      LCD_DispStr(100, 100, (uint8_t *)"Calibrate fail", BLUE);
      LCD_DispStr(100, 120, (uint8_t *)"try again", BLUE);     
     // Delay_ms(2000);
			DelayUS(0x1ffff);
      return 1;
    }    
    
    /* У��ϵ��Ϊȫ�ֱ��� */
//    aa1 = (touch_para.An*1.0)/touch_para.Divider;
//    bb1 = (touch_para.Bn*1.0)/touch_para.Divider;
//    cc1 = (touch_para.Cn*1.0)/touch_para.Divider;
//    
//    aa2 = (touch_para.Dn*1.0)/touch_para.Divider;
//    bb2 = (touch_para.En*1.0)/touch_para.Divider;
//    cc2 = (touch_para.Fn*1.0)/touch_para.Divider; 

    cal_p[0] = (touch_para.An*1.0)/touch_para.Divider;  // aa1
    cal_p[1] = (touch_para.Bn*1.0)/touch_para.Divider;  // bb1
    cal_p[2] = (touch_para.Cn*1.0)/touch_para.Divider;  // cc1
    
    cal_p[3] = (touch_para.Dn*1.0)/touch_para.Divider;  // aa2
    cal_p[4] = (touch_para.En*1.0)/touch_para.Divider;  // bb2
    cal_p[5] = (touch_para.Fn*1.0)/touch_para.Divider;  // cc2     
 
    {
      cal_flag = 0x45;
      SPI_FLASH_SectorErase(0);
      SPI_FLASH_BufferWrite(&cal_flag, 0, 1);     
      SPI_FLASH_BufferWrite((void*)cal_p, 1, sizeof(cal_p));
      for( k=0; k<6; k++ )
        printf("\r\n tx = %LF \r\n",cal_p[k]);
    }
    
    LCD_DispStr(100, 100, (uint8_t *)"Calibrate Succed", BLUE);  
    Delay_ms(1000);
    return 0;    
}

/*
 * �����ʼ��������ȡɫ��
 */
void Palette_Init(void)
{
  /* ������Ϊ��ɫ */
  LCD_Clear(0, 0, 320, 240, WHITE);
  
  /* ������ֱ�� */
  LCD_Clear(39, 0, 1, 30, BLACK);
  LCD_Clear(0, 29, 40, 1, BLACK);
  LCD_DispStr(7, 10, (uint8_t *)"CLR", BLUE);
  
  LCD_Clear(0, 30, 40, 30, GREEN);
  LCD_Clear(0, 60, 40, 30, BLUE);
  LCD_Clear(0, 90, 40, 30, BRED);
  LCD_Clear(0, 120, 40, 30, GRED);
  LCD_Clear(0, 150, 40, 30, GBLUE);
  LCD_Clear(0, 180, 40, 30, BLACK);
  LCD_Clear(0, 210, 40, 30, RED);  
  
 // Delay_ms(500);
	DelayUS(0x1ffff);
}

/******************************************************
* ��������Get_touch_point
* ����  ��ͨ�� K A B C D E F ��ͨ��X Y��ֵת��ΪҺ��������
* ����  : ��
* ���  ������1��ʾ�ɹ� 0ʧ��
* ����  ����
* ע��  �������ȡ�Ĵ�����Ϣ���󣬽�����DISABLE
*********************************************************/    
//long double linear=0 ;
//long double aa1=0,bb1=0,cc1=0,aa2=0,bb2=0,cc2=0;
FunctionalState Get_touch_point(Coordinate * displayPtr,
                                Coordinate * screenPtr,
                                Parameter * para )
{
  FunctionalState retTHRESHOLD =ENABLE ;

  if(screenPtr==0)
  {
    /*�����ȡ�Ĵ�����Ϣ�����򷵻�DISABLE*/
    retTHRESHOLD = DISABLE;			
  }
  else
  {    
    //if( para->Divider != 0 )  /* ÿ�ζ�ҪУ��ʱ */
    if( para->Divider != 1 )    /* У��ϵ��д��FLASHʱ */
    {        
      //displayPtr->x = ( (aa1 * screenPtr->x) + (bb1 * screenPtr->y) + cc1);        
      //displayPtr->y = ((aa2 * screenPtr->x) + (bb2 * screenPtr->y) + cc2 );
      displayPtr->x = ( (cal_p[0] * screenPtr->x) + (cal_p[1] * screenPtr->y) + cal_p[2]);        
      displayPtr->y = ((cal_p[3] * screenPtr->x) + (cal_p[4] * screenPtr->y) + cal_p[5] );
    }
    else
    {
      retTHRESHOLD = DISABLE;
    }
  }
  return(retTHRESHOLD);
} 

/******************************************************
* ��������Palette_draw_point
* ����  ����LCDָ��λ�û�һ�����(�����ĸ�С��)
* ����  : Xpos		--X����λ��
*         Ypos		--Y����λ��
* ���  ����
* ����  ��Palette_draw_point(100,100);
* ע��  ���ú����� "��������Ӧ��ʵ��" ר�ú���
*********************************************************/    
void Palette_draw_point(uint16_t x, uint16_t y)
{
  /* ����Ĭ��Ϊ��ɫ */
  static u16 Pen_color=0; 
  u16 y_pos = y;

  /* �ڻ�����ȡɫ */
  if( x<40 )
  {
    if( y>30 )
    Pen_color = (y_pos<60)?GREEN:\
                (y_pos<90)?BLUE:\
                (y_pos<120)?BRED:\
                (y_pos<150)?GRED:\
                (y_pos<180)?GBLUE:\
                (y_pos<210)?BLACK:\
                (y_pos<240)?RED:BLUE;
    else
    {/* ���� */
      #if 0
      LCD_Clear(40, 0, 280, 240, WHITE);
      #elif 1
      LCD_Clear(40, 0, 280, 240, BLACK);
      #endif
      return;
    }
  }
  else
  {
    LCD_SetPoint(x , y , Pen_color);
    LCD_SetPoint(x+1 , y , Pen_color);
    LCD_SetPoint(x , y+1 , Pen_color);
    LCD_SetPoint(x+1 , y+1 , Pen_color);
  }	
}