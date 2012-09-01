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

int main(int argc, char **argv) {

	int socketServer; // listen on socketServer
	int socketClient;  // new connection on socketClient

	socketServer = tcp_socket();
	tcp_bind(socketServer, MYPORT);
	tcp_listen(socketServer, BACKLOG);

	while (1) {
		socketClient = tcp_accept(socketServer);

		//fork here to accept multiple connections
		processClient(socketClient);
	}

	return EXIT_SUCCESS;
}


int processClient(int socketClient){
	map_t *configFile = readConfigFile(CONFIG_FILE_PATH);

	char request[FILENAME_MAX];
	tcp_readText(socketClient, request, sizeof(request));

	char buffer[100][500];
	int lines = readTextFile(configFile->getValue(request)->value, buffer);

	int i;
	for (i = 0; i < lines; ++i) {
		tcp_writeText(socketClient, buffer[i]);
	}


	tcp_close(socketClient);
	return EXIT_SUCCESS;
}


