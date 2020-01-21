/* Incluir a biblioteca do robô */
#include "mr32.h"
/* Incluir booleanos */
#include <stdbool.h>

int
main (void)
{
  /* initPIC32() makes all the required initializations to the
   * PIC32 hardware platform */
  initPIC32 ();
	
/* Definir B3 e B4 como inputs e Eo e E1 como outputs */
	TRISEbits.TRISE0 = 0;
	TRISEbits.TRISE1 = 0;
	TRISBbits.TRISB3 = 1;
	TRISBbits.TRISB4 = 1;
	
/* Definir variáveis */	
bool start,stop; /* Botoes start e stop */
int distancia; /* Distância de um obstáculo, atraves do sensor da frente */
int s1,s2E,s2D,s3E,s3D; /* Leitura do sensor de chão correspondente */
int x, correr, contar; /* Variáveis de estado auxiliares */
double velocidade; /* Multiplicador de velocidade do robô */
bool parar; /* Variável de controlo */
int n_voltas; /* Contador do numero de voltas */
int distancia_frente; /* Distância de um obstáculo, atraves do sensor da frente */
 
 enableObstSens(); /* Ligar os sensores de obstáculos */


  while (1) /* Loop */
    {	
	start=PORTBbits.RB3; /* Ler o estado dos botões */   /* !!!O botao start é igual a 1 quando não esta carregado (normalmente fechado)!!! */
	stop=PORTBbits.RB4;
	velocidade=1; /* Definir o multiplicador da velocidade */
	
 	if (start==0 && correr==0) { /* Se o Start estiver carregado e o robo nao estiver em funcionamento, entra em funcionamento e faz o reset do contador de voltas */
 	/*LATEbits.LATE0 = 1;*/
 	correr=1;
 	n_voltas=0;
	}

	if (stop==0) { /* Se o Stop estiver carregado, pára o funcionamento */
 	correr=0;
	}
	
	while(correr==1){ /* Loop de controlo durante o funcionamento */
		
	readAnalogSensors(); /* Ler os sensores de obstáculos */
    	distancia_frente=analogSensors.obstSensFront; /* Escrever o valor da distância ao obstáculo */
		
	if (distancia_frente <= 15) /* Se a distância ao obstáculo for menor que 15cm, ordena suspender temporariamente o funcionamento até sair o obstáculo */
        {
		parar=1;
        }
    	else {
		parar=0;
	}
 	
	enableGroundSens(); /* Ligar os sensores de chão */
	x=readLineSensors(0); /* Ler o valor dos sensores de chão */
 
	if(x==31) { /* Tabela de condições para andar em frente, virar ou parar. */
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
	if(parar==1){ /* Parar se tiver obstáculo */
	setVel2(0,0);
	}
	
	if (n_voltas < 16){ /* Contador de voltas quando o robot passa no travessão de volta */
		if (x==31){ /* Quando o robot entra no travessão, altera uma variável auxiliar de passagem pelo travessão*/
			contar=1;
			}
	if (x != 31 && contar==1) /* Quando o robot sai do travessão e tem a variável de passagem a um, incrementa o contador de volta */
        {
        n_voltas = n_voltas + 1;
        contar=0; /* Leva a variável auxiliar a zero */
        printInt10(n_voltas); /* Escreve na consola o numero de voltas */
		printStr("\n");
		}
	}
	
	if (n_voltas==16){ /* Quando acaba as voltas préprogramadas, faz um pião */
		setVel2(-50,50);
	}
	
	if(n_voltas==0){ /* Tabela de estados para acender os leds */
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
	    LATEbits.LATE3 = 0;
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
	    LATEbits.LATE3 = 0;
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
	    LATEbits.LATE3 = 1;
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
	    LATEbits.LATE3 = 1;
		}
		
	if (stop==0) { /* Parar o funcionamento do robot com o botão stop */
	    correr=0;
	        }
			}
			
}
  return (0);
}
