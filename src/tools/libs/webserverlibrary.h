/*
 * proyectResources.h
 *
 *  Created on: 08/08/2012
 *      Author: ivan
 */

#ifndef PROYECTRESOURCES_H_
#define PROYECTRESOURCES_H_

//Used system libraries
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// WebServer Definitions Library

/**
 * The max amount of lines at the WSconfig.txt file
 */
#define WS_CONFIG_MAX_LINES 100

/**
 * Each line of the Configuration file is a entry_t.
 */
typedef struct{
	char key[20];
	char value[FILENAME_MAX];
} entry_t;

typedef entry_t map_t[WS_CONFIG_MAX_LINES];


#endif /* PROYECTRESOURCES_H_ */
