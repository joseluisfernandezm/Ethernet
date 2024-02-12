#---------------------------------------------------------------
# Otro Makefile
#---------------------------------------------------------------
# La siguiente no es necesariamente requerida, se agrega para
# mostrar como funciona.

.SUFFIXES: .o .c
.c.o:
	$(CC) -c $(CFLAGS) $<


# Macros

CC = gcc
CFLAGS = -g -Wall -lpcap -lpthread
SRC1 = main_enviar.c rc_funcs.c nivelEth.c rc_funcs.h  niveEth.h
SRC2 = main_recibir.c rc_funcs.c nivel1a.c rc_funcs.h nivelEth.h
SRC3 = main_enviar_ejercicio_3.C rc_funcs.c nivelEth.c rc_funcs.h  niveEth.h
SRC4 = main_recibir_ejercicio3.c rc_funcs.c nivel1a.c rc_funcs.h nivelEth.h
OBJ1 = main_enviar.o nivelEth.o rc_funcs.o
OBJ2 = main_recibir.o nivelEth.o rc_funcs.o
OBJ3 = main_enviar_ejercicio_3.o nivelEth.o rc_funcs.o
OBJ4 = main_recibir_ejercicio3.o nivelEth.o rc_funcs.o

# Reglas expl citas
all: receptor emisor receptor_ej3 emisor_ej3
receptor: $(OBJ1)
	$(CC)  $(OBJ1) -o enviar $(CFLAGS)
emisor: $(OBJ2)
	$(CC) $(OBJ2) -o recibir $(CFLAGS)
receptor_ej3: $(OBJ3)
	$(CC)  $(OBJ3) -o enviar_ej3 $(CFLAGS)
emisor_ej3: $(OBJ4)
	$(CC) $(OBJ4) -o recibir_ej3 $(CFLAGS)

clean:
	$(RM) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) receptor emisor receptor_ej3 emisor_ej3

# Reglas implicitas
rc_funcs.o: rc_funcs.c rc_funcs.h
main_recibir.o: main_recibir.c
main_enviar.o: main_enviar.c
main_recibir_ejercicio3.o: main_recibir_ejercicio3.c
main_enviar_ejercicio_3.o.o: main_enviar_ejercicio_3.c
nivel1a.o: nivel1a.c nivel1a.h
