all: server

server: server.o funcoes.o
	gcc server.o funcoes.o -o server
	
server.o: server.c
	gcc -c server.c

funcoes.o: incl/funcoes.c
	gcc -c incl/funcoes.c

clean: server
	rm *o server

run: server
	./server