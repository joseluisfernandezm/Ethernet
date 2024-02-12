#include <stdint.h>
#include <stdio.h>

/********************************************************************************
*Funcion: CRCs							*
*Descripcion: Esta funcion calcula el CRC de un conjunto de datos		*

*Entrada:									*
*	data: Array de datos sobre los que calcular el CRC			*
*	len: longitud de los datos sobre los que calcular el CRC		*
*Salida: Esta funcion devuelve el valor del CRC calculado (1, 2, 4 bytes)		*
*										*
*********************************************************************************/
uint32_t crc32(int len, uint8_t *data);

