/**
	Nikolo Sperberg
	Sterling Rohlinger
	CS 252
	File Name: head.c
	This code ceated the server/head
*/

#include <netdb.h> 
#include <stdio.h> /* for printf() and fprintf() */ 
#include <sys/types.h> /* for Socket data types */ 
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */ 
#include <netinet/in.h> /* for IP Socket data types */ 
#include <arpa/inet.h> /* for sockaddr_in and inet_addr() */ 
#include <stdlib.h> /* for atoi() */ 
#include <string.h> /* for memset() */ 
#include <unistd.h> /* for close() */
#include <strings.h> 
#define MAX 256 
#define PORT 9548 
#define SA struct sockaddr 

//method to setup the server
int setupServerSocket(int portno){
	int sockfd, connfd; 
    struct sockaddr_in servaddr; 
    // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else{
        printf("socket successfully created..\n"); 
	}
    bzero(&servaddr, sizeof(servaddr)); 
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else{
        printf("socket successfully binded..\n"); 
	}
    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("listen failed...\n"); 
        exit(0); 
    } 
    else{
        printf("server listening..\n"); 
	}
	return sockfd;
}

//method to accept sockets
int serverSocketAccept(int sockfd){
	//printf("socket method\n");
	int connfd;
	struct sockaddr_in cli;
	int len = sizeof(cli);  
    // Accept the data packet from client and verification 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else{
        printf("server acccept the client...\n"); 
	}
	return connfd;
}

//method to write data to the nodes.  reports error if exists
void writeInt(int primeCount, int sockfd) {
	int success = write(sockfd, &primeCount, sizeof(int));
	if (success < 0) {
		printf("unable to write to the socket...\n");
    exit(0);
  }
}

//method to read data from node.  reports error if exists
int readInt(int connfd) {
  int value;
  int success = read(connfd, &value, sizeof(int));
  if (success < 0) {
    printf("unable to read from the socket...\n");
    exit(0);
  }
  return value;
}



//main method
int main() { 
	int sockfd, connfd0, connfd1, connfd2, value, value0, value1, value2, result0, result1, result2, result3, min0, max0, min1, max1, min2, max2;
	int start = 1000;
	int end = 1000000;
	int range = end - start;
	int divider = range/3; 
	//following lines set but the thre ranges for the three nodes
	min0 = start;
	max0 = min0 + divider;
	min1 = max0 + 1;
	max1 = min1 + divider - 1;
	min2 = max1 + 1;
	max2 = min2 + divider - 1;
	//set up servers and clients
	sockfd = setupServerSocket(PORT);
    connfd0 = serverSocketAccept(sockfd);
	connfd1 = serverSocketAccept(sockfd);
    connfd2 = serverSocketAccept(sockfd);
	//send the max and min to 1st node
	writeInt(min0, connfd0);
	writeInt(max0, connfd0);
	//receives the calculated value from node
	value0 = readInt(connfd0);
	//send the max and min to 2nd node
	writeInt(min1, connfd1);
	writeInt(max1, connfd1);
	//receives the calculated value from node
	value1 = readInt(connfd1);
	//send the max and min to 3rd node
	writeInt(min2, connfd2);
	writeInt(max2, connfd2);
	//receives the calculated value from node
	value2 = readInt(connfd2);
	//add the three returns together
	value = value0 + value1 + value2;
	//prints the answer to the console
	printf("value = %d\n", value); 
    //after chatting close the socket 
    close(sockfd); 
} 
