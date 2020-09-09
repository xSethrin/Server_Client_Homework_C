/**
	Nikolo Sperberg
	Sterling Rohlinger
	CS 252
	File Name: node.c
	This code ceated the client/node
*/

#include <netdb.h> 
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <strings.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MAX 256 
#define PORT 9548 
#define SA struct sockaddr 


//method that finds prime number
int findPrime(int num){
	//int num = 13;
	int count = 2;
	int mod = 0;
	int temp = 0;
	while(count <= num){
		mod = num%count;
		if(mod == 0 && count != num){
			//printf("%d is not a prime number.\n", num);
			count = num + 1;
		}
		else if(count == num){
			//printf("%d is a prime number.\n", num);
			temp = 1;
		}
		count++;
	}
	return temp;
}


//caculates number of primes in a given range
int numberOfPrimes(int start, int end){
	int counter = start;
	int primeCount = 0;
	int temp = 0;
	while(counter <= end){
		temp = findPrime(counter);
		if(temp == 1){
			primeCount = primeCount + 1;
		}
		counter++;
	}
	//printf("Number of primes between %d and %d are %d\n", start, end, primeCount);
	return primeCount;
}

//method that calls the server
int callServer(char* host, int portno){
	int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
    // socket create and varification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else {
        printf("socket successfully created..\n"); 
	}
    bzero(&servaddr, sizeof(servaddr));   
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
	//user may need to change the address before compling
    servaddr.sin_addr.s_addr = inet_addr("10.35.195.46"); 
    servaddr.sin_port = htons(PORT); 
    // connect the client socket to server socket 
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else {
        printf("connected to the server..\n"); 
	}
	return sockfd;
}


//method to write data to the head.  reports error if exists
void writeInt(int primeCount, int sockfd) {
  int success = write(sockfd, &primeCount, sizeof(int));
  if (success < 0) {
    printf("unable to write to the socket...\n");
    exit(0);
  }
}

//method to read data to the head.  reports error if exists
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
	char* host = "localhost";
	int sockfd, primeCount, max, min;
	sockfd = callServer(host, PORT);
	//read the input from the head
	min = readInt(sockfd);
	max = readInt(sockfd);
	//method call to calculate number of primes
	primeCount = numberOfPrimes(min, max);
	//sends answer to head
	writeInt(primeCount, sockfd);
    // close the socket 
    close(sockfd); 
} 
