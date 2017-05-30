CC = gcc
CFLAGS = -Wall -Wextra -Wconversion -ansi -pedantic -O2 -g
OUT = gereVendas
OBJS = main.o faturacaoGlobal.o gestaoFilial.o bstmap.o catalogoClientes.c catalogoProdutos.o bstree.o iterator.o

project : $(OBJS)
	$(CC) $(OBJS) -o $(OUT) $(CFLAGS)

main.o : main.c bstree.h iterator.h catalogoClientes.h catalogoProdutos.h gestaoFilial.h faturacaoGlobal.h
	cc -c main.c
faturacaoGlobal.o : faturacaoGlobal.c bstmap.h bstree.h iterator.h faturacaoGlobal.h
	cc -c faturacaoGlobal.c

gestaoFilial.o : gestaoFilial.c bstmap.h bstree.h iterator.h gestaoFilial.h
	cc -c gestaoFilial.c

bstmap.o : bstmap.c bstmap.h bstree.h iterator.h
	cc -c bstmap.c

catalogoClientes.o : catalogoClientes.c bstree.h iterator.h catalogoClientes.h
	cc -c catalogoCientes.c

catalogoProdutos.o : catalogoProdutos.c bstree.h iterator.h catalogoProdutos.h
	cc -c catalogoProdutos.c

bstree.o : bstree.c bstree.h iterator.h
	cc -c bstree.c

iterator.o : iterator.h iterator.c
	cc -c iterator.c

clean:
	rm -f *.o $(OUT)
