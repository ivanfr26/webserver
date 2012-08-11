/*
 * map.c
 *
 *  Created on: Aug 9, 2012
 *      Author: irrolnik
 */

#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

map_t *map;

/*
 * Adds a new entry_t to the map.
 * Returns the index of that entry_t.
 */
int addEntry(entry_t *entry){
	int index = map->size;

	strcpy(map->entries[index].key, entry->key);
	strcpy(map->entries[index].value, entry->value);

	map->size = index + 1;

	return index;
}

entry_t* getValue(char *key) {
	entry_t *re = map->entries;

	int i;
	for (i = 0; i < map->size; ++i) {
		int isDifferent = strcmp(key, re->key);

		if (isDifferent == false) {
			return re;
		}

		re++;
	}

	return re;
}

/**
 * Creates a newEntry
 */
entry_t* newEntry(char *key, char *value) {
	entry_t *entry = malloc(sizeof(*map));

	strcpy(entry->key, key);
	strcpy(entry->value, value);

	return entry;
}

/**
 * Creates a newMap
 */
map_t* newMap() {
	map = malloc(sizeof(*map));
	map->getValue = getValue;
	map->addEntry = addEntry;

	return map;
}
