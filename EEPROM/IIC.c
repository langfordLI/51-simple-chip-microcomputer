#include"IIC.h"


void delay10us()
{
	unsigned char a,b;
	for(b=1;b>0;b--)
		for(a=2;a>0;a--);

}

void IICStart()
{
	SDA = 1;
	delay10us();
	SCL = 1;
	delay10us();
	SDA = 0;
	delay10us();

	SCL = 0;
	delay10us();
}

void IICStop()
{
	SDA = 0;
	delay10us();
	SCL = 1;
	delay10us();
	SDA = 1;
	delay10us();
}

u8 IICSendByte(u8 dat)
{
	u8 i = 0;
	u8 j = 0;
	for(i = 0; i < 8; i++)
	{
		SDA = dat>>7;
		dat = dat<<1;
		delay10us();

		SCL = 1;
		delay10us();
		SCL = 0;
		delay10us();
	}

	SDA = 1;	//freed the bus
	delay10us();
	SCL = 1;
	while(SDA)
	{
		j++;	  //wait for the SDA change, if the SDA still keep 1 for 200(sum must exceed 40us) says that produce a non-answer signal
					//the program step into the if judge to force quit the wait
		if(j > 200)
		{
			SCL = 0;			 //note that release the bus
			delay10us();
			return 0;		
		}
	}	 
	/**if the SDA detect 0 says that produce a answer signal where you can return**/
	SCL = 0;				//not that release the bus
	delay10us();
	return 1;
}

u8 IICReceiveByte()
{
	u8 i = 0;
	u8 dat = 0;
	for(i = 0; i < 8; i++)
	{
		SCL = 1;
		delay10us();//note the high level to collect number		

	    dat = dat<<1;
		dat |= SDA;
		delay10us();

		SCL = 0;
		delay10us();
	}
	return dat;
}

void AT24C02Write(u8 addr, u8 dat)
{
//	u8 i = 0;
	IICStart();
	IICSendByte(0xA0);
//	printf("%d", i);
	IICSendByte(addr);
//	printf("%d", i);
	IICSendByte(dat);
//	printf("%d", i);
	IICStop();
}

u8 AT24C02Read(u8 addr)
{
	u8 num = 0;
	IICStart();
	IICSendByte(0xA0);	//false wirte, when read the number you must write the addr to the AT24C02 first
	IICSendByte(addr);

	/**rewrite the start signal and the addr**/
	IICStart();
	IICSendByte(0xA1);
	num = IICReceiveByte();
	IICStop();
	return num;
}


