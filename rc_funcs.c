#include "rc_funcs.h"

unsigned reverse(unsigned x) {
	x = ((x & 0x55555555) <<  1) | ((x >>  1) & 0x55555555);
	x = ((x & 0x33333333) <<  2) | ((x >>  2) & 0x33333333);
	x = ((x & 0x0F0F0F0F) <<  4) | ((x >>  4) & 0x0F0F0F0F);
	x = (x << 24) | ((x & 0xFF00) << 8) |
		((x >> 8) & 0xFF00) | (x >> 24);
	return x;
}

/*******************************************************************************
*Funcion: crc32								*
*Descripcion: Esta funcion calcula el CRC (Ethernet) de un conjunto de datos   *

*Entrada:									                                 *
*	data: Array de datos sobre los que calcular el CRC			             *
*	len: longitud de los datos sobre los que calcular el CRC		         *
*Salida: Esta funcion devuelve el valor del CRC calculado (4 bytes)          *
*        en notacion network Big enddian		                             *
*										                                     *
*********************************************************************************/

// Generating polynomial:
//const uint32_t ethernet_polynomial_le = 0xedb88320U;

//bit-oriented implementation: processes a byte array.


const uint32_t ethernet_polynomial_le = 0x04C11DB7;

//bit-oriented implementation: processes a byte array.
uint32_t crc32(int length, uint8_t *data) {

    unsigned int crc = 0;	/* Initial value. */
    while(--length >= 0) 
      {
	unsigned char current_octet = *data++;
	int bit;
	// printf("%02X, %08X,  inv %08X\n", current_octet, crc, ~crc);

	for (bit = 8; --bit >= 0; current_octet >>= 1) {
	  if ((crc ^ current_octet) & 1) {
	    crc >>= 1;
	    crc ^= ethernet_polynomial_le;
	  } else
	    crc >>= 1;
	}
      }
    // printf("crc final %x\n", crc);
    return crc;
  }
