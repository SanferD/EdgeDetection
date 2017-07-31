#ifndef _TYPES_H
#define _TYPES_H

typedef struct _IMG_Char {
	int rows;
	int cols;
	char **image;
} IMG_Char;

typedef struct _IMG_Float {
	int rows;
	int cols;
	float **image;
} IMG_Float;

#endif