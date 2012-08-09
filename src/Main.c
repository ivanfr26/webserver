/*
 * Main.c
 *
 *  Created on: 08/08/2012
 *      Author: ivan
 */

#include <stdlib.h>
#include <stdio.h>

#include "tools/libs/webserverlibrary.h"
#include "tools/tools.h"

char* CONFIG_FILE_PATH = "C:/Users/ivan/workspace/webserver/resources/WSconfig.txt";

int main(int argc, char **argv) {

	map_t initList;

	readConfigFile(CONFIG_FILE_PATH, initList);

	int i;
	for (i = 0; i < 10; ++i) {
		puts(initList[i].key);
		puts(initList[i].value);
	}


	return EXIT_SUCCESS;
}

