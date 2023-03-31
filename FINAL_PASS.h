

#ifndef FINAL_PASS_H
#define FINAL_PASS_H


void VSTART_APP(); // say ahlan w sahlan

u8 VPASS_CHECK(u8 USER);  // passcode check


u8 VCHECK_NAME(u8* b);

u8 VUsernamecheck();  // username check


void VAPPMENU();  // function to IMAGE THE MENU

u8 VMAIN_MENU();  //function to transmit order from UART

void VALARM_OFF();

void VALARM_ON();

void VSYSTEM_HACKED() ;   // ALARM IF HACKER ENTER

u8 VSIGN_IN() ;    // Function to sign into system

void  VSIGN_OUT();

#endif
