#ifndef _IO_H
#define _IO_H

#include "types.h"

void
allocate_image_char(IMG_Char *img, int rows, int cols);

void
allocate_image_float(IMG_Float *img, int rows, int cols);

void
free_image_char(IMG_Char *img);

void
free_image_float(IMG_Float *img);

void
read_image_char(char *fn, IMG_Char *img);

void
write_image_char(char *fn, IMG_Char img);

void
write_image_float(char *fn, IMG_Float img);

void
display_image_char(const char *wn, IMG_Char img);

void
display_image_float(const char *wn, IMG_Float img);

#endif