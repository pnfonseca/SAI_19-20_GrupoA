/* Just for test */

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

	TRISGbits.TRISG7 = 1;

bool start,stop;
int distancia, bit_lido, escutar, contagem_bit, espera;
char leituras[32];

escutar=0;
contagem_bit=0;
espera=0;

  while (1)
    {
	start=PORTBbits.RB3;
	stop=PORTBbits.RB4;


	bit_lido = LATGbits.LATG7;

	if (bit_lido==0 && escutar==0 && start==0){
		resetCoreTimer();
		escutar=1;
		contagem_bit=1;
		leituras[0]="0";
		printf("%c", 'leu o primeiro');
		printf( "\n" );
		}
	if (escutar==1 && contagem_bit==1  && readCoreTimer()>=13000 /*325microsegundos*/){

		bit_lido = LATGbits.LATG7;

		if (bit_lido==0){
			espera=26000;
			leituras[1]="0";
		}
		if (bit_lido==1){
			espera=22000;
			leituras[1]="1";
		}
		contagem_bit=2;
		printf("%c", 'leu o segundo');
		printf( "\n" );
		resetCoreTimer();
		}
	while (contagem_bit<=32 && contagem_bit>=2) {

		if (readCoreTimer()>=espera) {

			bit_lido = LATGbits.LATG7;

			if (bit_lido==0){
			espera=26000;
			leituras[contagem_bit]="0";
			}
			if (bit_lido==1){
			espera=22000;
			leituras[contagem_bit]="1";
			}
			contagem_bit=contagem_bit+1;
			resetCoreTimer();
			printf("%c", 'leu os outros');
			printf( "\n" );
		}



	}
	if (contagem_bit==32) {
		printf("%c", leituras);
		printf( "\n" );
		contagem_bit=0;
		strncpy( leituras, "1", sizeof( leituras ) );
		escutar=0;
		wait(10);
	}


    }
  return (0);
}
