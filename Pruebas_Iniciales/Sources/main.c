#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */





void main(void) {
  EnableInterrupts;
  /* include your code here */

  

  for(;;) {
	  
	  
	  PTBD = 0xff; //PTB EN CERO
	  PTBD_PTBD4 = 0xff; //PTB EN CERO
	  PTBD_PTBD5 = 0xff; //PTB EN CERO
	  PTBD_PTBD6 = 0xff; //PTB EN CERO
	  PTBD_PTBD7 = 0xff; //PTB EN CERO
	  PTBD_PTBD4 = 1; //PTB EN CERO
	  PTBD_PTBD5 = 1; //PTB EN CERO
	  PTBD_PTBD6 = 1; //PTB EN CERO
	  PTBD_PTBD7 = 1; //PTB EN CERO  	
	  	
    __RESET_WATCHDOG();	/* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
