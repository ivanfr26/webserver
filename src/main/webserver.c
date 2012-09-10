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
#include "../tools/datatypes/bytelist.h"
#include "controller/tcp/connectionController.h"

#define MYPORT 8080    // the port users will be connecting to
#define BACKLOG 10     // how many pending connections queue will hold

char *HTML_PATH = "/home/dev/git/webserver/html";
char *HTTP_HEADER_PATH = "/home/dev/git/webserver/resources/HTTP_Protocol.txt";
char *CONFIG_FILE_PATH = "/home/dev/git/webserver/resources/WSconfig.txt";

map_t *configFile;

int main(int argc, char **argv) {

	int socketServer; // listen on socketServer
	int socketClient;  // new connection on socketClient

	socketServer = tcp_socket();
	tcp_bind(socketServer, MYPORT);
	tcp_listen(socketServer, BACKLOG);

	configFile = readConfigFile(CONFIG_FILE_PATH);

	puts("[WEBSERVER] Started");

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

void sendTextFile(char *request, int socketClient)
{
    char *file = readTextFile(configFile->getValue(request)->value);
    char *textToSend;
    if(file != NULL){

		printf("[REQUEST] \"%s\"\n", request);
		textToSend = appendTextHeader(file);

	}else{

		printf("[NOT FOUND] \"%s\"\n", request);
		textToSend = appendTextHeader("<p>sorry dude, l'page not found.</p>");

	}
    tcp_writeText(socketClient, textToSend);
    free(file);
    free(textToSend);
}

#include <sys/socket.h>

int processClient(int socketClient){
	char *request = getRequest(socketClient);

	if(strstr(request, "image")){
		bytelist_t *img = readBinaryFile(configFile->getValue(request)->value);

		printf("[REQUEST IMAGE] \"%s\" size: %d\n", request, (int)img->size);

		tcp_writeText(socketClient, getImageHeader(img->size));

		if (send(socketClient, img->list, img->size, 0) == TCP_ERROR) {
			perror("send");
		}

	}else{

		sendTextFile(request, socketClient);

	}

	free(request);

	tcp_close(socketClient);
	return EXIT_SUCCESS;
}

