#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#define debounce 30;

volatile unsigned short Lcont0, Lcont1, Pcont0, Pcont1, Blink0, Blink1;
char Pulsador0, Pulsador1;

void InitPorts(void);
void InitTimer(void);
interrupt VectorNumber_Vporta void PortaIsr(void);
interrupt VectorNumber_Vmtim void MTIMISR(void);

void main(void) {
	InitPorts();
	InitTimer();
	EnableInterrupts
	;
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
	PTBD = 0x00; //PTB EN CERO
	PTBDD = 0xff; //PTB SALIDA
	PTAD_PTAD = 0x00; //PTA EN CERO
	PTADD_PTADD = 0x00; //PTA ENTRADA
	PTAES_PTAES = 0x00; //PTA PULL-UP
	PTAPS_PTAPS0 = 1; //PTA0 REALIZA LA INTERRUPCION
	PTAPS_PTAPS1 = 1; //PTA0 REALIZA LA INTERRUPCION
	PTASC_PTAACK = 1; // BORRO EL FLAG DE INTERRUPCION
	PTASC_PTAIE = 1; //HABILITO INTERRUPCION

}

/* CONFIGURACION DE TIMER*/

void InitTimer(void) {
	MTIMSC_TOF = 0; //Timer overflow (flagg)
	MTIMSC_TSTP = 1; //Timer Stop
	MTIMSC_TRST = 1; //Timer reset
	MTIMCLK = 0X05; //Seleccionamos el bus clk y configuramos el PS
	MTIMMOD = 250; //Registro de comparacion
	MTIMSC_TOIE = 1; //Habilitamos la int. Por timer
	MTIMSC_TSTP = 0; //Activamos el contador
}

/*INTERRUPCION POR PULSADOR */
interrupt VectorNumber_Vporta void PortaIsr(void) {
	PTASC_PTAACK = 1; //Borro el flag de interrupcion
	if (PTAD_PTAD0 == 0) {
		Pulsador0 = 1;
		Pcont0 = 0;
	}
	if (PTAD_PTAD1 == 0) {
		Pulsador1 = 1;
		Pcont1 = 0;
	}
//	MTIMSC_TSTP=0;

}

/*INTERRUPCION POR TIMER */
interrupt VectorNumber_Vmtim void MTIMISR(void) {
	(void) MTIMSC; //Leemos el registro, sino no nos deja escribir
	MTIMSC_TOF = 0; //bajamos el Flagg de Overflow
	if (Pulsador0 == 1) {
		Pcont0 = Pcont0 + 1;
		if ((Pcont0 > 30)&&(PTAD_PTAD0==0)) {
			Blink0 = !Blink0;
			Pulsador0 = 0;
		
		}
	}
	if (Pulsador1 == 1) {
		Pcont1 = Pcont1 + 1;
		if ((Pcont1 > 30)&&(PTAD_PTAD1==0)) {
			Blink1 = !Blink1;
			Pulsador1 = 0;
			
		}
	}
	if (Blink0==1) {
		Lcont0 = Lcont0 + 1;
		if (Lcont0 > 250) {
			PTBD_PTBD4 = !PTBD_PTBD4;
			Lcont0 =0;
		} else {
			PTBD_PTBD4 = 0;
		}
	}

	if (Blink1==1) {
		Lcont1 = Lcont1 + 1;
		if (Lcont1 > 165) {
			PTBD_PTBD5 = !PTBD_PTBD5;
			Lcont1 =0;
		}
	} else {
		PTBD_PTBD5 = 0;
	}
//	if(Pulsador0==0 && Pulsador1==0){MTIMSC_TSTP=1;}
//	if (MTIMSC_TSTP==0){PTBD_PTBD6=1;}

}
