/*
 * server.h
 *
 *  Created on: Aug 27, 2012
 *      Author: ivan
 */

#ifndef SERVER_H_
#define SERVER_H_

#define TCP_ERROR -1   // error code use in the functions

#endif /* SERVER_H_ */

int tcp_socket(void);

int tcp_bind(int socket, short int port);

int tcp_listen(int socket, int backlog);

int tcp_accept(int socketServer);

int tcp_writeText(int socket, char *text);

int tcp_readText(int socket, char *text, int maxTextSize);

int processClient(int socketClient);

int tcp_close(int socket);




