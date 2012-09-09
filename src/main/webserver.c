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

#define MYPORT 8080    // the port users will be connecting to
#define BACKLOG 10     // how many pending connections queue will hold

char *HTML_PATH = "/home/ivan/git/webserver/html";
char *HTTP_HEADER_PATH = "/home/ivan/git/webserver/resources/HTTP_Protocol.txt";
char *CONFIG_FILE_PATH = "/home/ivan/git/webserver/resources/WSconfig.txt";

map_t *configFile;

int main(int argc, char **argv) {

	int socketServer; // listen on socketServer
	int socketClient;  // new connection on socketClient

	socketServer = tcp_socket();
	tcp_bind(socketServer, MYPORT);
	tcp_listen(socketServer, BACKLOG);

	configFile = readConfigFile(CONFIG_FILE_PATH);

	while (1) {
		socketClient = tcp_accept(socketServer);

		//fork here to accept multiple connections
		processClient(socketClient);
	}

	return EXIT_SUCCESS;
}

char* getRequest(int socketClient) {
	char request[FILENAME_MAX];
	tcp_readText(socketClient, request, sizeof(request));

	int PREFIX = 5; //"GET /"

	int i = 0;
	char c = '\0';

	char *page = malloc(200);
	page[0] = '\0';

	while(c != ' '){
		c = request[PREFIX + i];
		page[i] = c;

		i++;
	}
	page[i-1] = '\0';

	return page;
}

int processClient(int socketClient){
	char *request = getRequest(socketClient);
	char* file = readTextFile(configFile->getValue(request)->value);

	char* textToSend;

	if(file != NULL){

		printf("[REQUEST] \"%s\"\n", request);
		textToSend = appendHeader(file);

	}else{

		printf("[NOT FOUND] \"%s\"\n", request);
		textToSend = appendHeader("Something went terribly wrong.");

	}

	tcp_writeText(socketClient, textToSend);

	free(file);
	free(request);
	free(textToSend);

	tcp_close(socketClient);
	return EXIT_SUCCESS;
}

