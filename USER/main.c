#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "sbus.h"
#include "timer.h"

u8 test[3] = {1,2,3};

 int main(void)
 {		
	int i=0,j=0;
	
	uint8_t str[500]={0};
	uint16_t channel[12];
	u32 count;
	u16 motorpwmval=899;
	
	uint8_t fireEable = 0 ;
	
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200 
	uart2_init(100000);
	 

 	while(1)
	{
		
		parser(); //串口解析
		count++;
		
		if(count >2000)
		{
			count =0;
			for(i=0;i<12;i++)
			{
				channel[i] = sbus_get(i+1);
			}

			sprintf(str,"%04d %04d %04d %04d %04d %04d %04d %04d %04d %04d %04d %04d \r\n",
			channel[0],channel[1],channel[2],channel[3],channel[4],channel[5],channel[6],channel[7],channel[8],channel[9],channel[10],channel[11]);
		
			Usart1_Send(strlen(str),(uint8_t *)str);
			
		}
	}
}
 
 
 
 
 
 

