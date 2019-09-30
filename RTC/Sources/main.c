#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

volatile unsigned short blink;
volatile unsigned short contador;
char debounce = 0;

void InitPorts(void);
void InitRTC(void);
interrupt VectorNumber_Vporta void PortaIsr(void);
interrupt VectorNumber_Vrtc void RTC_ISR(void);

void main(void) {
	InitPorts();
	InitRTC();
	EnableInterrupts;
	/* include your code here */

	for (;;) {

		__RESET_WATCHDOG(); /* feeds the dog */
	} /* loop forever */
	/* please make sure that you never leave main */
}
/* INICIALIZACION DE PUERTOS */

void InitPorts(void) {
	/* */

	/* inicializacion de puertos */
	PTBD = 0; //PTB EN CERO
	PTBDD = 0xff; //PTB SALIDA
	PTAD_PTAD = 0x00; //PTA EN CERO
	PTADD_PTADD = 0x00; //PTA ENTRADA
	PTAES_PTAES = 0; //PTA PULL-UP
	PTAPS_PTAPS1 = 1; //PTA1 REALIZA LA INTERRUPCION
	PTASC_PTAACK = 1; // BORRO EL FLAG DE INTERRUPCION
	PTASC_PTAIE = 1; //HABILITO INTERRUPCION

}

/* CONFIGURACION DE RTC*/

void InitRTC(void) {
	RTCSC_RTIE = 0;
	RTCSC=0x9f;
	RTCMOD = 0x00;
	RTCSC_RTIF=1;
	RTCSC_RTIE = 1;
	contador = 0;
}

/*INTERRUPCION POR PULSADOR */
interrupt VectorNumber_Vporta void PortaIsr(void) {
	PTASC_PTAACK = 1; //Borro el flag de interrupcion
	debounce = 1; //Activo la rutina antirebote
	contador = 0; //Borro el buffer de contador

}

/*INTERRUPCION POR RTC */
interrupt VectorNumber_Vrtc void RTC_ISR(void) {
RTCSC_RTIF=1;
PTBD_PTBD4=!PTBD_PTBD4;

//contador=contador +1;
//if(contador>20){
//PTBD_PTBD4=!PTBD_PTBD4;
//contador=0;
//}

}
