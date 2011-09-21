#include "cvhw.h"

CVHW::CVHW(char* image_name , int flag )
{
	try
	{
		image = cv::imread(image_name,flag);
		if ( !image.data )
		{
			throw "could not open or find the image";
		}
		printf("image %s loaded\n",image_name);
		printf("rows=%d, columns=%d\n",image.rows,image.cols);
	}
	catch ( char* str )
	{
		printf("%s\n",str);
		exit(1);
	}
}


CVHW::~CVHW(){}

void CVHW::set_pix(int x, int y, int value)
{
	try
	{
		if ( x>=image.rows || y>=image.cols )
		{
			throw "wrong position!";
		}
		else
		{
			uchar* tp = image.data+x*image.cols+y;
			*tp = value;
		}
	}
	catch (char* str)
	{
		printf("%s\n",str);
	}
}

uchar CVHW::get_pix(int x, int y)
{
	try
	{
		if ( x>=image.rows || y>=image.cols )
		{
			throw "wrong position!";
		}
		else
		{
			uchar* tp = image.data+x*image.cols+y;
			return *tp;
		}
	}
	catch (char* str)
	{
		printf("%s\n",str);
	}
	return 0;
}

cv::Mat CVHW::get_image()
{
	return image;
}