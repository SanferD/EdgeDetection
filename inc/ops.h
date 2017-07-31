#ifndef _OPS_H
#define _OPS_H

#include "types.h"

void
logical_mask(IMG_Char input, IMG_Char mask, IMG_Char output);

void
logical_le(IMG_Char input, unsigned char value, IMG_Char output);

void
logical_gt(IMG_Char input, unsigned char value, IMG_Char output);

void
logical_or(IMG_Char input1, IMG_Char input2, IMG_Char output);

void
logical_eq(IMG_Char input, char value, IMG_Char output);

void
bitwise_or(IMG_Char input1, IMG_Char input2, IMG_Char output);

void
copy_image_char(IMG_Char original, IMG_Char copy);

#endif