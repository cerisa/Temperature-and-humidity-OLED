#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "ds18b20.h"  
#include "dht11.h"
#include "OLED_ii.h"

  int main(void)
 {
	u8 t=0;			    
	u8 temperature;  	    
	u8 humidity;  
  short x,y;
  char string1 [10];	
	char string2 [10];	 	 

	SystemInit();
	delay_init();	     //��ʱ��ʼ��
//	NVIC_Configuration();
	uart_init(9600);
	I2C_Configuration();  //OLED IIC��ʼ��
  
 	while(DHT11_Init())	//DHT11��ʼ��	
	{
		printf("error");
 		delay_ms(200);
	}
	 OLED_Init();   //OLED��ʼ��
	 OLED_CLS(); //OLED����
	printf("ok");
	
	
	while(1)
	{	    	    
 		if(t%10==0)//ÿ100ms��ȡһ��
		{									  
			DHT11_Read_Data(&temperature,&humidity);		//��ȡ��ʪ��ֵ					     
			 printf("temperature:%d\r\n",temperature);
			 printf("humidity%d\r\n",humidity);
		}	 			   
	 	delay_ms(10);
		t++;
		x=temperature;
		y=humidity;
		sprintf(string1,"%d  ",x);//����Sprintf������DHT11���¶����ݸ�ʽ�����ַ����������string1
		sprintf(string2,"%d  ",y);
		OLED_ShowCN(10,1, 13);   //��
		OLED_ShowCN(30,1, 14);   //��
		OLED_ShowCN(10,4, 15);   //ʪ
		OLED_ShowCN(30,4, 14);   //��
		
		OLED_ShowStr(60,1,(unsigned char*)string1,2); //OLED��ʾX Yλ��
		OLED_ShowStr(60,4,(unsigned char*)string2,2); //OLED��ʾX Yλ��
		
	}
}
