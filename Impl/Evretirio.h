/************************************************************************
Programma pelaths	: Evretirio.h
Syggrafeas			: Karvelas Apostolos 1115201800312
Skopos				: antikeimeniko arxeio gia to Evretirio.c
*************************************************************************/
#ifndef __Evr__
#define __Evr__

#include <stdlib.h>
#include <stdio.h>
#include "TSEvr.h"
#include "TSDDA.h"

typedef struct EvrNode *EvrPtr;

EvrPtr EvrConstruct(int MaxSize);	/* gia erwthma 1 */
int EvrDestruct(EvrPtr *E);		/* gia erwthma 5 */

int EvrInsert(EvrPtr E, TStoixeiouEvr Data); /* gia erwthma 2 */
int EvrSearch(EvrPtr E, keyType key, int InOut, int * found); /* gia erwthma 3 */
int EvrPrintAll(EvrPtr E, FILE *out, int *counter); /* gia Erwthma 4 */
int initialize(TStoixeiouEvr **Data,int *simple);

#endif
