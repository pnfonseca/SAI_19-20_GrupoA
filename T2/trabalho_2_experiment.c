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
int distancia, bit_lido, escutar, contagem_bit, espera, i;
char leituras[32];

escutar=0;
contagem_bit=0;
espera=0;
printf("acordei");
printf( "\n" );

  while (1)
    {
	
	start=PORTBbits.RB3;
	stop=PORTBbits.RB4;
	
	bit_lido = LATGbits.LATG7;
	
	if (bit_lido==0 && escutar==0 && stop==0){
		resetCoreTimer();
		escutar=1;
		contagem_bit=1;
		leituras[0]='0';
		printf("leu o primeiro");
		printf( "\n" );
		}
	if (escutar==1 && contagem_bit==1  && readCoreTimer()>= 13000 /*325microsegundos*/){

		if (bit_lido==0){
			espera=26000;
			leituras[1]='0';
		}
		if (bit_lido==1){
			espera=22000;
			leituras[1]='1';
		}
		contagem_bit=2;
		printf("leu o segundo");
		printf( "\n" );
		resetCoreTimer();
		}
	while (contagem_bit<31 && contagem_bit>=2) {
		
		if (readCoreTimer()>=espera) {
			
			bit_lido = LATGbits.LATG7;
		
			if (bit_lido==0){
			espera=26000;
			leituras[contagem_bit]='0';
			}
			if (bit_lido==1){
			espera=22000;
			leituras[contagem_bit]='1';
			}
			contagem_bit=contagem_bit+1;
			resetCoreTimer();
			printf("leu os outros");
			printf( "\n" );
		}
		
			
		
	}
 int i=0;
	if (contagem_bit==31) {	
		for(i=0;i<=31;++i){
		printf("%d", leituras[i]);
	}
		printf( "\n" );
		printf("acabei de ler");
		printf( "\n" );
		contagem_bit=0;
		strncpy( leituras, '1', sizeof( leituras ) );
		escutar=
		0;
		wait(5);
		if(leituras[i]='0000101010010100100100100101010'){
		setVel2(100,100);
}
	}
	wait(10);	

	

}
  return (0);
  


}
