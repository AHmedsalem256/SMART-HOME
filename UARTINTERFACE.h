#ifndef UARTINTERFACE_H
#define UARTINTERFACE_H

void UART_init();

void UARTSENDDATA(u8 data);

void UART_Send_String(u8 *ptr);
u8 UARTRECIEVEDATA();


#endif
