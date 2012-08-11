/*
 * FileParser.h
 *
 *  Created on: 08/08/2012
 *      Author: ivan
 */

#ifndef FILEPARSER_H_y
#define FILEPARSER_H_

#include "../libs/syslibs.h"
#include "../model/map.h"
#include "../model/bytelist.h"

int readTextFile(char *file, map_t *buffer);
bytelist_t* readBinaryFile(char *name);


#endif /* FILEPARSER_H_ */
