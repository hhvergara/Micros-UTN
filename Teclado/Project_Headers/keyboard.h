/*
 * keyboard.h
 *
 *  Created on: Apr 5, 2014
 *      Author: Marcelo
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_
#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

/*
 * Definición de un valor para representar que no hay ninguna tecla
 */
#define NO_TECLA	0xFF

/*
 * Definiciones de pines, para la placa del SH8
 * Para otra configuración / micro, se puede cambiar acá
 */
/* Entradas KBI c/pullup */
#define FILA0	PTAD_PTAD0
#define FILA1	PTAD_PTAD1
#define FILA2	PTAD_PTAD2
#define FILA3	PTAD_PTAD3
/* Salidas en 0 */
#define COL0	PTCD_PTCD0
#define COL1	PTBD_PTBD3
#define COL2	PTBD_PTBD2

/*
 * Variable donde se guarda la tecla o "NO_TECLA"
 * cada vez que se lee el teclado
 */
extern unsigned char key_press;

/*
 * Funciones que se usan desde la aplicación
 */
void PushKEY(void);
void GetKEY(void);
void TicKEY(void);

#endif /* KEYBOARD_H_ */
