/*
 * bytelist.c
 *
 *  Created on: 11/08/2012
 *      Author: ivan
 */

#include "../libs/syslibs.h"
#include "bytelist.h"

bytelist_t *bytelist;

/*
 * Adds a unit_8 to the end of the list,
 * returns the index.
 */
int addByte(uint_8 *byte){
	int index = bytelist->size;

	bytelist->list[index] = *byte;
	bytelist->size = index + 1;

	return index;
}

/*
 * Returns a new instance of a bytelist_t
 */
bytelist_t* newBytelist(fsize_t initialSize){
	bytelist = malloc(sizeof(bytelist_t));
	bytelist->list = malloc(initialSize + 1);
	bytelist->size = initialSize;
	bytelist->addByte = addByte;
	return bytelist;
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
