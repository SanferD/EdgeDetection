#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <stdlib.h>

#include "io.h"

void
allocate_image_char(IMG_Char *img, int rows, int cols)
{
	img->rows = rows;
	img->cols = cols;

	img->image = (char **) malloc(sizeof(char*)*rows);
	for (int i=0; i!=rows; i++)
		img->image[i] = (char*) malloc(sizeof(char)*cols);
}

void
allocate_image_float(IMG_Float *img, int rows, int cols)
{
	img->rows = rows;
	img->cols = cols;

	img->image = (float **) malloc(sizeof(float*)*rows);
	for (int i=0; i!=rows; i++)
		img->image[i] = (float*) malloc(sizeof(float)*cols);		
}

void
free_image_char(IMG_Char *img)
{
	for (int i=0; i!=img->rows; free(img->image[i++]));
	free(img->image);
}

void
free_image_float(IMG_Float *img)
{
	for (int i=0; i!=img->rows; free(img->image[i++]));
	free(img->image);
}

void
read_image_char(char *fn, IMG_Char *img)
{
	cv::Mat mat = cv::imread(fn, CV_LOAD_IMAGE_GRAYSCALE);
	if (mat.empty())
	{
		char err[500];
		scanf("\'%s\'", fn);
		perror(err);
		exit(1);
	}

	allocate_image_char(img, mat.rows, mat.cols);

	int i, j;
	for (i=0; i!=img->rows; i++)
		for (j=0; j!=img->cols; j++)
			img->image[i][j] = mat.at<uchar>(i,j);
}

void
write_image_char(char *fn, IMG_Char img)
{
	cv::Mat mat(img.rows, img.cols, CV_8UC1);

	int i, j;
	for (i=0; i!=img.rows; i++)
		for (j=0; j!=img.cols; j++)
			mat.at<uchar>(i,j) = img.image[i][j];

	cv::imwrite(fn, mat); 	
}

void
write_image_float(char *fn, IMG_Float img)
{
	cv::Mat mat(img.rows, img.cols, CV_32FC1);

	int i, j;
	for (i=0; i!=img.rows; i++)
		for (j=0; j!=img.cols; j++)
			mat.at<float>(i,j) = img.image[i][j];

	cv::imwrite(fn, mat); 	
}


void
display_image_char(const char *wn, IMG_Char img)
{
	cv::Mat image = cv::Mat(img.rows, img.cols, CV_8UC1);
	for (int i=0; i!=image.rows; i++)
		for (int j=0; j!=image.cols; j++)
			image.at<uchar>(i,j) = img.image[i][j];

	cv::namedWindow(wn, 0);
	cv::moveWindow(wn, 800, 500);
	cv::imshow(wn, image);

	while (cv::waitKey(33) != 'n');

	cv::destroyWindow(wn);
}

void
display_image_float(const char *wn, IMG_Float img)
{
	cv::Mat image = cv::Mat(img.rows, img.cols, CV_32FC1);
	for (int i=0; i!=image.rows; i++)
		for (int j=0; j!=image.cols; j++)
			image.at<float>(i,j) = img.image[i][j];

	cv::namedWindow(wn, 0);
	cv::imshow(wn, image);

	while (cv::waitKey(33) != 'n');

	cv::destroyWindow(wn);	
}


