CFLAGS = -g -Wall 

object = escalona.c agendamentos.c auxiliar.c grafos.c

all:  $(object)
	gcc $(object) -o escalona $(CFLAGS)

clean:
	rm -f *.o escalona

purge:	clean
	rm -f escalona

