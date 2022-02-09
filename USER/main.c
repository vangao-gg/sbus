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
	
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200 
	uart2_init(100000);
	 

 	while(1)
	{
		
		parser(); //���ڽ���
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
 
 
 
 
 
 

