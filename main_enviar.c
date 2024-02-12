#include "nivelEth.h"
#include "rc_funcs.h"
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>

struct timeval currentTime;
/*NOTA, así es la estructura timeval:
				struct timeval {
								time_t      tv_sec;      seconds
								suseconds_t tv_usec;    microseconds
						};*/

char buffer[BUFFSIZE];



void fn_signal(int nsignal)
{
	int finalizar=FinalizarEth();

	if (finalizar==-1){
	printf("Error finalizando\n");
	exit(1);
	}


	else{
		printf("Finalizacion correcta\n");
		exit(0);
		}

}
// main para la función enviar
int main(int argc,char *argv[]){

   char canal[20]={0};//cadena que guardara el nombre del canal
   char usuario[20]={0};//cadena que guardara el nombre del usuario
// Declaracion de Variables
	int resultado;
	uint16_t tipos[2];

	int finalizar;
	int enviado;
	uint8_t macdestino[6]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};//MAC de broadcast (a todos)

	int timeout=1000;
	char cadena[1456];//revisar para no exceder limite


	uint8_t trama_chat[1498]={0x00};//donde guardaremos el mensaje
        uint16_t incremento=0;//nos ayidara a ir guardando todo en la trama

	uint16_t longitud_camposiguiente;//tam del mensaje




        //Comprobacion del numero de argumentos pasado por la linea de comandos (ejecutable, canal , usuario)
	if(argc!=3){
            printf("Error en el numero de parametros\n Enviar canal usuario");
		return -1;

                    }

    tipos[0]=TYPE1;//tipo de trama1 0xBBBB
    tipos[1]=TYPE2;//tipo de trama2 0x4444
	resultado=InicializarEth(tipos,2,0,timeout);//la funcion InicializarEth retorna 1 si toda ha ido bien o -1 si no
                                              //como le pasamos un 2 como segundo parametro le estamos dando el Tipo2
	if (resultado==-1)
	{
                printf("Error al IniciarNivel eTH, resultado = %d \n",resultado);
		return -1;
	}
	else{

    	   memcpy(canal,argv[1],strlen(argv[1]));//copiamos en canal el argv[1] intoducido desde la terminal



            if (strlen(argv[1])>20){
			printf("El nombre del canal excede de la longitud permitida\n");
			return -1;
	               }

            else if(strlen(argv[1])==0){
                        printf("No se le ha pasado nada al nombre del canal\n");
			return -1;
                       }

        memcpy(usuario,argv[2],strlen(argv[2]));//copiamos en usuario el nombre que hallamos escrito en argv[2] desde la terminal


            if (strlen(argv[1])>20){
			printf("El nombre del canal excede de la longitud permitida\n");
			return -1;
	               }

            else if(strlen(usuario)==0){
                     printf("No se le ha pasado nada al nombre de usuario\n");
                     return -1;
                      }



	//Para salir del bucle pulsar Ctrl+C
	signal(SIGINT,fn_signal);

	while (1)
	{
		printf ("\nIntroduce Mensaje a enviar: ");
		fgets(cadena,1456,stdin);//guardamos en cadena el mensaje


		longitud_camposiguiente=strlen(cadena);//vemos cual es la longitud del mensaje

	/**PRACTICA Implementar aquí las acciones necesarias para crear un mensaje y un canal*/

		gettimeofday(&currentTime, NULL);//obtiene la hora del reloj del sistema en segundos
		memcpy(trama_chat+incremento, &currentTime.tv_sec, 20);//reservamos un tamaño de 20 caracteres para el tiempo y añadimos a trama_chat el tiempo actual en segundos currentTime.tv_sec
		incremento+=20;//avanzamos 20(por la reserva que hemos hecho) en trama_chat

		memcpy(trama_chat+incremento, &usuario, 20);//reservamos 20 caracteres para el nombre de usuario
		incremento+=20;//avanzamos en trama_chat los 20 caracteres de usuario

		memcpy(trama_chat+incremento, &canal, 20);//reservamos 20 caracteres para el nombre del canal
		incremento+=20;//avanzamos los 20 caracteres del nombre del canal

		memcpy(trama_chat+incremento, &longitud_camposiguiente, sizeof(uint16_t));// reservamos 2Bytes para Longitud del mensaje
		 incremento+=sizeof(uint16_t);//avanzamos los 2Bytes en trama_chat

		memcpy(trama_chat+incremento, &cadena, longitud_camposiguiente);//metemos el mensaje en trama_chat indicando en longitud_camposiguiente el tamaño del mensaje a partir del strlen que le hicimos arriba
		incremento+=longitud_camposiguiente;

    /*                *******************************             */

    	enviado=EnviarDatagramaEth(macdestino,trama_chat,incremento, TYPE2);//si no se ha enviado correctamente enviado=-1 y en el caso contrario enviado=0

		if (enviado==-1)
			printf("Error enviando trama\n");


		incremento=0;

		}
	}

	finalizar=FinalizarEth();//si se ha finalizado con error finalizar=-1 en caso contrario finalixar=0

	if (finalizar==-1){

	printf("Error finalizando\n");
	return(EXIT_FAILURE);}


	else{


	printf("Finalizacion correcta\n");

	return(EXIT_SUCCESS);}





}
