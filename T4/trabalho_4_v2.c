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

  int luz_ambiente=1650;
  int limite=luz_ambiente*1.02;
  double diferenca;
  bool start, stop;
  double velocidade=30;
  double degrade=velocidade/luz_ambiente;

  
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
		limite=luz_ambiente * 1.02;
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
	  
/*Verificar se tiver pouca luz*/
if ((voltagem_esquerda < limite) && (voltagem_direita < limite)) {
	 /*Se sim, pára*/
	   setVel2(0,0);
	   printf("\r");
	   }
/*Se tiver luz*/  
else {
		setVel2(velocidade+(degrade*diferenca),velocidade-(degrade*diferenca));
		printf("A andar para o lado   \r");
	}


wait(3);
}
return (0);
}		


