Nombre del proyecto: AR2-4262-02-PR2
Autor: José Luis Fernández Moreno <joseluis.fernandezm@estudiante.uam.es>
Fecha:25/03/2021

Descripción: 

En esta carpeta AR2-4262-02-PR2 encontrará los diferentes archivos .c y .h para el desempeño de la práctica y otra carpeta "Memoria-Ejercicio4":

*En la carpeta "Memoria-Ejercicio4" se encuentra la memoria de la práctica 2 con las cuestiones teóricas del ejercicio 4 y un archivo .xlsx con los datos empleados para sacar la gráfica del último ejercicio.

*En la carpeta principal encontrará;

-Un archivo Makefile necesario para compilar la práctica, basta con ejecutar "make" en la terminal. Nota: puede que al hacer esto salten mensajes Warning, pero no afectan a la práctica

-main_enviar.c y main_recibir.c, el programa emisor y el receptor, los cuales se ejecutan:

	->(main_enviar.c): “. /recibir <canal>", en la terminal.
	->(main_recibir.c): “. /enviar <canal> <usuario>", en la terminal.

-main_enviar_ejercicio_3.c y main_recibir_ejercicio_3.c, con las modificaciones para los ejercicios 3 y 4, se ejecutan:

	->(main_enviar_ejercicio_3.c)”. /recibir_ej3 <canal>", en la terminal.
	->(main_recibir_ejercicio3.c)”. /enviar_ej3 <canal> <usuario>", en la terminal.
	
-nivelEth.c, con la implementación de la funcionalidad comunicación capa Ethernet.

-nivelEth.h, con las declaraciones de las funciones, las constantes y definiciones de tipo
que sean necesarias para su correcta utilización, para su inclusión por el resto de los
programas que utilicen el módulo.

-test_crc.c, rcfuncs.c, relativas al cálculo de CRC

-rcfuncs.h, archivo de cabecera de rcfuncs.c




