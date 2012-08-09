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

char *CONFIG_FILE_PATH = "/home/dev/workspace/webserver/resources/WSconfig.txt";

int main(int argc, char **argv) {

	map_t *initList = newMap();

	readFilePerLine(CONFIG_FILE_PATH, initList);

	entry_t *en = newEntry("wow", "wowVal");
	initList->add(en);

	int i;
	for (i = 0; i < initList->size; ++i) {
		printf("Entry: %d\n", i);
		printf("key: %s\n", initList->entries[i].key);
		printf("value: %s\n", initList->entries[i].value);
		puts("");
	}


	entry_t *found = initList->getValue("");

	puts(found->key);
	puts(found->value);

	return EXIT_SUCCESS;
}

