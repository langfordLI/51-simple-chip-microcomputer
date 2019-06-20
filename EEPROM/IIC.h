#ifndef _IIC_H
#define _IIC_H

#include"reg51.h"
typedef unsigned char u8;
typedef unsigned int u16;

sbit SCL = P2^1;
sbit SDA = P2^0;

void AT24C02Write(u8 addr, u8 dat);
u8 AT24C02Read(u8 addr);

#endif