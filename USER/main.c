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
	delay_init();	     //延时初始化
//	NVIC_Configuration();
	uart_init(9600);
	I2C_Configuration();  //OLED IIC初始化
  
 	while(DHT11_Init())	//DHT11初始化	
	{
		printf("error");
 		delay_ms(200);
	}
	 OLED_Init();   //OLED初始化
	 OLED_CLS(); //OLED清屏
	printf("ok");
	
	
	while(1)
	{	    	    
 		if(t%10==0)//每100ms读取一次
		{									  
			DHT11_Read_Data(&temperature,&humidity);		//读取温湿度值					     
			 printf("temperature:%d\r\n",temperature);
			 printf("humidity%d\r\n",humidity);
		}	 			   
	 	delay_ms(10);
		t++;
		x=temperature;
		y=humidity;
		sprintf(string1,"%d  ",x);//调用Sprintf函数把DHT11的温度数据格式化到字符串数组变量string1
		sprintf(string2,"%d  ",y);
		OLED_ShowCN(10,1, 13);   //温
		OLED_ShowCN(30,1, 14);   //度
		OLED_ShowCN(10,4, 15);   //湿
		OLED_ShowCN(30,4, 14);   //度
		
		OLED_ShowStr(60,1,(unsigned char*)string1,2); //OLED显示X Y位置
		OLED_ShowStr(60,4,(unsigned char*)string2,2); //OLED显示X Y位置
		
	}
}
