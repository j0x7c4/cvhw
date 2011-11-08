#include "cvhw.h"
#include <math.h>
//int kernal1_num = 20;
int kernel1[21][2] = { 0,0, -1,0, -1,1, 0,1, 1,1, 1,0, 1,-1, 0,-1, -1,-1,
                      -2,0, -2,1, -1,2, 0,2, 1,2, 2,1, 2,0, 2,-1, 1,-2, 0,-2, -1,-2, -2,-1};
void CVHW::init() {
  //initilize kernals;
  Kernel kernel;
  kernel.num = 21;
  for ( int i=0 ; i<21 ; i++ ) 
    kernel.neighbour.push_back(Point(kernel1[i][0],kernel1[i][1]));
  Kernels.push_back(kernel);
  //second;
  kernel.num = 3;
  kernel.neighbour.clear();
  kernel.neighbour.push_back(Point(0,0));
  kernel.neighbour.push_back(Point(1,0));
  kernel.neighbour.push_back(Point(0,-1));
  Kernels.push_back(kernel);
  //third;
  kernel.num=3;
  kernel.neighbour.clear();
  kernel.neighbour.push_back(Point(-1,0));
  kernel.neighbour.push_back(Point(-1,1));
  kernel.neighbour.push_back(Point(0,1));
  Kernels.push_back(kernel);
}
Kernel CVHW::GetKernel(int idx) {
  return Kernels[idx];
}
CVHW::CVHW(char* image_name , int flag )
{
	try
	{
		origin_image = cv::imread(image_name,flag);
		if ( !origin_image.data )
		{
			throw "could not open or find the image";
		}
		printf("image %s loaded\n",image_name);
		printf("rows=%d, columns=%d\n",origin_image.rows,origin_image.cols);
	}
	catch ( char* str )
	{
		printf("%s\n",str);
		exit(1);
	}
}


CVHW::~CVHW()
{
	delete row_start;
	delete row_end;
	delete row;
	delete start_col;
	delete end_col;
	delete perm_label;
	delete label;
	delete next;
	delete eq_class;
}

void CVHW::set_pix(cv::Mat& image, int x, int y, int value)
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

uchar CVHW::get_pix(cv::Mat& image, int x, int y)
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
	return origin_image;
}