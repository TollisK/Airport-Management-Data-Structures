/************************************************************************
Programma pelaths	: TSEvr.c
Syggrafeas			: Karvelas Apostolos 1115201800312
Skopos				: Functions gia ton pinaka toy EvrNode
*************************************************************************/
#include "TSEvr.h"

int TSEvr_setValue (TStoixeiouEvr *target, TStoixeiouEvr source){
	/**target = source;*/
	(*target).anax = source.anax;
	(*target).afi = source.afi;
	(*target).id = source.id;	
	(*target).name = source.name;
	(*target).city = source.city;
	(*target).country = source.country;
	(*target).iata = source.iata;
	(*target).icao = source.icao;
}

int TSEvr_readValue (FILE *from,  TStoixeiouEvr *Elem){ /*diabazei apo to txt input xaraktires kai toys arxikopoiei sto Elem*/
	int nch=0,c,i=0;
	while(c = getc(from))
	{
		if(c == ';')
			break;
		if(c == EOF){
			return 1;
		}
		Elem->id[nch] = c;
		nch = nch + 1;
		Elem->id[nch] = '\0';
	}
	nch = 0;
	while(c = getc(from))
	{
		if(c == ';')
			break;
		Elem->name[nch] = c;
		nch = nch + 1;
		Elem->name[nch] = '\0';
	}
	nch = 0;
	while(c = getc(from))
	{
		if(c == ';')
			break;
		Elem->city[nch] = c;
		nch = nch + 1;
		Elem->city[nch] = '\0';
	}
	nch = 0;
	while(c = getc(from))
	{
		if(c == ';')
			break;
		Elem->country[nch] = c;
		nch = nch + 1;
		Elem->country[nch] = '\0';
	}
	nch = 0;
	while(c = getc(from))
	{
		if(c == ';')
			break;
		Elem->iata[nch] = c;
		nch = nch + 1;
		Elem->iata[nch] = '\0';
	}
		nch = 0;
	while(c = getc(from))
	{
		if(c == '\n')
			break;
		if(c == EOF){
			return 1;
		}
		Elem->icao[nch] = c;
		nch = nch + 1;
		Elem->icao[nch] = '\0';
	}
	return 0;

/*atoi apo string se int izi char s[100]="22"  ===== int i = atoi(s) = 22*/
}

int TSEvr_readValueRoutes (FILE *from,  TStoixeiouEvr *Elem){ /*Opws h TSEvr_readValue alla gia ton input routes.txt*/
	int nch=0,c;
	while(c = getc(from))
	{
		if(c == ';')
			break;
	}
	while(c = getc(from))
	{
		if(c == ';')
			break;
	}
	while(c = getc(from))
	{
		if(c == ';')
			break;
	}
	nch = 0;
	while(c = getc(from))
	{
		if(c == ';')
			break;
		Elem->id[nch] = c;
		nch = nch + 1;
		Elem->id[nch] = '\0';
	}
	while(c = getc(from))
	{
		if(c == ';')
			break;
	}
	nch = 0;
	while(c = getc(from))
	{
		if(c == ';'){
			break;
		}
		Elem->name[nch] = c;
		nch = nch + 1;
		Elem->name[nch] = '\0';
	}
	while(c = getc(from))
	{
		if(c == '\n')
			break;
		if(c == EOF){
			return 1;
		}	
			
	}
	return 0;
}

int TSEvr_writeValue(FILE *to, TStoixeiouEvr Elem){ /*ektypwnei sto output ta stoixeia tou Elem*/
	int kd,i;
	char *anaxx = " Anaxwrhseis:     ",*afii = "    Afikseis:  ",*nn = "\n";
	char afikseis[10];
	char anaxwrhseis[10];
	itoa(Elem.afi,afikseis,10);
	itoa(Elem.anax,anaxwrhseis,10); 
	if(to==NULL)
	 	return 1;
	for(i=0;anaxx[i]!='\0';i++){
     	kd=anaxx[i];
		putc(kd,to);
	}
	for(i=0;anaxwrhseis[i] >= '0' && anaxwrhseis[i] <= '9';i++){
		kd = anaxwrhseis[i];
		putc(kd,to);
	}
	
	for(i=0;afii[i]!='\0';i++){
     	kd=afii[i];
		putc(kd,to);
	}
	for(i=0;afikseis[i] >= '0' && afikseis[i] <= '9';i++){
		kd = afikseis[i];
		putc(kd,to);
	}
	for(i=0;nn[i]!='\0';i++){
     	kd=nn[i];
		putc(kd,to);
	}
}

