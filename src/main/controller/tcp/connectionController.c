/*
 * server.c

 *
 *  Created on: Aug 27, 2012
 *      Author: ivan
 */

#include "connectionController.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

/**
 * The return value from socket is the file descriptor for the new socket, or -1 in case of error.
 * And sets the socket option optname at level level.
 */
int tcp_socket(void) {
	int yes = 1;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd == TCP_ERROR) {
		perror("[SOCKET] - Unable to create socket.");
		return EXIT_FAILURE;
	}

	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		perror("[SOCKET] - Unable set the socket option optname.");
		return EXIT_FAILURE;
	}

	return sockfd;
}

/**
 * Assigns an address to the socket.
 */
int tcp_bind(int socket, short int port) {
	struct sockaddr_in my_addr;    // my address information

	my_addr.sin_family = AF_INET;         // host byte order
	my_addr.sin_port = htons(port);     // short, network byte order
	my_addr.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP
	memset(&(my_addr.sin_zero), '\0', 8); // zero the rest of the struct

	if (bind(socket, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == TCP_ERROR) {
		perror("[BIND] - Unable to bind the socket to port");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/**
 * Enables the socket socket to accept connections, thus making it a server socket.
 */
int tcp_listen(int socket, int backlog) {
	if (listen(socket, backlog) == TCP_ERROR) {
		perror("listen");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/**
 * Await a connection on socket FD.
 */
int tcp_accept(int socketServer) {
	struct sockaddr_in their_addr; // connector's address information
	int sin_size;

	int socketClient;

	sin_size = sizeof(struct sockaddr_in);
	if ((socketClient = accept(socketServer, (struct sockaddr *) &their_addr, &sin_size)) == TCP_ERROR) {
		perror("accept");
	}
	printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));

	return socketClient;
}

/**
 * Sends text to the socketClient
 */
int tcp_writeText(int socket, char *text) {
	if (send(socket, text, strlen(text), 0) == TCP_ERROR) {
		printf("[WRITE ERROR] - %s", text);
		perror("send");
	}

	return EXIT_SUCCESS;
}


/**
 * Reads text into the char *text parameter
 */
int tcp_readText(int socket, char *text, int maxTextSize) {
	int numbytes;

	numbytes = recv(socket, text, maxTextSize - 1, 0);

	if (numbytes == TCP_ERROR) {

		if (errno == EINTR) {
			tcp_readText(socket, text, maxTextSize);
			return EXIT_SUCCESS;
		}

		perror("recv");
		return EXIT_FAILURE;
	}
	text[numbytes] = '\0';

	return EXIT_SUCCESS;
}

/**
 * Closes the socket
 */
int tcp_close(int socket){
	close(socket);

	return EXIT_SUCCESS;
}