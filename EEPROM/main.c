#include"reg51.h"
#include"IIC.h"


u8 num = 230;

sbit LSA = P2^2;
sbit LSB = P2^3;
sbit LSC = P2^4;

sbit k1 = P3^0;
sbit k2 = P3^1;
sbit k3 = P3^2;
sbit k4 = P3^3;

u8 code light[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

u8 disp[4];

	  
void delay(u16 i)
{
	while(i--);
}

void keyPros()
{
	if(k1 == 0)
	{
		delay(1000);
		if(k1 == 0)
		{
			AT24C02Write(1, num);	  //save the number into the EEPROM
		}
		while(!k1);	//note to detect the key release, or the number while increase quickly
	}
	if(k2 == 0)
	{
		delay(1000);
		if(k2 == 0)
		{
			num = AT24C02Read(1);	 //get the number form EEPROM
		}
		while(!k2);	//note to detect the key release, or the number while increase quickly
	}
	if(k3 == 0)		 //add the number
	{
		delay(1000);
		if(k3 == 0)
		{
			num++;
			if(num > 255)
			{
				num = 0;	//every time EEPROM can only save one byte in a address, must limit the data
			}
		}
		while(!k3);	//note to detect the key release, or the number while increase quickly
	}
	if(k4 == 0)	   //clear the number
	{
		delay(1000);
		if(k4 == 0)
		{
			num = 0;
		}
		while(!k4);	//note to detect the key release, or the number while increase quickly
	}
}

void DataShow()
{
	disp[0] = light[num / 1000];
	disp[1] = light[num % 1000 / 100];
	disp[2] = light[num % 100  / 10];
	disp[3] = light[num % 10];

}


void Display()
{
	u8 i = 0;
	for(i = 0; i < 4; i++)
	{
		switch(i)
		{
			case 0: LSA = 0; LSB = 0; LSC = 0; break;
			case 1: LSA = 1; LSB = 0; LSC = 0; break;
			case 2: LSA = 0; LSB = 1; LSC = 0; break;
			case 3: LSA = 1; LSB = 1; LSC = 0; break;
		}
		P0 = disp[i];
		delay(100);
		P0 = 0x00;
	}
}

void main()
{
	  while(1)
	  {
	  	keyPros();
	  	DataShow();
	  	Display();
	  }
}
