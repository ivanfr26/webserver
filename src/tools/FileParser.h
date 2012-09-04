/*
 * FileParser.h
 *
 *  Created on: 08/08/2012
 *      Author: ivan
 */

#ifndef FILEPARSER_H_y
#define FILEPARSER_H_

#include "../libs/webserverlibrary.h"
#include "../tools/datatypes/map.h"
#include "../tools/datatypes/bytelist.h"

map_t* readConfigFile(char *file);
bytelist_t* readBinaryFile(char *name);
int readTextFile(char *file, char buffer[][500]);


#endif /* FILEPARSER_H_ */
