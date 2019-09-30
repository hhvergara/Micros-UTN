/*
 * keyboard.c
 *
 *  Created on: Apr 5, 2014
 *      Author: Marcelo
 */

#include "keyboard.h"

/*
 * Definiciones de uso interno
 */
#define NO_KEYB_FILA			0xFF
#define NO_KEYB_COL				0xFF
#define KEYB_DLY_DEBOUNCE		30
#define KEYB_DLY_RELEASE		100

/*
 * Estados de la máquina de teclado
 */
enum{
	KB_IDLE,
	KB_DETECTA,
	KB_RELEASE,
};

/*
 * Definición del valor de las teclas
 * Planteado como una matriz ASCII
 */
const unsigned char keyb_map[4][3]={
 {'1','2','3'},
 {'4','5','6'},
 {'7','8','9'},
 {'*','0','#'}
};

/*
 * Variable donde se guarda el valor de la tecla presionada
 */
unsigned char key_press=NO_TECLA;

/*
 * Variables de uso interno
 */
static volatile unsigned char keyb_delay,keyb_press;
static unsigned char keyb_fila=NO_KEYB_FILA, keyb_col=NO_KEYB_COL;

/*
 * Máquina de estado de teclado
 * Si se detecta una interrupción de taclado inicia lectura
 * Si hay una tecla, devuelve ese valor
 * Si no hay una tecla, devuelve NO_TECLA
 */
void GetKEY(void){
	static unsigned char keyb_status = KB_IDLE;

	if(keyb_status==KB_IDLE){
		if(keyb_press){
			keyb_press = FALSE;
			keyb_fila = NO_KEYB_FILA;
			keyb_col = NO_KEYB_COL;
			key_press = NO_TECLA;
			keyb_delay = KEYB_DLY_DEBOUNCE;
			keyb_status = KB_DETECTA;
		}
	}else if(keyb_status==KB_DETECTA){
		if(!keyb_delay){
			if(!FILA0) keyb_fila = 0;
			else if(!FILA1) keyb_fila = 1;
			else if(!FILA2) keyb_fila = 2;
			else if(!FILA3) keyb_fila = 3;

			if(keyb_fila == NO_KEYB_FILA){
				keyb_status = KB_IDLE;
			}else{
				COL0 = 1;
				if(FILA0 & FILA1 & FILA2 & FILA3){
					keyb_col = 0;
				}else{
					COL1 = 1;
					if(FILA0 & FILA1 & FILA2 & FILA3){
						keyb_col = 1;
					}else{
						COL2 = 1;
						if(FILA0 & FILA1 & FILA2 & FILA3){
							keyb_col = 2;
						}
					}
				}

				COL0 = 0;
				COL1 = 0;
				COL2 = 0;

				if(keyb_col == NO_KEYB_COL){
					keyb_status = KB_IDLE;
				}else{
					keyb_delay = KEYB_DLY_RELEASE;
					key_press = keyb_map[keyb_fila][keyb_col];
					keyb_status = KB_RELEASE;
				}
			}
		}
	}else if(keyb_status==KB_RELEASE){
		if(!keyb_delay){
			if(FILA0 & FILA1 & FILA2 & FILA3){
				keyb_status = KB_IDLE;
			}
		}
	}else{
		keyb_press = FALSE;
		keyb_fila = NO_KEYB_FILA;
		keyb_col = NO_KEYB_COL;
		key_press = NO_TECLA;
		keyb_status = KB_IDLE;
	}
}

/*
 * Función que avisa se presionó una tecla
 * Llamar desde interrupción de teclado
 */
void PushKEY(void){
	keyb_press = TRUE;
}

/*
 * Función temporizadora de teclado
 * Llamar cada 1mS
 */
void TicKEY(void){
	if(keyb_delay) keyb_delay--;
}
