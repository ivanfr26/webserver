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
#include  "controller/FileParser.h"

#define CONFIG_FILE_PATH "C:/Users/ivan/git/webserver/resources/WSconfig.txt"
//char *CONFIG_FILE_PATH = "/home/dev/workspace/webserver/resources/WSconfig.txt";

void testReadTextFile(void);
void testBytelist(void);
void testReadBinary(void);

int main(int argc, char **argv) {

//	testReadTextFile();
//	testBytelist();

	testReadBinary();


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

void testReadTextFile(){
	map_t *initList = newMap();

	readTextFile(CONFIG_FILE_PATH, initList);

	entry_t *en = newEntry("wow", "wowVal");
	initList->addEntry(en);

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
}
