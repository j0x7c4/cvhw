#include "cvhw.h"
//swap image[i][j] image[m-1-i][j]
void CVHW::upside_down(cv::Mat& t_image)
{
	//cv::Mat* t_image = new cv::Mat(origin_image);
	int m = t_image.rows;
	int n = t_image.cols;

	printf("doing upside down\n");

	for ( int i=0; i <m/2 ; i++ )
	{
		for ( int j=0 ; j<n ; j++ )
		{
			uchar t = get_pix(t_image,m-1-i,j);
			set_pix(t_image,m-1-i,j,get_pix(t_image,i,j));
			set_pix(t_image,i,j,t);
		}
	}
}
//swap image[i][j] image[i][n-1-j]
void CVHW::right_side_left(cv::Mat& t_image)
{
	//cv::Mat* t_image = new cv::Mat(origin_image);
	int m = t_image.rows;
	int n = t_image.cols;

	printf("doing right-side-left\n");

	for ( int i=0 ; i<m ; i++ )
	{
		for ( int j=0 ; j<n/2 ; j++ )
		{
			uchar t = get_pix(t_image,i,n-1-j);
			set_pix(t_image,i,n-1-j,get_pix(t_image,i,j));
			set_pix(t_image,i,j,t);
		}
	}
}

//swap image[i][j] image[j][i]
void CVHW::diagonally_mirrored(cv::Mat& t_image)
{
	//cv::Mat* t_image = new cv::Mat(origin_image);
	int m = t_image.rows;
	int n = t_image.cols;

	printf("doing diagonally mirrored\n");

	for ( int i=0 ; i<m ; i++ )
	{
		for ( int j=i ; j<n ; j++ )
		{
			uchar t = get_pix(t_image,j,i);
			set_pix(t_image,j,i,get_pix(t_image,i,j));
			set_pix(t_image,i,j,t);
		}
	}
}