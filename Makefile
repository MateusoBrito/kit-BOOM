CC = gcc

OBJ = main.o logica.o entradaSaida.o

EXEC = kitBoom

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ)

main.o: main.c kitBoom.h
	$(CC) -c main.c

entradaSaida.o: entradaSaida.c kitBoom.h
	$(CC) -c entradaSaida.c

logica.o: logica.c kitBoom.h
	$(CC) -c logica.c

clean:
	rm -rf *.o $(EXEC)

run: all
	./$(EXEC) -k configuracoes/composicao.txt -c configuracoes/configuracao.txt
	./$(EXEC) -k configuracoes/composicao2.txt -c configuracoes/configuracao2.txt
