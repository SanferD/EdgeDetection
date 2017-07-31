#ifndef _PROC_H
#define _PROC_H

#include "types.h"

void
gradient_magnitude(IMG_Char gx, IMG_Char gy, IMG_Char res);

void
gradient_direction(IMG_Char gx, IMG_Char gy, IMG_Float  res);

void
threshold_char(IMG_Char in, IMG_Char out, unsigned char threshold);

void
threshold_float(IMG_Float in, IMG_Char out, float threshold);

void
enlarge_char(IMG_Char in, IMG_Char out, int count);

void
thinning_char(IMG_Char in, IMG_Char out);

#endif