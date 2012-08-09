/*
 * map.h
 *
 *  Created on: Aug 9, 2012
 *      Author: irrolnik
 */

#define MAP_MAX_SIZE 50

#define KEY_MAX_SIZE 20
#define VALUE_MAX_SIZE 260

typedef struct{
	char key[KEY_MAX_SIZE];
	char value[VALUE_MAX_SIZE];
} entry_t;

typedef struct{
	int size;
	entry_t entries[MAP_MAX_SIZE];

	//Looks for the matching key inside the map_t
	entry_t* (*getValue)(char *key);
	entry_t* (*add)(entry_t *entry);
} map_t;

map_t* newMap();

entry_t* newEntry(char *key, char *value);
map_t* newMap();
