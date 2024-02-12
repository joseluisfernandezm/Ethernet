#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "nivelEth.h"
#include <stdint.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>

int stop=0, num_men=0, aux;
int send_time=0, send_time2=0;
char canal[20], canal_env[20]={0}, user2[20] = {0};
struct timeval currentTime;
struct tm *tm_actual;
struct tm *tm_actual2;
char buffer[BUFFSIZE], buffer2[BUFFSIZE], buffer3[BUFFSIZE];


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
	stop=1;
}

// Funcion de recepcion de mensajes. Esta funcion debe  llamada cada vez que se recibe un mensaje
// remitente: Direccion Eth remitente
// tamano: Tamaño del mensaje formato practica
//  mensaje : Buffer  mensaje
// tipo: Tipo ethernet de mensaje
// tv: Informacion de captura de la trama
int notificacion (const uint8_t *remitente,int tamano,const uint8_t *mensaje, uint16_t tipo,  const struct timeval *tv )

{
	// Funcion de recepcion de Tramas

	/**PRACTICA Implementar aquí las acciones necesarias al recibir un mensaje*/


	int comp = 0, TempTransferencia = 0, i, restaTemps = 0, TempTransferencia2 = 0;
	uint16_t longsig = 0;
	uint8_t message[1500]={0x00};
	uint16_t inct = 0;//incremento

	gettimeofday(&currentTime, NULL);//obtiene la hora del reloj del sistema en segundos
	tm_actual = localtime(&currentTime.tv_sec);//guardamos el tiampo actual en segundos en tm_actual
	strftime(buffer, BUFFSIZE, "%Y-%m-%d %H:%M:%S", tm_actual);//copiamos en buffer el tiempo actual en el formato indicado
																															/*La funcion strftime formatea la fecha :
																																%Y: Representación numérica del año en 4 dígitos;
																																%m: Representación numérica del mes con ceros iniciales;
																																%d: Día del mes incluyendo ceros iniciales;
																																%H: Representación numérica de la hora en 2 dígitos con formato 24h;
																																%M: Representación numérica de los minutos en 2 dígitos;
																																%S: Representación numérica de los segundos en 2 dígitos*/

	if(num_men==0){
		memcpy(&send_time2, mensaje+inct, 20);//metemos el tiempo (en segundos) en el que mensaje que nos llega en send_time2, para saber cuando inició el chat
		tm_actual2 = localtime(&send_time2);////guardamos el tiempo en el que se inició el chat (en segundos) en tm_actual2
		strftime(buffer3, BUFFSIZE, "%Y-%m-%d %H:%M:%S", tm_actual2);//copiamos en buffer3 el tiempo actual en el formato indicado
		TempTransferencia2 = currentTime.tv_sec - send_time2;//el tiempo actual menos en el que se envió el mensaje nos da cuanto tiempo este tarda en ser transmitido
		aux = send_time2;//guardamos en aux el tiempo en el que se envió el primer mensaje en segundos
	}//si es el primer mensaje

	else if(num_men!=0) {
		memcpy(&send_time, mensaje+inct, 20);//metemos el tiempo en segundos del mensaje que nos llega en send_time para saber cuando llegó el mesage numero num_men
		tm_actual = localtime(&send_time);//guardamos el tiampo en el que llegó el mensaje numero num_men en segundos en tm_actual
		strftime(buffer2, BUFFSIZE, "%Y-%m-%d %H:%M:%S", tm_actual);//copiamos en buffer2 el tiempo actual en el formato indicado
		TempTransferencia = currentTime.tv_sec - send_time;//el tiempo actual menos en el que se envió el mensaje nos da cuanto tiempo este tarda en ser transmitido
		restaTemps = send_time - aux;//en restaTemps guardamos la diferencia entre el tiempo en el que se envió el mensaje num_men y el tiempo en el que se envió el primer mensaje, lo cual nos da cuanto tiempo lleva el chat abierto
	}//no es el primer mensaje
	inct+=20;//incrementamos tras haber guardado el tiempo

	memcpy(user2, mensaje+inct, 20);//guardamos en user2 el nombre de usuario que hemos recibido
	inct+=20;//ya guardado el user en su variable aumentamos en 20 para seguir guardando info

	memcpy(canal_env, mensaje+inct, 20);//guardamos en canal_env el nombre del canal desde el que se nos envio el mensaje
	inct+=20;//incrementamos tras haber guardado el canal

	comp = memcmp(canal, canal_env, 20);//vemos si el canal del envio es el mismo que el de la recepcion si lo es comp=0
	if(comp == 0) {
		printf("------------------------¡MENSAJE RECIBIDO!------------------------\n");
	}
	else {
		printf("¡EL CANAL NO ES EL CORRECTO!\n");
		return ETH_ERROR;
	}

	memcpy(&longsig, mensaje+inct, sizeof(uint16_t));//metemos en longsig el tamanio del mensaje
	inct+=sizeof(uint16_t);//avanzamos 2bytes

	memcpy(message, mensaje+inct, longsig);//metemos en message el contenido del mensaje
	inct+=longsig;//avanzamoslo que ocupa el mensaje

	//presentamos la informacion recibida

	printf("Nombre de usuario: %s\n", user2);
	printf("MAC origen: %02x:%02x:%02x:%02x:%02x:%02x\n", remitente[0], remitente[1], remitente[2], remitente[3], remitente[4], remitente[5]);
	printf("Mensaje: %s", message);
	printf("Tiempo de inició de chat: %s\n", buffer3);
	if(num_men==0) {
		printf("Tiempo en el que inició el chat: 0 sec\n"); }
	else if(num_men!=0) {
		printf("Tiempo en el que inició el chat: %d sec\n", restaTemps);}
	if(num_men==0) {
		printf("Tiempo desde el envio del mensaje: %d sec\n\n", TempTransferencia2); }
	else if(num_men!=0){
		printf("Tiempo desde el envio del mensaje: %d sec\n\n", TempTransferencia); }

	num_men=num_men+1;//num_men nos dice en que mensaje del chat estamos


	return ETH_OK;

}




int main (int argc,char *argv[]){//recibir



	int resultado;
	int timeout=1000;
	int finalizado;
	uint16_t tipos[2];

		//Comprobacion del numero de argumentos pasado por la linea de comandos (ejecutable, canal)
	 if(argc!=2){
            printf("Error en el numero de parametros");
		return -1;
                    }


	strcpy(canal,argv[1]);//copiamos en canal el arg1[1] intoducido desde la terminal con el nombre del canal a escuchar
      //INICIALIZAMOS EL NIVEL Ethernet

    tipos[0]=TYPE1;//tipo de trama1
    tipos[1]=TYPE2;//tipo de trama2
	resultado=InicializarEth(tipos,2,notificacion,timeout);//la funcion InicializarEth retorna 1 si toda ha ido bien o -1 si no
	                                                       //como le pasamos un 2 como segundo parametro le estamos dando el Tipo2


	if (resultado==-1){
		printf("Error inicializando Ethernet\n");
		return -1;
		}


	signal(SIGINT,fn_signal);//para finalizar la escucha




	while(stop==0){


		/* Bucle infinito NO Modificar  */

	}//para la escucha constante



	finalizado=FinalizarEth();//si se ha finalizado con error finalizar=-1 en caso contrario finalixar=0
	if (finalizado==-1){

	printf("Error finalizando\n");
	return (EXIT_FAILURE);
	}
	else{

	printf("Finalizacion correcta\n");

	return (EXIT_SUCCESS);
	}

}
