/*
 * main.c
 *
 *  Created on: Jan 23, 2023
 *      Author: Ahmed
 */
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"LCDINTERFACE.h"
#include"UARTINTERFACE.h"
#include"ADC_INTERFACE.h"
#include"PWMinterface.h"
#include"InternalEEprominterface.h"
#include"FINAL_PASS.h"
#include<avr/delay.h>


/*
 * APPLICATION START WITH V
 * */




void main(void)
{
	UART_init();
	LCD_VidIntialize();
	Timer0_PWM_Init();
	ADC_INIT();
	Timer0_PWM_Init();


	u8 x;
	u8 b;
	u8 y;
	u8 q;

	while(1)
	{
		y = VSIGN_IN();

		if(y == 1){

			while(1)
			{
				VALARM_OFF();

				q = VUsernamecheck();

				x = VPASS_CHECK(q);

				if( x == 1)
				{
					VAPPMENU();

					while(x == 1)
					{
						b = VMAIN_MENU();

						if(b == 4)
						{
							break;
						}
					}
				}

				else if (x == 0)
				{
					LCD_VidSendCommand(0x01);

					LCD_VidGOTOPOS(0,0);

					VSYSTEM_HACKED();

					_delay_ms(1000);

					break;
				}
			}
		}


	}


	}


/*
 *
 * USER NAME AND PASS
 *
 * ADMIN WICH HAVE NO USERNAME >> PASS : 0000
 *
 * */


//u8 *c[] = { (u8 *)"Ahmed"1 , (u8 *)"mosad"2, (u8 *)"amr"3,(u8 *)"bahaa"4,(u8 *)"ali"5,(u8 *)"alaa"6,(u8 *)"omar"7,(u8 *)"karim"8 }; // GLOBAL Array for usernames
/*
 *
 *
 *
	u8 cc0[3] = {0,0,0};
	u8 cc1[3] = {1,2,3};
	u8 cc2[3] = {4,4,6};
	u8 cc3[3] = {4,1,6};
	u8 cc4[3] = {6,6,6};
	u8 cc5[3] = {7,7,7};
	u8 cc6[3] = {8,8,8};
	u8 cc7[3] = {9,9,9};
	u8 cc8[3] = {1,1,1};
 *
 *
 *
 */



