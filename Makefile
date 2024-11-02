TARGET = kitBoom

all: $(TARGET)

$(TARGET): entradaSaida.o logica.o main.o

	gcc entradaSaida.o logica.o main.o -o $(TARGET)

entradaSaida.o: entradaSaida.c kitBoom.h
	gcc -c entradaSaida.c -o entradaSaida.o

logica.o: logica.c kitBoom.h
	gcc -c logica.c -o logica.o

main.o: main.c kitBoom.h
	gcc -c main.c -o main.o

clean:
	rm -rf *.o $(TARGET)

run: all
	./$(TARGET) -k composicao.txt -c configuracao.txt
