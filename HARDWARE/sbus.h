#ifndef __SBUS_H__
#define __SBUS_H__

#include "stdint.h"

void uart_recv_cb(uint8_t ch); //���ڽ����ж� ���ݴ洢
void timer_cb(void); //��ʱ���ж� ����sbus���յ������� 
int sbus_get(int ch_num); //�ӽ�����buf�����ȡ ��Ӧͨ��������

void parser(void); //���ڽ���


#endif /*__SBUS_H__*/


