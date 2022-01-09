/************************************************************************
Programma pelaths	: Evretirio.c
Syggrafeas			: Karvelas Apostolos 1115201800312
Skopos				: kyria function gia thn main
*************************************************************************/
#include "Evretirio.h"

#define Simple 1 /* 0 for AVL - any Evr integer for Simple  */

/* Oi diafores tvn ylopoihsevn Simple kai AVL einai mikres - mporeite na xrhsimopoihsete 
   thn  domh #if ... #else ...#endif gia na diaforopihsete tis dyo ylopoihseis  */
   
#if (Simple)
#include "BST/ch8_BSTpointer.h" /* gia Simple Ylopoihsh */
#else
#include "AVL/ch8_AVLpointer.h" /* gia AVL Ylopoihsh */
#endif

int Rec(EvrPtr E,FILE *out,typos_deikti riza,int *counter);/*anadromikh synarthsh gia thn xrhsh ths sthn Evr_PrintAll*/


struct EvrNode{
       TStoixeiouEvr *DataArray; /* array of size MaxSize */
       int Index;              /* index of first available element in array */
       typos_deikti TreeRoot;     /* Root of DDA */
} EvrNode;

EvrPtr EvrConstruct(int MaxSize){
/* Oi diafores tvn ylopoihsevn Simple kai AVL einai mikres - 
	mporeite na xrhsimopoihsete thn  domh #if ... #else ...#endif */
	EvrPtr Evr;
	typos_deikti TreeRoot;
   	Evr = malloc(sizeof(EvrNode));
   	Evr->DataArray = NULL;

   	Evr->DataArray = malloc(MaxSize*sizeof(TStoixeiouEvr));
	Evr->Index = 0; 

#if (Simple)
   printf("use simple BST\n");
   Tree_dimiourgia(&TreeRoot);
#else   
    printf("use AVL BST\n");
    AVLTree_dimiourgia(&TreeRoot);
    
#endif
	Evr->TreeRoot = TreeRoot;
	return Evr;
}

int Evr_Insert(EvrPtr E, TStoixeiouEvr Data){/*arxikopoihsh twn data*/
	int error;
	int avl;
	TStoixeiouDDA stoixeio;
	TStoixeiouEvr btdata,btdata2;
	TSEvr_setValue (&E->DataArray[E->Index],Data);
	stoixeio.arrayIndex = E->Index;
	stoixeio.key = atoi(Data.id);/*metatrapei to Data.id apo string se integer gia thn xrhsh toy ws klhdh*/
	#if (Simple)
		Tree_eisagogi(&E->TreeRoot,stoixeio,&error);
	#else
		AVLTree_eisagogi(&E->TreeRoot,stoixeio,&avl,&error);
	#endif	
	E->Index++;
	if(error)
		return 1;
	return 0;
}

int EvrSearch(EvrPtr E, keyType key, int InOut, int * found){
	typos_deikti deiktis;
	TStoixeiouDDA stoixeio;
	TStoixeiouEvr *st;
	stoixeio.key = key;
	stoixeio.arrayIndex = 0;
	#if (Simple)
		Tree_anazitisi(E->TreeRoot,stoixeio,&deiktis,found);
		Tree_periexomeno(deiktis, &stoixeio);
	#else
		AVLTree_anazitisi(E->TreeRoot,stoixeio,&deiktis,found);
		AVLTree_periexomeno(deiktis, &stoixeio);
	#endif	
	st = E->DataArray+stoixeio.arrayIndex;
	if(found){
		if(InOut)
			st->anax++;
		else
			st->afi++;	
	}

	return 0;
}


int Evr_PrintAll(EvrPtr E, FILE *out, int * counter){
	typos_deikti deiktis = E->TreeRoot;
/* endo-diadromh - use recursion with apaidi-depaidi */ 
/* example of use */

#if (Simple)
    Rec(E,out,deiktis,counter);
#else   
    Rec(E,out,deiktis,counter);
#endif
	return 0;
}

int Rec(EvrPtr E,FILE *out,typos_deikti riza,int *counter){ /*Anadromikh synarthsh me endodiata3h*/
		TStoixeiouDDA stoixeio;
	#if (Simple)
		if(!Tree_keno(riza)){
			Rec(E,out,Tree_apaidi(riza),counter);
			Tree_periexomeno(riza,&stoixeio);
			fprintf(out,"Airport ID: %d ", stoixeio.key);/*ektypwnei sto output*/
			TSEvr_writeValue(out,E->DataArray[stoixeio.arrayIndex]);
			*counter+=1;
			Rec(E,out,Tree_dpaidi(riza),counter);
		}
	#else	
		if(!AVLTree_keno(riza)){
			Rec(E,out,AVLTree_apaidi(riza),counter);
			AVLTree_periexomeno(riza,&stoixeio);
			fprintf(out,"Airport ID: %d ", stoixeio.key);
			TSEvr_writeValue(out,E->DataArray[stoixeio.arrayIndex]);
			*counter+=1;
			Rec(E,out,AVLTree_dpaidi(riza),counter);
		}
	#endif	
}	
	



int Evr_katastrofi(EvrPtr *E){
	#if (Simple)
		Tree_katastrofi(&(*E)->TreeRoot);
	#else
		AVLTree_katastrofi(&(*E)->TreeRoot);
	#endif		
		free((*E)->DataArray);
		(*E)->DataArray = NULL;
		E = NULL;	
}

int initialize(TStoixeiouEvr **Data,int *simple){ 
	#if (Simple)
		*simple = 1;
	#else
		*simple = 0;
	#endif	
	(*Data) = malloc(sizeof(TStoixeiouEvr));
	(*Data)->id = malloc(7*sizeof(char));	
	(*Data)->name = malloc(50*sizeof(char));
	(*Data)->city = malloc(50*sizeof(char));
	(*Data)->country = malloc(50*sizeof(char));
	(*Data)->iata = malloc(50*sizeof(char));
	(*Data)->icao = malloc(50*sizeof(char));
	(*Data)->afi = 0;
	(*Data)->anax = 0;
}






