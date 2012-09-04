/*
 * ByteList.h
 *
 *  Created on: 11/08/2012
 *      Author: ivan
 */

#ifndef BYTELIST_H_
#define BYTELIST_H_

#include "../../libs/syslibs.h"

//In bytes, 100Kb
#define FILE_MAX_SIZE 102400

typedef struct{

	//Bytes list
	uint_8 *list;

	//In Bytes
	fsize_t size;

	/*
	 * Adds a unit_8 to the end of the list,
	 * returns the index.
	 */
	int (*addByte)(uint_8 *byte);
} bytelist_t;


bytelist_t* newBytelist(fsize_t initialSize);


#endif /* BYTELIST_H_ */
