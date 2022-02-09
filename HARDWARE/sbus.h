#ifndef __SBUS_H__
#define __SBUS_H__

#include "stdint.h"

void uart_recv_cb(uint8_t ch); //串口接收中断 数据存储
void timer_cb(void); //定时器中断 解析sbus接收到的数据 
int sbus_get(int ch_num); //从解析的buf里面读取 对应通道的数据

void parser(void); //串口解析


#endif /*__SBUS_H__*/


