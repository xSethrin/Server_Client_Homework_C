all: head node

head: head.o
	gcc -o head -std=c99 head.o

head.o: head.c
	gcc -c head.c -std=c99 
	
node: node.o
	gcc -o node -std=c99 node.o 

node.o: node.c
	gcc -c node.c -std=c99 

clean:
	rm *.o head 
	rm *.o node
