#include "sbus.h"
#include "string.h"

static int count = 0; //计数
static int rx_flag=0; //接收标志位
static uint8_t rx_buf[258]={0}; //接收缓冲区
static uint8_t rx_len=0; //接收长度

static int sbus_channel[12]={0}; //12个通道的数据

void uart_recv_cb(uint8_t ch)
{
	count = 0;
	
	rx_buf[rx_len] = ch;
	rx_len ++;
}

//数据分析器
void parser(void)
{
	int i,j;
	char bin[300]={0};
	uint8_t temp=0;
	
	if(rx_buf[0] == 0x0F && rx_len==25)//首字节是 0x0F  长度达到25
	{
		for(j=0;j<22;j++)
		{
			temp = rx_buf[j+1]; //从 1 到23 都输出 1次 
			
			for(i=0;i<8;i++) // bin[]
			{
				bin[i+j*8] = ((temp>>i)&0x01) ? '1' : '0';
			}
		}
		
		memset(sbus_channel,0,12); //申请一块区域 并清空
		
		for(j=0;j<12;j++)
		{
			for(i=0;i<11;i++)
			{
				if(bin[j*11+i]=='1')
				{
					sbus_channel[j] |= (1<<i);
				}
				else
				{
					sbus_channel[j] &= ~(1<<i);
				}
			}
		}
	}
	
	rx_len = 0;
}

void timer_cb(void)
{
	count++;
	
	if(count==2)
	{
		rx_flag = 1;
		parser(); 	 //分析器
	}
}

/*
	ch_num:channel number 1-12
*/
int sbus_get(int ch_num)
{
	if(ch_num > 0 && ch_num<=12)
	{
		return sbus_channel[ch_num-1];
	}
	
	return 0;
}

