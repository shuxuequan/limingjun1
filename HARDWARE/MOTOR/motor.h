#ifndef __MOTOR_H
#define __MOTOR_H	 
#include "sys.h"
#define MOTORP PBout(5)// PB8
#define MOTORP PBout(5)// PB9

void MOTOR_Init(void);
void MOTORP_out(void);
void MOTORN_out(void);
void MOTOR_stop(void);
void MOTOR_start(u16 count);
#endif