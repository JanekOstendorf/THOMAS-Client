ARGS= -std=c99

all: socket.o main.o
	gcc socket.o main.o -o thomas-client ${ARGS}
	
main.o: main.c
	gcc -c main.c ${ARGS}
	
socket.o: socket.c
	gcc -c socket.c ${ARGS}
	
clean:
	rm -rf ./*.o thomas-client