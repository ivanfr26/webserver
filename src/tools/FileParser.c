/*
 * FileParser.c
 *
 *  Created on: 08/08/2012
 *      Author: ivan
 */

#include "FileParser.h"

int setKey(char *key, char *line);
int setValue(char *value, char *line, int keylen);

/**
 * Reads a config file and saves it in the buffer
 */
int readConfigFile(char *file, map_t configList) {
	FILE *fp;
	fp = fopen(file, "rt");

	char line[FILENAME_MAX];
	int eof;

	int i;
	while((eof = feof(fp)) == false){
		fgets(line, FILENAME_MAX, fp);

		int keylen = setKey(configList[i].key, line);
		setValue(configList[i].value, line, keylen);

		i++;
	}

	return i;
}


int setKey(char *key, char *line){

	int i = 1;
	char c;
	while((c = *line++) != '='){
		i++;
	}

	line -= i;

	char re[i + 1];

	int j;
	for (j = 0; j < i-1; ++j) {
		re[j] = *line++;
	}
	re[j] = '\0';

	strcpy(key, re);
	return j;
}

int setValue(char *value, char *line, int keylen){
	char re[FILENAME_MAX];

	line += (keylen + 1);

	int j;
	for (j = 0; j < FILENAME_MAX; ++j) {
		re[j] = *line++;
	}
	re[j] = '\0';

	strcpy(value, re);
	return j;
}
