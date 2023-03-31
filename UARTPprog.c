

/*

AUTHOR: Ahmed salem mohamed

Date : 16/11/2022

Description : Uart driver for ATMEGA32 base on C

*/


#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"UARTPRIV.h"



void UART_init()
{
	 UCSRC = 0x86;
	  // Enable RX and TX
	  UCSRB = 0x18;

	UBRRL = 0x33;
   // UBRRH = 0;

}


void UARTSENDDATA(u8 data)
{
	//while(GET_BIT(UCSRA,5) == 0)
	while((UCSRA&0x20) == 0x00);

	UDR = data;
}


u8 UARTRECIEVEDATA()
{

	 while((UCSRA&0x80) == 0x00);
  //while(GET_BIT(UCSRA,7) == 0)

	return UDR;
}


void UART_Send_String(u8 *ptr)
{
	for(u8 i=0; ptr[i]!='\0' ; i++)
	{
		UARTSENDDATA(ptr[i]);
	}
}

