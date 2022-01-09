/************************************************************************
Programma pelaths	: TSEvr.h
Syggrafeas			: Karvelas Apostolos 1115201800312
Skopos				: antikeimeniko arxeio gia to TSEvr.c
*************************************************************************/
#ifndef __TSEvr__
#define __TSEvr__

#include <stdio.h>


typedef struct data {
        /*  members for airport data in array */
        int anax;
        int afi;
        char *id;
        char *name;
        char *city;
        char *country;
        char *iata;
        char *icao;
} TStoixeiouEvr;

int TSEvr_setValue (TStoixeiouEvr *target, TStoixeiouEvr source);

int TSEvr_readValue (FILE *from,  TStoixeiouEvr *Elem);
int TSEvr_readValueRoutes (FILE *from,  TStoixeiouEvr *Elem);

int TSEvr_writeValue(FILE *to, TStoixeiouEvr Elem);

#endif
