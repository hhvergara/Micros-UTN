#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
volatile unsigned short int Pcont0 = 0,window=0;
int Pulsador0 = 0, ADTmin = 0,ADmin=0,ADmax=0, ADTmax = 0, input=0;

unsigned char ConvAD(unsigned char canal);
void InitPorts(void);
void InitADC(void);
void InitMTIM(void);
interrupt VectorNumber_Vporta void HTIMisr(void);
interrupt VectorNumber_Vmtim void MTIMISR(void);
void WindowStatus (void);

void main(void) {
	PTBD = 0xff; //PTB EN CERO
	PTBD_PTBD4 = 0xff; //PTB EN CERO

	InitPorts();
	InitADC();
	InitMTIM();
	EnableInterrupts
	;
	/* include your code here */

	for (;;) {
		WindowStatus();
		__RESET_WATCHDOG(); /* feeds the dog */
	} /* loop forever */
	/* please make sure that you never leave main */
}

/*Inicialización de puertos-----------------------------------------------------------------------------------*/
void InitPorts(void) {

	/* inicializacion de puertos */
	PTAD = 0x00; //PTA EN CERO
	PTADD_PTADD = 0x00; //PTA ENTRADA
	PTAES_PTAES = 0x00; //PTA PULL-UP
	PTAPS_PTAPS0 = 1; //PTA0 REALIZA LA INTERRUPCION
//	PTAPS_PTAPS1 = 1; //PTA0 REALIZA LA INTERRUPCION
	PTASC_PTAACK = 1; // BORRO EL FLAG DE INTERRUPCION
	PTASC_PTAIE = 1; //HABILITO INTERRUPCION
	PTBD = 0x00; //PTB EN CERO
	PTBDD = 0xf0; //PTB SALIDA/entrada
	PTBD = 0xff; //PTB EN CERO
	PTBD = 0x00; //PTB EN CERO

	PTCD = 0x00; //PTC en cero
	PTCDD = 0x00; //PTC entrada
}

//Inicialización de conversor AD
void InitADC(void) {
	ADCCFG = 0x60; // configuramos el clock en 1Mhz, FBUS 8Mhz y ADIV en 8%
	APCTL1 = 0xc0; //Habilitamos en 1100 0000 [ADP6 – PTB2][ADP7– PTB3]enable  
	APCTL2 = 0x01; //Habilitamos en 0000 0001[ADP8 – PTC0] enable
}

//Inicializacion de Timer
void InitMTIM(void) {

	MTIMSC_TSTP = 1; //
	MTIMSC_TRST = 1; //
	MTIMCLK = 0X05; //
	MTIMMOD = 250; //
	MTIMSC_TOIE = 1; //
	MTIMSC_TSTP = 0; //
}

/*funciones generales---------------------------------------------------------------------------------------------*/

//Lectura de ADC
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
//Comparador de valores de entrada analogica






/*Rutinas de interrupcion----------------------------------------------------------------------------------------*/

//Interrupcion de pulsador
interrupt VectorNumber_Vporta void HTIMisr(void) {
	PTASC_PTAACK = 1; //Borro el flag de interrupcion
	if (PTAD_PTAD0 == 0) {
		Pulsador0 = 1;
		Pcont0 = 0;

	}

}

//Interrupcion de Timer
interrupt VectorNumber_Vmtim void MTIMISR(void) {
	(void) MTIMSC; //
	MTIMSC_TOF = 0; //
//Antirebote SW1 ******************************************************************************************************
	if (Pulsador0 == 1) {
		Pcont0 = Pcont0 + 1;
		if ((Pcont0 > 30) && (PTAD_PTAD0 == 0)) {

			// rutina de lectura de conversores CH 6 y CH 8
			ADTmin = ConvAD(6);
			ADTmax = ConvAD(8);
			if (ADTmin < ADTmax){
				
				ADmin=ADTmin;
				ADmax=ADTmax;
			}

				Pulsador0 = 0;
			Pcont0 = 0;
		}
		if ((Pcont0 > 30) && (PTAD_PTAD0 == 1)) {
			Pulsador0 = 0;
			Pcont0 = 0;
		}

	}

}

void WindowStatus (void){
	
	window= ConvAD(7);
	if (window>0 && window<ADmin){
		PTBD=0x10;		
		
	}else{
		if (ADmin<window && window<ADmax){
			PTBD=0x20;
			
		}else {
			if(ADmax <window && window<255){
				PTBD=0x40;
				
				
			}else {PTBD=0xff;}
			
		}
		
	}
	
	
	
	
	
	
}


