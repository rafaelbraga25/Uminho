CC = gcc

OUT1 = sobusrv
OBJS1 = sobusrv.c

OUT2 = sobucli
OBJS2 = sobucli.c

install : srv cli

srv : $(OBJS1)
	$(CC) $(OBJS1) -Wall -Wconversion -pedantic -Wextra -o $(OUT1)

cli : $(OBJS2)
	$(CC) $(OBJS2) -Wall -Wconversion -pedantic -Wextra -o $(OUT2)


sobusrv.o : sobusrv.c 
	cc -c .c
	
sobucli.o : sobucli.c 
	cc -c .c

clean:
	rm -f *.o $(OUT)
