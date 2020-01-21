#include "mr32.h"
#include <stdbool.h>


int
main (void)
{
  /* Variable declarations go here */

  /* initPIC32() makes all the required initializations to the
   * PIC32 hardware platform */
  initPIC32 ();

	TRISEbits.TRISE0 = 0;
	TRISEbits.TRISE1 = 0;

	TRISBbits.TRISB3 = 1;
	TRISBbits.TRISB4 = 1;
	
bool start,stop;
int distancia;
int s1,s2E,s2D,s3E,s3D;
int x, correr, contar;
double velocidade;
bool parar;

int n_voltas;
int distancia_frente;
 
 enableObstSens();


  while (1)
    {
		
	TRISBbits.TRISB3 = 1;
    TRISBbits.TRISB4 = 1;	
		
	start=PORTBbits.RB3;
	stop=PORTBbits.RB4;
	velocidade=1;
	

/* o botao start é igual a 1 quando não esta carregado (normalmente fechado) */

 	if (start==0 && correr==0) {
 	/*LATEbits.LATE0 = 1;*/
 	correr=1;
 	n_voltas=0;
	}

	if (stop==0) {
 	/*LATEbits.LATE0 = 0;*/
 	correr=0;
	}
	
	while(correr==1){
		
	readAnalogSensors();
    distancia_frente=analogSensors.obstSensFront;     	
		
		if (distancia_frente <= 15)
        {
			parar=1;
        }
    else {
		parar=0;
	}
 	
		
	enableGroundSens();
	x=readLineSensors(0);
	/*delay(1000);
	printInt10(x);
	printStr("\n");*/
 
	if(x==31) {
	setVel2(40*velocidade,40*velocidade);
	}
	if(x==4){
	setVel2(40*velocidade,40*velocidade);
	}
	if(x==6){
	setVel2(40*velocidade,15*velocidade);
	}
	if(x==2){
	setVel2(50*velocidade,-20*velocidade);
	}
	if(x==12){
	setVel2(15*velocidade,40*velocidade);
	}
	if(x==8){
	setVel2(-20*velocidade,50*velocidade);
	}
	if(x==0){
	setVel2(0,0);
	}
	if(parar==1){
	setVel2(0,0);
	}
	
	if (n_voltas < 16){
		if (x==31){
			contar=1;
			}
        if (x != 31 && contar==1)
        {
        n_voltas = n_voltas + 1;
        contar=0;
        printInt10(n_voltas);
		printStr("\n");
		}
	}
	
	if (n_voltas==16){
		setVel2(-50,50);
	}
	
		if(n_voltas==0){
            LATEbits.LATE0 = 0;
            LATEbits.LATE1 = 0;
            LATEbits.LATE2 = 0;
            LATEbits.LATE3 = 0;
          }
        if(n_voltas==1){
            LATEbits.LATE0 = 1;
            LATEbits.LATE1 = 0;
            LATEbits.LATE2 = 0;
            LATEbits.LATE3 = 0;
		}
        if(n_voltas==2){
            LATEbits.LATE0 = 0;
            LATEbits.LATE1 = 1;
            LATEbits.LATE2 = 0;
            LATEbits.LATE3 = 0;
		}
		if(n_voltas==3){
            LATEbits.LATE0 = 1;
            LATEbits.LATE1 = 1;
            LATEbits.LATE2 = 0;
			LATEbits.LATE0 = 0;
		}
		if(n_voltas==4){
            LATEbits.LATE0 = 0;
            LATEbits.LATE1 = 0;
            LATEbits.LATE2 = 1;
            LATEbits.LATE3 = 0;
		}
        if(n_voltas==5){
            LATEbits.LATE0 = 1;
            LATEbits.LATE1 = 0;
            LATEbits.LATE2 = 1;
            LATEbits.LATE3 = 0;
		}
        if(n_voltas==6){
            LATEbits.LATE0 = 0;
            LATEbits.LATE1 = 1;
            LATEbits.LATE2 = 1;
            LATEbits.LATE3 = 0;
		}
        if(n_voltas==7){
            LATEbits.LATE0 = 1;
            LATEbits.LATE1 = 1;
            LATEbits.LATE2 = 1;
			LATEbits.LATE0 = 0;
		}
    	     if(n_voltas==8){
            LATEbits.LATE0 = 0;
            LATEbits.LATE1 = 0;
            LATEbits.LATE2 = 0;
            LATEbits.LATE3 = 1;
		}
        if(n_voltas==9){
            LATEbits.LATE0 = 1;
            LATEbits.LATE1 = 0;
            LATEbits.LATE2 = 0;
            LATEbits.LATE3 = 1;
		}
        if(n_voltas==10){
            LATEbits.LATE0 = 0;
            LATEbits.LATE1 = 1;
            LATEbits.LATE2 = 0;
            LATEbits.LATE3 = 1;
		}
        if(n_voltas==11){
            LATEbits.LATE0 = 1;
            LATEbits.LATE1 = 1;
            LATEbits.LATE2 = 0;
			LATEbits.LATE0 = 1;
		}
		if(n_voltas==12){
            LATEbits.LATE0 = 0;
            LATEbits.LATE1 = 0;
            LATEbits.LATE2 = 1;
            LATEbits.LATE3 = 1;
		}
        if(n_voltas==13){
            LATEbits.LATE0 = 1;
            LATEbits.LATE1 = 0;
            LATEbits.LATE2 = 1;
            LATEbits.LATE3 = 1;
          }
        if(n_voltas==14){
            LATEbits.LATE0 = 0;
            LATEbits.LATE1 = 1;
            LATEbits.LATE2 = 1;
            LATEbits.LATE3 = 1;
		}
        if(n_voltas==15){
            LATEbits.LATE0 = 1;
            LATEbits.LATE1 = 1;
            LATEbits.LATE2 = 1;
			LATEbits.LATE0 = 1;
		}
		
		if (stop==0) {
		/*LATEbits.LATE0 = 0;*/
		correr=0;
		}
		
		
			}
			
}
  return (0);
}
