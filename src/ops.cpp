#include "ops.h"

void
logical_mask(IMG_Char input, IMG_Char mask, IMG_Char output)
{
	int i, j;
	for (i=0; i!=input.rows; i++)
		for (j=0; j!=input.cols; j++)
			output.image[i][j] = input.image[i][j]*mask.image[i][j];
}

void
logical_le(IMG_Char input, unsigned char value, IMG_Char output)
{
	int i, j;
	for (i=0; i!=input.rows; i++)
		for (j=0; j!=input.cols; j++)
			output.image[i][j] = (unsigned char)input.image[i][j] <= value;
}

void
logical_gt(IMG_Char input, unsigned char value, IMG_Char output)
{
	int i, j;
	for (i=0; i!=input.rows; i++)
		for (j=0; j!=input.cols; j++)
			output.image[i][j] = (unsigned char)input.image[i][j] > value;
}


void
logical_eq(IMG_Char input, char value, IMG_Char output)
{
	int i, j;
	for (i=0; i!=input.rows; i++)
		for (j=0; j!=input.cols; j++)
			output.image[i][j] = input.image[i][j] == value;
}

void
logical_or(IMG_Char input1, IMG_Char input2, IMG_Char output)
{
	int i, j;
	for (i=0; i!=input1.rows; i++)
		for (j=0; j!=input1.cols; j++)
			output.image[i][j] = input1.image[i][j] || input2.image[i][j];
}


void
bitwise_or(IMG_Char input1, IMG_Char input2, IMG_Char output)
{
	int i, j;
	for (i=0; i!=input1.rows; i++)
		for (j=0; j!=input1.cols; j++)
			output.image[i][j] = input1.image[i][j] | input2.image[i][j];
}

void
copy_image_char(IMG_Char original, IMG_Char copy)
{
	int i, j;
	for (i=0; i!=original.rows; i++)
		for (j=0; j!=original.cols; j++)
			copy.image[i][j] = original.image[i][j];
}
