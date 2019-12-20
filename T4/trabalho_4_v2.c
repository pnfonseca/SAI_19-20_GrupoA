#include "mr32.h"
#include <stdbool.h>

int

main (void)
{
  initPIC32 ();

  int sensor_esquerdo;
  int sensor_direito;
  double voltagem_esquerda;
  double voltagem_direita;
  double voltagem_luz_ambiente;
  int limite=1700;
  int limite_frente=100;
  int luz_ambiente=1650;
  double diferenca;
  bool start, stop;

  
    TRISBbits.TRISB3 = 1;
    TRISBbits.TRISB4 = 1;

while (1)
    {
      /* Read line with default values */
      
      	start=PORTBbits.RB3;
		stop=PORTBbits.RB4;
      
      if (stop==0) {
		setVel2(0,0);
		printf("A calibrar \n");
		printf("Coloque o robô no seu habitat  \n");
		wait(30);
		printf("Afaste-se do robô! \n");
		wait(30);
		readAnalogSensors();
		sensor_esquerdo = analogSensors.an7;
		sensor_direito = analogSensors.an6;
		luz_ambiente=(sensor_esquerdo+sensor_direito)/2;
		voltagem_luz_ambiente=(luz_ambiente * 3300) / 1023;
		printf("Robô calibrado! \n");
		limite=luz_ambiente * 1.05;
		}
		
      readAnalogSensors();
      
      voltagem_esquerda=0;
      voltagem_direita=0;
      sensor_esquerdo = 0;
      sensor_direito = 0;
  
	  sensor_esquerdo = analogSensors.an7;
	  sensor_direito = analogSensors.an6;

	  voltagem_esquerda = (sensor_esquerdo * 3300) / 1023; /* Transformar o valor de analógico (entre 0 e 1023) para mV */
	  voltagem_direita = (sensor_direito * 3300) / 1023;

      diferenca = voltagem_esquerda - voltagem_direita; /* Se for positivo a esquerda é mais forte, se for negativo a direita é mais forte */

	  printf("Esquerda: %4.0f	\t Direita: %4.0f \t Diferença: %4.0f    \t", voltagem_esquerda, voltagem_direita, diferenca);

	  /*wait(1);*/

if ((voltagem_esquerda < limite) && (voltagem_direita < limite)) {
	   setVel2(0,0);
	   printf("\r");
	   }
else { 
	if (abs(diferenca) <= limite_frente) {
		if (voltagem_esquerda >= limite && voltagem_direita >= limite) {
			setVel2(30,30);
			printf("A andar em frente        \r");
		}
		else{
			printf("\r");
		}
	}
	else {
		if (diferenca < 0) {
			setVel2(0,30);
			printf("A andar para a esquerda   \r");
		}
		else {
			setVel2(30,0);
			printf("A andar para a direita   \r");
		}
	}
}

wait(3);
}
return (0);
}		


