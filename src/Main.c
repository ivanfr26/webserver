/*
 * Main.c
 *
 *  Created on: 08/08/2012
 *      Author: ivan
 */

#include <stdlib.h>
#include <stdio.h>

#include "libs/syslibs.h"
#include "libs/webserverlibrary.h"
#include "controller/FileParser.h"
#include "controller/tcp/server/server.h"

#define MYPORT 3490    // the port users will be connecting to
#define BACKLOG 10     // how many pending connections queue will hold

char *CONFIG_FILE_PATH = "/home/ivan/git/webserver/resources/WSconfig.txt";

void testBytelist(void);
void testReadBinary(void);

int main(int argc, char **argv) {

	map_t *configFile = readTextFile(CONFIG_FILE_PATH);

//	testBytelist();
//	testReadBinary()s;

	int socketServer; // listen on socketServer
	int socketClient;  // new connection on socketClient

	socketServer = tcp_socket();
	tcp_bind(socketServer, MYPORT);
	tcp_listen(socketServer, BACKLOG);

	while (1) {
		socketClient = tcp_accept(socketServer);
		tcp_writeText(socketClient, configFile->getValue('hello'));
	}

	return EXIT_SUCCESS;
}


void testReadBinary(){
	bytelist_t *myList = readBinaryFile(CONFIG_FILE_PATH);

	int i;
	for (i = 0; i < myList->size; ++i) {
		printf("%c", myList->list[i]);
	}
}

void testBytelist(){
	bytelist_t *myList;
	myList = newBytelist(FILE_MAX_SIZE);

	int max = FILE_MAX_SIZE + 1;

	int i;
	for (i = 0; i < max; ++i) {
		myList->addByte((uint_8*)(&i));
	}

	printf("myList size: %ld\n", myList->size);

	for (i = max - 4; i < max; ++i) {
		printf("%d: 0x%0x \n", i, myList->list[i]);
	}
}

