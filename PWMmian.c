/*

FILE for timer using PWM FOR TIMER TO CONTROLL LEDS


*/

#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"PWMinterface.h"
#include"PWMpriv.h"

void Timer0_PWM_Init()
{

	/*TCCR0 register */

	/* Chosing fast PWM MODE */

	SET_BIT(TCCR0,6);
	SET_BIT(TCCR0,2);

	/* COM00, COM01 >> SEETING OCR */

	SET_BIT(TCCR0,5);
	SET_BIT(TCCR0,4);

	/* PRESCALER  >> /8 >> 2 : 0 */

	CLR_BIT(TCCR0,2);
	SET_BIT(TCCR0,1);
	CLR_BIT(TCCR0,0);

	//TCNT0 = 256;

}


void TIMER0_PWM_SetDutyCycle(u8 Duty)
{
	OCR0 = Duty;
}

