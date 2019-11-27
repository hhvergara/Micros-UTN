#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "SCI.h"
#include "keyboard.h"

#define Motor_A PTBD_PTBD4 
#define Motor_B PTBD_PTBD5
#define _Motor_A PTBDD_PTBDD4 
#define _Motor_B PTBDD_PTBDD5

const unsigned char codigo[] = "1234";
int PWRD_OK = 0;

#if(1)
//Configuracion final
#define FCC PTBD_PTBD7
#define FCA PTBD_PTBD6
#define	_FCA PTBDD_PTBDD6
#define	_FCC PTBDD_PTBDD7

#else
//Configuracion de prueba
#define FCC PTAD_PTAD0// switch de cerrado
#define FCA PTAD_PTAD1//switch de abierto
#define PASS_KEY PTAD_PTAD2//switch de password ok
#define	_FCA PTADD_PTADD1
#define	_FCC PTADD_PTADD0
#define	_PASS_KEY PTADD_PTADD2

#endif

#define abrir 1
#define cerrar 0
#define time_delay 2000

char abriendo = 0;
char cerrando = 1;
int tout = time_delay; //flagg de timeout
char sucess = 1;

void Init_Ports(void) {
	FCC = 0;
	FCA = 0;
	_FCA = 0;
	_FCC = 0;
	//PASS_KEY = 0;
	//_PASS_KEY = 0;
	Motor_A = 0;
	Motor_B = 0;
	_Motor_A = 1;
	_Motor_B = 1;

	/* inicializacion de puertos */
	PTCDD = 0x01;
	PTBD = 0; //PTB EN CERO
	PTBDD = 0xfc; //PTB SALIDA
	PTAD_PTAD = 0x00; //PTA EN CERO
	PTADD_PTADD = 0x00; //PTA ENTRADA
	PTAES = 0; //PTA PULL-UP
	PTAPS = 0x0f; //PTA 0,1,2 REALIZA LA INTERRUPCION
	PTASC_PTAACK = 1; // BORRO EL FLAG DE INTERRUPCION
	PTASC_PTAIE = 1; //HABILITO INTERRUPCION

}
void InitTimer(void) {

	MTIMSC_TOF = 0; //Timer overflow (flagg)
	MTIMSC_TSTP = 1; //Timer Stop
	MTIMSC_TRST = 1; //Timer reset
	MTIMCLK = 0X05; //Seleccionamos el bus clk y configuramos el PS
	MTIMMOD = 250; //Registro de comparacion
	MTIMSC_TOIE = 1; //Habilitamos la int. Por timer
	MTIMSC_TSTP = 0; //Activamos el contador

}

interrupt VectorNumber_Vporta void PortaIsr(void) {
	PTASC_PTAACK = 1; //Borro el flag de interrupcion
	PushKEY();
}

interrupt VectorNumber_Vmtim void MTIMISR(void) {
	(void) MTIMSC; //Leemos el registro, sino no nos deja escribir
	MTIMSC_TOF = 0; //bajamos el Flagg de Overflow
	tout--;
	TicKEY();

}

void Motor_run(int Open_close) {
	if (Open_close == 1) {
		Motor_A = 0;
		Motor_B = 1;

	}
	if (Open_close == 0) {
		Motor_A = 1;
		Motor_B = 0;

	}

}

void Motor_stop(void) {

	Motor_A = 0;
	Motor_B = 0;

}

void main(void) {
	int i = 0;
	//int FCC = 0, FCA = 1;
	int aux = 1;
	int estado = 0, hecho = 0, exito = 0;
	char input_value[4];

	Init_Ports();
	InitSCI();
	InitTimer();
	EnableInterrupts
	;
	Motor_stop();

	if (FCC == 1 && FCA == 1) { //el porton esta en el medio

		abriendo = 1;
		Motor_run(abrir);
		PutSCI("Abriendo el porton\r\n", 0);

	}
	if (FCA == 0) { //el porton esta abierto
		cerrando = 1;
		Motor_run(cerrar);
		PutSCI("El porton esta abierto, cerrando \r\n", 0);

	}

	if (FCC == 0) { //Si el porton esta cerrado, habilita la recepcion de password
		sucess = 0;
		aux = 0;
		PutSCI("Porton cerrado, ingrese password \r\n", 0);

	}

	for (;;) {

		//Porton Abierto, entra al if cuando el porton esta abierto del todo.
		if (FCA == 0 && FCC == 1 && abriendo == 1) { //consulto si el porton llego al final de apertura

			Motor_stop(); //paro el motor
			//Timmer 5 seg.
			if (MTIMSC_TOIE == 0) {
				PutSCI("Porton Abierto, esperando...\r\n", 0);

			}

			switch (tout) {
			case 3000:
				PutSCI("El porton se cerrara en= 3 seg.\r\n", 0);
				break;
			case 2000:
				PutSCI("El porton se cerrara en= 2 seg.\r\n", 0);
				break;
			case 1000:
				PutSCI("El porton se cerrara en= 1 seg.\r\n", 0);
				break;
			default:
				break;
			}

			MTIMSC_TOIE = 1; //Habilitamos la int. Por timer

			if (tout == 0) {
				PutSCI("Cerrando\r\n", 0);
				Motor_run(cerrar);
				abriendo = 0;
				cerrando = 1;
				tout = time_delay;
				MTIMSC_TOIE = 0; //Habilitamos la int. Por timer
				aux = 1;
			}

		}

//Porton cerrado
		if (FCC == 0 && FCA == 1 && cerrando == 1) {

			if (aux) {
				PutSCI("Porton cerrado, ingrese password \r\n", 0);
				Motor_stop();
			}
			GetKEY();

			if (key_press != NO_TECLA) {
				(void) estado++;

				if (estado == 1) {

					input_value[0] = key_press;
					PutSCI("*", 0);
					key_press = NO_TECLA;
				}
				if (estado == 2) {
					input_value[1] = key_press;
					key_press = NO_TECLA;
					PutSCI("*", 0);
				}
				if (estado == 3) {
					input_value[2] = key_press;
					key_press = NO_TECLA;
					PutSCI("*", 0);

				}
				if (estado == 4) {
					input_value[3] = key_press;
					key_press = NO_TECLA;
					hecho = 1;
					PutSCI("*\r\n", 0);

				}

				if (hecho == 1) {
					hecho = 0;
					estado = 0;
					for (i = 0; i < 4; i++) {

						if (input_value[i] != codigo[i]) {
							PutSCI("Password incorrecto\r\n", 0);
							PutSCI("Reingrese el Password \r\n", 0);

							PWRD_OK = 0;
							exito = 0;
							break;
						} else {
							exito++;
						}

					}

					if (exito == 4) {
						exito = 0;
						cerrando = 0;
						sucess = 0;
						PutSCI("Password correcto\r\n", 0);
						PWRD_OK = 1;
						aux = 0;
					}
				}

			}
		}
//Espera de Password

		if (PWRD_OK == 1 && sucess == 0) {
			PutSCI("Abriendo el porton\r\n", 0);
			abriendo = 1;
			Motor_run(abrir);
			sucess = 1;
			PWRD_OK = 0;

		}

		__RESET_WATCHDOG(); /* feeds the dog */
	} /* loop forever */
	/* please make sure that you never leave main */
}
