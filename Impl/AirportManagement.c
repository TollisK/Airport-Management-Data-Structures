/************************************************************************
Programma pelaths	: AirportManagement.c
Syggrafeas			: Karvelas Apostolos 1115201800312
Skopos				: skeleton main for askhsh 3
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "TSEvr.h"
#include "TSDDA.h"
#include "Evretirio.h"

int main(int argc, char *argv[]){
	EvrPtr E;
	TStoixeiouEvr *Data;/*proswrinh metavlhth gia thn topothetish toy apo to txt arxeio sto Insert*/
	FILE *ifp,*ifp2,*ofp,*Sifp,*Sofp,*Sifp2;
	int error=0,found=0,printcounter = 0,airportcounter=0,routecounter=0,airfound=0,airnotfound=0,simple=0;
	LARGE_INTEGER frequency;/*gia tous xronous*/
	LARGE_INTEGER t1, t2;
	double elapsedTime;
	QueryPerformanceFrequency(&frequency);
	E=EvrConstruct(7200);
	initialize(&Data,&simple);/*malloc Data kai twn metavlhtvn ths kai kathorizei to eidos toy dentroy gia to arxeio output*/
	if(simple){
		ofp = fopen("OUTPUTRandomBST.txt.","w");
		Sofp = fopen("OUTPUTSortedBST.txt.","w");
	}
	else{
		ofp = fopen("OUTPUTRandomAVL.txt.","w");
		Sofp = fopen("OUTPUTSortedAVL.txt.","w");
	}
		
	ifp = fopen("airportsWinRandom.txt", "r");
	ifp2 = fopen("routesWin.txt","r");
	Sifp = fopen("airportsWinSorted.txt", "r");
	Sifp2 = fopen("routesWin.txt","r");
	if(ofp==NULL||Sofp==NULL||ifp==NULL||ifp2==NULL||Sifp==NULL||Sifp2==NULL)/*if any of the files doesnt work*/
		printf("Error with the input or output files!");
	printf("Me tyxaies eisodous:\n");
	fprintf(ofp,"Me tyxaies eisodous:\n");
	QueryPerformanceCounter(&t1);
	while(TSEvr_readValue(ifp,Data) != 1){ /*While ifp != EOF*/
		if(Evr_Insert(E,*Data))
			printf("Error!");
		airportcounter++;
		if(airportcounter == 511||airportcounter == 1023||airportcounter==2047||airportcounter == 4095){
			QueryPerformanceCounter(&t2);
			elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
    		fprintf(ofp,"Meta apo 2^N - 1 stoixeia: %g msec\n", elapsedTime);
    		printf("Meta apo 2^N - 1 stoixeia: %g msec\n", elapsedTime);
		}	
	}
	fprintf(ofp,"Gia N = 9,10,11,12 antistoixa\n");
	printf("Gia N = 9,10,11,12 antistoixa\n");
	fprintf(ofp,"Synolika %d stoixeia\n",airportcounter);
	printf("Synolika %d stoixeia\n",airportcounter);
	QueryPerformanceCounter(&t2);
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
    fprintf(ofp,"Synolikos xronos eisagwghs stoixeiwn: %g msec\n", elapsedTime);
	printf("Synolikos xronos eisagwghs stoixeiwn: %g msec\n", elapsedTime);
	QueryPerformanceCounter(&t1);
	while(TSEvr_readValueRoutes(ifp2,Data) != 1 ){ /*While ifp2!=EOF thetei to Data->id = Source airportId kai to Data->name = Destination airportId*/
		EvrSearch(E,atoi(Data->id),1,&found); /*anaxwrhseis*/
		if(found) /*an brethei ay3anei ton counter kata 1*/
			airfound++;
		else
			airnotfound++;	
		EvrSearch(E,atoi(Data->name),0,&found);	/*afikseis*/
		if(found)
			airfound++;
		else
			airnotfound++;		
		routecounter++;
	}
	routecounter++;	
	EvrSearch(E,atoi(Data->id),1,&found);/*Gia thn teleutaia grammh toy ifp2*/
	if(found)
		airfound++;
	else
		airnotfound++;			
	EvrSearch(E,atoi(Data->name),0,&found);
	if(found)
		airfound++;
	else
		airnotfound++;
		
	QueryPerformanceCounter(&t2);
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
	fprintf(ofp,"Diabase %d syndeseis\n",routecounter);
	fprintf(ofp,"Brethhkan %d aerodromia\n",airfound);
	fprintf(ofp,"Den brethhkan %d aerodromia\n",airnotfound);
    fprintf(ofp,"Synolikos xronos enhmerwshs: %g msec\n", elapsedTime);
    fprintf(ofp,"O mesos xronos anazhthshs enos aerodromioy einai %g msec\n",elapsedTime/(routecounter*2));/*ta synolika aerodromia poy diabase einai oso oi syndeseis epi 2*/
    QueryPerformanceCounter(&t1);
	Evr_PrintAll(E,ofp,&printcounter);	
	QueryPerformanceCounter(&t2);
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;/*apo edw*/
    fprintf(ofp,"Ektypwthikan %d stoixeia\n",printcounter);
    fprintf(ofp,"Synolikos xronos ektypwshs: %g msec\n", elapsedTime);
	Evr_katastrofi(&E); /*katastrefei to EvrPtr wste na 3anarxisoyme me diaforetiko input txt*/ /*ews edw mexri stigms*/
	/*E = NULL;*/
	fprintf(Sofp,"Me taksinomimenes eisodous:\n");
	printcounter = 0;airportcounter = 0;routecounter = 0;airfound = 0;airnotfound = 0;
	E=EvrConstruct(7200);
	QueryPerformanceCounter(&t1);
	while(TSEvr_readValue(Sifp,Data) != 1){/*TSEvr_readValue(ifp,Data) != 1*/
		if(Evr_Insert(E,*Data))
			printf("error!");	
		airportcounter++;
		if(airportcounter == 511||airportcounter == 1023||airportcounter==2047||airportcounter == 4095){
			QueryPerformanceCounter(&t2);
			elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
    		fprintf(Sofp,"Meta apo 2^N - 1 stoixeia: %g msec\n", elapsedTime);
		}	
	}
	fprintf(Sofp,"Gia N = 9,10,11,12 antistoixa\n");
	fprintf(Sofp,"Synolika %d stoixeia\n",airportcounter);
	QueryPerformanceCounter(&t2);
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
	fprintf(Sofp,"Synolikos xronos eisagwghs stoixeiwn: %g msec\n", elapsedTime);
	QueryPerformanceCounter(&t1);
	while(TSEvr_readValueRoutes(Sifp2,Data) != 1 ){
		EvrSearch(E,atoi(Data->id),1,&found);/*anaxwrhseis*/
		if(found)
			airfound++;
		else
			airnotfound++;
		EvrSearch(E,atoi(Data->name),0,&found);/*afikseis*/
		if(found)
			airfound++;
		else
			airnotfound++;
		routecounter++;
		
	}
	routecounter++;	
	EvrSearch(E,atoi(Data->id),1,&found);/*gia ton teleytaio*/
	if(found)
			airfound++;
		else
			airnotfound++;
	EvrSearch(E,atoi(Data->name),0,&found);
	if(found)
			airfound++;
		else
			airnotfound++;
	QueryPerformanceCounter(&t2);
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
	fprintf(Sofp,"Diabase %d syndeseis\n",routecounter);
	fprintf(Sofp,"Brethhkan %d aerodromia\n",airfound);
	fprintf(Sofp,"Den brethhkan %d aerodromia\n",airnotfound);
    fprintf(Sofp,"Synolikos xronos enhmerwshs: %g msec\n", elapsedTime);
    fprintf(Sofp,"O mesos xronos anazhthshs enos aerodromioy einai %g msec\n",elapsedTime/(routecounter*2));
    
    QueryPerformanceCounter(&t1);
	Evr_PrintAll(E,Sofp,&printcounter);	
	QueryPerformanceCounter(&t2);
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
    fprintf(Sofp,"Ektypwthikan %d stoixeia\n",printcounter);
	fprintf(Sofp,"Synolikos xronos ektypwshs: %g msec\n", elapsedTime);
	printf("Every detail is in the output files!");
	if(simple){/*kleinei tous deiktes*/
		fclose(ofp);
		fclose(Sofp);
	}
	else{
		fclose(ofp);
		fclose(Sofp);
	}
		
	fclose(ifp);
	fclose(ifp2);
	fclose(Sifp);
	fclose(Sifp2);
	Evr_katastrofi(&E);
	free(Data);/*eleytherwnei  ton deikti Data*/


	return 0;
}

