#include "convolution.h"

void
convolution(IMG_Char input, IMG_Char kernel, IMG_Char output)
{
	int khx, khy, mx, my;

	mx = khx = kernel.rows/2;
	my = khy = kernel.cols/2;

	if (kernel.rows & 0x1)
		mx++;
	if (kernel.cols & 0x1)
		my++;

	int i,j;
	for (i=0; i<input.rows; i++)
		for (j=0; j<input.cols; j++)
		{
			output.image[i][j] = 0;
			int x, y;
			for (x=-khx; x<mx; x++)
				for (y=-khy; y<my; y++)
				{
					char pix, kpix;

					int ix=i+x, jy=j+y;
					if (ix<0 || jy<0 || ix>=input.rows || jy>=input.cols)
						pix = 0;
					else
						pix = input.image[ix][jy];

					kpix = kernel.image[x+khx][y+khy];
					output.image[i][j] += pix*kpix;
				}
		}
}

void
convolution_and(IMG_Char input, IMG_Char kernel, IMG_Char output)
{
	int khx, khy, mx, my;

	mx = khx = kernel.rows/2;
	my = khy = kernel.cols/2;

	if (kernel.rows & 0x1)
		mx++;
	if (kernel.cols & 0x1)
		my++;

	int i, j;
	for (i=0; i<input.rows; i++)
		for (j=0; j<input.cols; j++)
		{
			output.image[i][j] = 0;
			int x, y;
			for (x=-khx; x<mx; x++)
				for (y=-khy; y<my; y++)
				{
					char pix, kpix;

					int ix=i+x, jy=j+y;
					if (ix<0 || jy<0 || ix>=input.rows || jy>=input.cols)
						pix = 0;
					else
						pix = input.image[ix][jy];

					kpix = kernel.image[x+khx][y+khy];
					output.image[i][j] += pix && kpix;
				}
		}
}

void
convolution_sand(IMG_Char input, IMG_Char kernel, IMG_Char output)
{
	int khx, khy, mx, my;

	mx = khx = kernel.rows/2;
	my = khy = kernel.cols/2;

	if (kernel.rows & 0x1)
		mx++;
	if (kernel.cols & 0x1)
		my++;

	int i, j;
	for (i=0; i<input.rows; i++)
		for (j=0; j<input.cols; j++)
		{
			output.image[i][j] = 0;
			int x, y;
			for (x=-khx; x<mx; x++)
				for (y=-khy; y<my; y++)
				{
					char pix, kpix;

					int ix=i+x, jy=j+y;
					if (ix<0 || jy<0 || ix>=input.rows || jy>=input.cols)
						pix = 0;
					else
						pix = input.image[ix][jy];

					kpix = kernel.image[x+khx][y+khy];

					char sign = (kpix > 0) - (kpix < 0);
					output.image[i][j] += sign*(pix && kpix);
				}
		}
}