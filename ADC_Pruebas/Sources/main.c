#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

unsigned char ADvalue;

unsigned char ConvAD(unsigned char canal);
void InitPorts(void);
void InitADC(void);
void InitMTIM(void);

void main(void) {
	InitPorts();
	InitADC();
	InitMTIM;
	EnableInterrupts
	;
	/* include your code here */

	for (;;) {

		ADvalue = ConvAD(6);
		if (ADvalue >= 201) {
			PTBD=0xf0;
		} else {if (ADvalue >= 151) {
			PTBD=0x70;
		} else {if (ADvalue >= 101) {
			PTBD=0x30;
		} else {if (ADvalue >= 51) {
			PTBD=0x10;
		} else {PTBD=0x00;
			;
		}
			;
		}
			;
		}
			;
		}

		__RESET_WATCHDOG(); /* feeds the dog */
	} /* loop forever */
	/* please make sure that you never leave main */
}

/*Funciones de inicialización*/

//Inicialización de puertos
void InitPorts(void) {

	/* inicializacion de puertos */
	PTBD = 0x00; //PTB EN CERO
	PTBDD = 0xf0; //PTB SALIDA/entrada
	PTAD_PTAD = 0x00; //PTA EN CERO
	PTADD_PTADD = 0x00; //PTA ENTRADA
	PTAES_PTAES = 0x00; //PTA PULL-UP
	PTAPS_PTAPS0 = 1; //PTA0 REALIZA LA INTERRUPCION
	PTAPS_PTAPS1 = 1; //PTA0 REALIZA LA INTERRUPCION
	PTASC_PTAACK = 1; // BORRO EL FLAG DE INTERRUPCION
	PTASC_PTAIE = 1; //HABILITO INTERRUPCION

}

//Inicialización de conversor AD
void InitADC(void) {
	ADCCFG = 0x60; // configuramos el clock en 1Mhz, FBUS 8Mhz y ADIV en 8%
	APCTL1 = 0xc0; //Habilitamos en 1100 0000 [ADP6 – PTB2][ADP7– PTB3]enable  
	APCTL2 = 0x01; //Habilitamos en 0000 0001[ADP8 – PTC0] enable
}



/*funciones generales---------------------------------------------------------------------------------------------*/

//Función get del conversor
unsigned char ConvAD(unsigned char canal) {
	ADCSC1 = 0x20 | canal; //COnfiguramos el multiplexor para trabajar con el canal ingesado y aplicamos una mascara para activar las conversiones continuas e interrupción
	while (ADCSC1_COCO == 0)
		//Esperamos a que se realice la primera conversiòn y la descartamos porque puede tener errores
		;
	(void) ADCRL; //leemos el registro de resultado para bajar el flagg
	while (ADCSC1_COCO == 0)
		//Esperamos a la segunda conversión
		;
	ADCSC1 = 0x1f; //Apagamos el conversor
	return ADCRL; //devolvemos el valor de lectura al programa.

}
















