/*
 * Main.c
 *
 *  Created on: 08/08/2012
 *      Author: ivan
 */

#include <stdlib.h>
#include <stdio.h>

#include "../libs/syslibs.h"
#include "../libs/webserverlibrary.h"
#include "../tools/FileParser.h"
#include "controller/tcp/connectionController.h"

#define MYPORT 3490    // the port users will be connecting to
#define BACKLOG 10     // how many pending connections queue will hold

char *HTML_PATH = "/home/ivan/git/webserver/html";
char *HTTP_HEADER_PATH = "/home/ivan/git/webserver/resources/HTTP_Protocol.txt";
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
	int lines = readTextFile(strcat_t(HTML_PATH, configFile->getValue(request)->value), buffer);

	int len = 0;
	int i;

	for (i = 0; i < lines; ++i) {
		len = len + strlen(buffer[i]);
	}

	char str[15];
	sprintf(str, "%d", len);

	char header[10][500];
	readTextFile(HTTP_HEADER_PATH, header);

	strcpy(header[7], strcat_t("Content-Length: ", str));

	for (i = 0; i < 10; ++i) {
		tcp_writeText(socketClient, header[i]);
	}

	for (i = 0; i < lines; ++i) {
		tcp_writeText(socketClient, buffer[i]);
	}

	tcp_close(socketClient);
	return EXIT_SUCCESS;
}

