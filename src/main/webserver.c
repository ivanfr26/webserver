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

#define BACKLOG 10     // how many pending connections queue will hold

int PORT_LISTEN;
char *HTML_PATH;
size_t htmlPathLen;

char *CONFIG_FILE_PATH = "/home/ivan/git/webserver/resources/WSconfig.txt";

map_t *configFile;

enum {
	text,
	image,
	notSuported
};

int main(int argc, char **argv) {
	configFile = readConfigFile(CONFIG_FILE_PATH);

	HTML_PATH = configFile->getValue("HTML_PATH")->value;
	htmlPathLen = strlen(HTML_PATH);

	PORT_LISTEN = 8080;//configFile->getValue("PORT")->value;

	int socketServer; // listen on socketServer
	int socketClient;  // new connection on socketClient

	socketServer = tcp_socket();
	tcp_bind(socketServer, PORT_LISTEN);
	tcp_listen(socketServer, BACKLOG);


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

	int PREFIX = 4; //"GET /"

	int i = 0;
	char c = '\0';

	char *page = malloc(200);
	page[0] = '\0';

	while (c != ' ') {
		c = request[PREFIX + i];
		page[i] = c;

		i++;
	}
	page[i - 1] = '\0';

	return page;
}

char* getFilePath(size_t htmlPathLen, char* request, char* HTML_PATH) {
	char* name = malloc(htmlPathLen + strlen(request) + 1);
	strcat(name, HTML_PATH);
	strcat(name, request);
	return name;
}

void sendTextFile(char *request, int socketClient) {
	char* name = getFilePath(htmlPathLen, request, HTML_PATH);

	char *file = readTextFile(name);
	char *textToSend;
	if (file != NULL ) {

		printf("[REQUEST] \"%s\"\n", name);
		textToSend = appendTextHeader(file);

	} else {

		printf("[NOT FOUND] \"%s\"\n", request);
		textToSend = appendTextHeader("<p>sorry dude, l'page not found.</p>");

	}
	tcp_writeText(socketClient, textToSend);
	free(file);
	free(textToSend);
}

#include <sys/socket.h>

int getRequestType(char* request) {
	if (strstr(request, ".jpg") != NULL  ||
		strstr(request, ".jpeg") != NULL ||
		strstr(request, ".gif") != NULL ||
		strstr(request, ".bmp") != NULL) {
		return image;
	}

	return text;
}

int sendImageFile(int socketClient, bytelist_t* img, map_t* configFile, char* request) {
	char* name = getFilePath(htmlPathLen, request, HTML_PATH);
	img = readBinaryFile(name);

	if(img == NULL){
		return EXIT_FAILURE;
	}

	printf("[REQUEST IMAGE] \"%s\" size: %d\n", request, (int) img->size);
	tcp_writeText(socketClient, getImageHeader(img->size));
	if (send(socketClient, img->list, img->size, 0) == TCP_ERROR) {
		perror("send");
	}

	return EXIT_SUCCESS;
}

/**
 * Process a clients request and then closes the connection
 */
int processClient(int socketClient) {
	char *request = getRequest(socketClient);

	bytelist_t *img = NULL;

	switch (getRequestType(request)) {

	case text:
		sendTextFile(request, socketClient);
		break;

	case image:
		sendImageFile(socketClient, img, configFile, request);
		break;

	default:
		printf("File not supported yet: '%s' \n", request);
		break;
	}

	if(img != NULL){
		free(img);
	}
	free(request);

	tcp_close(socketClient);
	return EXIT_SUCCESS;
}

