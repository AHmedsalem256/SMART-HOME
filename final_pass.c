
/*

 DAte : 23/1/2023 
 
 Author : Ahmed Salem Mohamed 

 @brief : Porgram final project for smart home 


*/


#include"BIT_MATH.h"
#include"STD_TYPES.h"
#include"DIO_interface.h"
#include"LCDINTERFACE.h"
#include"UARTINTERFACE.h"
#include"ADC_INTERFACE.h"
#include"PWMinterface.h"
#include"InternalEEprominterface.h"
#include<util/delay.h>


#define MAXPASSLOOP 3
#define MAXPASS 3
#define MAXUSERLOOP 5
#define MAXUSER 5


/*************************************************************************************************************************************************************/

                                                      /******USERNAMES******/

//u8 *c[] = { (u8 *)"Ahmed" , (u8 *)"mosad", (u8 *)"amr",(u8 *)"bahaa",(u8 *)"bahaa",(u8 *)"alaa",(u8 *)"bahaa",(u8 *)"bahaa" }; // GLOBAL Array for usernames
u8 *c[] = { (u8 *)"Ahmed" , (u8 *)"mosad", (u8 *)"amr",(u8 *)"bahaa",(u8 *)"ali",(u8 *)"alaa",(u8 *)"omar",(u8 *)"karim" };

/*************************************************************************************************************************************************************/

                                                                       /*USER ENTRANCE*/

typedef struct
{
	u8 ID[3];
	u8 username[5];

}user ;


user user1;

/**************************************************************************************************************************************************************/

void VSTART_APP()
{
	LCD_VidSendCommand(0x01);

	LCD_VidGOTOPOS(0,1);
	LCD_VidSendString("WELCOME HOME ");

	_delay_ms(500);

	LCD_VidSendCommand(0x01);

}

/**************************************************************************************************************************************************************/


/*
 * user1 >> ahmed >> 123
 * user2 >> mosad >> 321
 * user3 >> omar  >> 541
 * user4 >> samy  >> 456
 * user5 >> nour  >> 641
 * user6 >> sayed >> 789
 * user6 >> boody >> 471
 * user7 >> shamy >> 410
 * user8 >> wael  >> 411
 * user9 >> karem >>  412
 * user10 >> james >> 007
 * */

//u8 *c[] = { (u8 *)"Ahmed" , (u8 *)"mosad", (u8 *)"amr",(u8 *)"bahaa",(u8 *)"bahaa",(u8 *)"bahaa",(u8 *)"bahaa",(u8 *)"bahaa" }; //array for usernames


/**************************************************************************************************************************************************************/

u8 VPASS_CHECK(u8 USER)
{

	u8 PASS_Default1[3]  ;

	/*
	 *
	 * PASS is STORED IN EEPROM
	 *
	 * */

/******************************************************************************/



	u8 cc0[3] = {0,0,0};
	u8 cc1[3] = {1,2,3};
	u8 cc2[3] = {4,4,6};
	u8 cc3[3] = {4,1,6};
	u8 cc4[3] = {6,6,6};
	u8 cc5[3] = {7,7,7};
	u8 cc6[3] = {8,8,8};
	u8 cc7[3] = {9,9,9};
	u8 cc8[3] = {1,1,1};



/******************************************************************************/


	u8 i;
	u8 counter;


	switch(USER)
	{

	case 1 :

		for(i=0;i<3;i++)
		{
			PASS_Default1[i] = cc1[i];
		}

		break;

	case 2 :
		for(i=0;i<3;i++)
			{
				PASS_Default1[i] = cc2[i];
			}

		break;

	case 3 :
		for(i=0;i<3;i++)
			{
				PASS_Default1[i] = cc3[i];
			}


		break;
	case 4 :
		for(i=0;i<3;i++)
			{
				PASS_Default1[i] = cc4[i];
			}

		break;
	case 5 :

		for(i=0;i<3;i++)
			{
				PASS_Default1[i] = cc5[i];
			}


			break;
	case 6 :

		for(i=0;i<3;i++)
		{
			PASS_Default1[i] = cc6[i];
		}

		break;
	case 7 :

		for(i=0;i<3;i++)
		{
			PASS_Default1[i] = cc7[i];
		}

		break;
	case 8 :

		for(i=0;i<3;i++)
		{
			PASS_Default1[i] = cc8[i];
		}

		break;


	default :

		for(i=0;i<3;i++)
		{
			PASS_Default1[i] = cc0[i] ;
		}

	}

	//static u8 ERRORS = 0 ;

	u8 ERRORS = 0 ;

	LCD_VidSendCommand(0x01);

	LCD_VidGOTOPOS(0,0);


	LCD_VidSendString("PASSWORD: ");

	LCD_VidGOTOPOS(1,0);

	while(1)
	{


		counter = 0;

		for(i=0;i<MAXPASSLOOP;i++)
		{
			user1.ID[i] = UARTRECIEVEDATA() - 48;

			LCD_VidSendNum(user1.ID[i]);
			UARTSENDDATA(user1.ID[i]);
		}

		for(i=0;i<MAXPASSLOOP;i++)
		{
			if( user1.ID[i] == PASS_Default1[i] )
			{
				counter ++;
			}
		}

		if(counter == 3)
		{
			LCD_VidSendCommand(0x01);
			LCD_VidGOTOPOS(0,0);
			LCD_VidSendString("RIGHT PASS");
			return 1;
			break;
		}


		else if(counter != 3)
		{
			/*
			 * SYSTEM UNLOCKED
			 * */
			LCD_VidSendCommand(0x01);
			LCD_VidGOTOPOS(0,0);
			LCD_VidSendString("WRONG PASS");
			LCD_VidGOTOPOS(1,0);
		}

		ERRORS++;

		if(ERRORS == 2 )
		{
			/*
			 * SYSTEM LOCKED
			 *
			 * */
			ERRORS = 0;
			return 0;
			break ;
		}

	}

}


/**************************************************************************************************************************************************************/

//u8 *c[] = { (u8 *)"Ahmed" , (u8 *)"mosad", (u8 *)"amr",(u8 *)"bahaa",(u8 *)"bahaa",(u8 *)"bahaa",(u8 *)"bahaa",(u8 *)"bahaa" }; // GLOBAL Array for usernames



u8 VCHECK_NAME(u8* b)
{
	u8 counter1 = 0;
	u8 counter2 = 0;

	u8 state = 0;


	while( counter1 < 10 )
	{

		while(b[counter2] == c[counter1][counter2] && b[counter2]!= '\0' && c[counter1][counter2] != '\0'  )
		{
			counter2 ++;
		}

		if(b[counter2] == '\0' || c[counter1][counter2] == '\0')
		{
			state = counter1 + 1 ;

			break;
		}

		else if( b[counter2]!= '\0' || c[counter1][counter2] != '\0' )
		{
			counter1 ++;

		}

	}

	return state;

}



u8 VUsernamecheck()
{

	LCD_VidSendCommand(0x01);
	LCD_VidGOTOPOS(0,0);
	LCD_VidSendString("USERNAME:");
	LCD_VidGOTOPOS(1,0);

	u8 username[5];
	u8 i;
	u8 x;


		for(i=0;i<5;i++)
		{
			username[i] = UARTRECIEVEDATA();
			LCD_VidSendData(username[i]);
			UARTSENDDATA(username[i]);
		}


		x = VCHECK_NAME(username);




		if(x != 0)
		{

			LCD_VidSendCommand(0x01);
			LCD_VidGOTOPOS(0,0);

			LCD_VidSendString("MR");


			for(i=0;i<5;i++)
			{
				LCD_VidSendData(username[i]);
				UARTSENDDATA(username[i]);

			}

			return x;
		}




}



/**************************************************************************************************************************************************************/



void VAPPMENU()
{

	   LCD_VidSendCommand(0x01);

		LCD_VidGOTOPOS(0,0);

		LCD_VidSendString("1:ROOM1");

		LCD_VidGOTOPOS(0,8);

		LCD_VidSendString("2:ROOM2");

		LCD_VidGOTOPOS(1,0);

		LCD_VidSendString("3:FAN");

		LCD_VidGOTOPOS(1,8);

		LCD_VidSendString("4:OUT");


		UART_Send_String("ENTER YOUR CHOICE");

}

/**************************************************************************************************************************************************************/


u8 VMAIN_MENU()
{
	u8 choice ;
	u8 temp ;

	switch(choice)
	{
	case 1:

		LCD_VidSendCommand(0x01);
		LCD_VidGOTOPOS(0,0);

		LCD_VidSendString("ROOM1 OPEN");
		LCD_VidGOTOPOS(1,0);

		LCD_VidSendString("ENTER 5 to OFF ");

		OPENROOM1();
		return 0;

		break;

	case 2:

		LCD_VidSendCommand(0x01);
		LCD_VidGOTOPOS(0,0);

		LCD_VidSendString("ROOM2 OPEN");
		LCD_VidGOTOPOS(1,0);

		LCD_VidSendString("ENTER 6 to OFF ");



		OPENROOM2();

		return 0;

	break;

	case 3:

		LCD_VidSendCommand(0x01);

		LCD_VidGOTOPOS(0,0);

		LCD_VidSendString("FAN OPEN");

		LCD_VidGOTOPOS(1,0);

		LCD_VidSendString("ENTER 7 to OFF ");

		OPENFAN();


		return 0;

	break;

	case 4:

		LCD_VidSendCommand(0x01);

		LCD_VidGOTOPOS(1,0);

		LCD_VidSendString("OUT");

		VSIGN_OUT();

		return 4;




	break;


	case 5:

		LCD_VidSendCommand(0x01);
		LCD_VidGOTOPOS(0,0);

		LCD_VidSendString("Room1 CLOSED");

		_delay_ms(500);

		VAPPMENU();

		CLOSEROOM1();

		return 0;


		break;

	case 6:

		LCD_VidSendCommand(0x01);
		LCD_VidGOTOPOS(0,0);

		LCD_VidSendString("ROOM2 CLOSED");

		 CLOSEROOM2();

			_delay_ms(500);

			VAPPMENU();

			return 0;

		break;


	case 7:

		LCD_VidSendCommand(0x01);
		LCD_VidGOTOPOS(0,0);

		LCD_VidSendString("FAN CLOSED");

		CLOSEFAN();

		_delay_ms(500);

		VAPPMENU();

		return 0;
		break;


	default :

		LCD_VidSendString("WRONG NUMBER");
		UART_Send_String("WRONG NUMBER\t");

		LCD_VidSendString("WRONG NUMBER\n");

		VAPPMENU();

		return 0;


	}


}


/**************************************************************************************************************************************************************/

void OPENROOM1()
{
	/*
	PIN B0 >>
	*/

	DIO_VidSetPinDirection(1,0,1);
	DIO_VidSetPinValue(1,0,1);

}


/**************************************************************************************************************************************************************/

void CLOSEROOM1()
{
	DIO_VidSetPinValue(1,0,0);

}

/**************************************************************************************************************************************************************/

void OPENROOM2()
{
	/*
	PIN B1 >>
	*/

	DIO_VidSetPinDirection(1,1,1);
	DIO_VidSetPinValue(1,1,1);

}


/**************************************************************************************************************************************************************/


void CLOSEROOM2()
{
	DIO_VidSetPinValue(1,1,0);
}

/**************************************************************************************************************************************************************/

void OPENFAN()
{
	/*
	 * PIN B2
	 * */

	DIO_VidSetPinDirection(1,2,1);
	DIO_VidSetPinValue(1,2,1);

}


/**************************************************************************************************************************************************************/

void CLOSEFAN()
{

	DIO_VidSetPinValue(1,2,0);

}


/**************************************************************************************************************************************************************/


void VSIGN_OUT()
{
	/*
	 * OFF PIN B0 , B1, B2
	 * */
	DIO_VidSetPinValue(1,2,0);
	DIO_VidSetPinValue(1,1,0);
	DIO_VidSetPinValue(1,0,0);

}

/**************************************************************************************************************************************************************/

void VALARM_ON()
{
	/*
	 * ON PIN B3
	 * */

	DIO_VidSetPinDirection(1,3,1);
	DIO_VidSetPinValue(1,3,1);
}

/**************************************************************************************************************************************************************/

void VALARM_OFF()
{
	DIO_VidSetPinValue(1,3,0);
}


/**************************************************************************************************************************************************************/


void VSYSTEM_HACKED()
{
	VALARM_ON();

	LCD_VidSendCommand(0x01);

	LCD_VidSendString("SYSTEM HACKED");

	LCD_VidGOTOPOS(1,0);

	LCD_VidSendString("ALARM ON");

	_delay_ms(3000);

	VALARM_OFF();
}


/**************************************************************************************************************************************************************/

u8 VSIGN_IN()
{
	LCD_VidSendCommand(0x01);
	LCD_VidGOTOPOS(0,0);

	LCD_VidSendString("ENTER HOME??");

	LCD_VidGOTOPOS(1,0);

	LCD_VidSendString("1:YES 2:NO :");


	u8 h;

	h = UARTRECIEVEDATA() - 48;

	return h;
}



/**************************************************************************************************************************************************************/

