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
	./$(EXEC) -k composicao.txt -c configuracao.txt
