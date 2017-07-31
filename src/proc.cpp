#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "convolution.h"
#include "io.h"
#include "kernels.h"
#include "ops.h"
#include "proc.h"
#include "types.h"

void
gradient_magnitude(IMG_Char gx, IMG_Char gy, IMG_Char res)
{
	if (gx.rows != gy.rows || gx.cols != gy.cols)
	{
		printf("Gradient dimensions must match\n");
		exit(1);
	}

	unsigned char min=UCHAR_MAX, max=0;

	int i, j;
	for (i=0; i!=gx.rows; i++)
		for (j=0; j!=gx.cols; j++)
		{
			float xsqr = (float) gx.image[i][j]*gx.image[i][j];
			float ysqr = (float) gy.image[i][j]*gy.image[i][j];

			float mag = (float) sqrt(xsqr + ysqr);
			float smag= (char) floor(mag/1.414);
			res.image[i][j] = smag;

			if ((unsigned char) smag < (unsigned char) min) 
				min = smag;
			if ((unsigned char) smag > (unsigned char) max) 
				max = smag;
		}

	float dif = (float) (max - min);
	if (max != min)
		for (i=0; i!=gx.rows; i++)
			for (j=0; j!=gx.cols; j++)
			{
				float delta = (float) (res.image[i][j]-min);
				res.image[i][j] = (char) floor( delta*255.0/dif );
			}

}

void
gradient_direction(IMG_Char gx, IMG_Char gy, IMG_Float res)
{
	if (gx.rows != gy.rows || gx.cols != gy.cols)
	{
		printf("Gradient dimensions must match\n");
		exit(1);
	}

	int i, j;
	for (i=0; i!=gx.rows; i++)
		for (j=0; j!=gy.cols; j++)
		{
			float x = (float) gx.image[i][j];
			float y = (float) gy.image[i][j];

			res.image[i][j] = (char) atan2(y, x)*255.0;
		}
}

void
threshold_char(IMG_Char in, IMG_Char out, unsigned char threshold)
{
	int i, j;
	for (i=0; i!=in.rows; i++)
	{
		for (j=0; j!=in.cols; j++)
		{
			unsigned char pix = (unsigned char) in.image[i][j];
			out.image[i][j] = pix<threshold? (char)0: (char)255;
		}
	}
}

void
threshold_float(IMG_Float in, IMG_Char out, float threshold)
{
	int i, j;
	for (i=0; i!=in.rows; i++)
		for (j=0; j!=in.cols; j++)
		{
			float pix = in.image[i][j];
			out.image[i][j] = pix<threshold? (char)0: (char)255;
		}
}

void
enlarge_char(IMG_Char in, IMG_Char out, int count)
{
	IMG_Char tmp;
	allocate_image_char(&tmp, in.rows, in.cols);
	
	copy_image_char(in, tmp);

	while (count-- >= 0)
	{
		int i, j, x, y;
		for (i=0; i!=tmp.rows; i++)
			for (j=0; j!=tmp.cols; j++)
				if (out.image[i][j]=tmp.image[i][j])
					for (x=-1; x<=1; x++)
						for (y=-1; y<=1; y++)
						{
							int ix, jy;
							ix = i+x; jy = j+y;
							if (ix>=0 && jy>=0 && ix<tmp.rows && jy<tmp.cols)
								out.image[ix][jy] = 255;
						}
		
		if (count)
			copy_image_char(out, tmp);
	}

	free_image_char(&tmp);
}

void
thinning_char(IMG_Char in, IMG_Char out)
{
	IMG_Char E, kernel, to_keep;
	
	allocate_image_char(&E, in.rows, in.cols);
	allocate_image_char(&to_keep, in.rows, in.cols);

	logical_eq(in, 255, E);

	get_thinning_kernel(&kernel, 0);

	convolution_and(E, kernel, to_keep);

	free_image_char(&kernel);
	
	logical_mask(to_keep, E, to_keep);

	logical_le(to_keep, 2, E);
	logical_gt(to_keep, 0, to_keep);

	IMG_Char mask, tmp;
	allocate_image_char(&mask, in.rows, in.cols);
	allocate_image_char(&tmp, in.rows, in.cols);

	int i, j;
	for (i=0; i!=mask.rows; i++)
		for (j=0; j!=mask.cols; j++)
			mask.image[i][j] = (char) 0;

	for (i=1; i!=7; i++)
	{
		IMG_Char K;
		get_thinning_kernel(&K, i);
		convolution_sand(to_keep, K, tmp);

		free_image_char(&K);
		logical_or(tmp, mask, mask);
	}

	logical_mask(in, mask, out);
	logical_mask(in, E, mask);

	bitwise_or(out, mask, out);
}