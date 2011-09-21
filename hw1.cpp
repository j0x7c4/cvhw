#include "cvhw.h"
//swap image[i][j] image[m-1-i][j]
void CVHW::upside_down()
{
	int m = image.rows;
	int n = image.cols;

	printf("doing upside down\n");

	for ( int i=0; i <m/2 ; i++ )
	{
		for ( int j=0 ; j<n ; j++ )
		{
			uchar t = get_pix(m-1-i,j);
			set_pix(m-1-i,j,get_pix(i,j));
			set_pix(i,j,t);
		}
	}
}
//swap image[i][j] image[i][n-1-j]
void CVHW::right_side_left()
{
	int m = image.rows;
	int n = image.cols;

	printf("doing right-side-left\n");

	for ( int i=0 ; i<m ; i++ )
	{
		for ( int j=0 ; j<n/2 ; j++ )
		{
			uchar t = get_pix(i,n-1-j);
			set_pix(i,n-1-j,get_pix(i,j));
			set_pix(i,j,t);
		}
	}
}

//swap image[i][j] image[j][i]
void CVHW::diagonally_mirrored()
{
	int m = image.rows;
	int n = image.cols;

	printf("doing diagonally mirrored\n");

	for ( int i=0 ; i<m ; i++ )
	{
		for ( int j=i ; j<n ; j++ )
		{
			uchar t = get_pix(j,i);
			set_pix(j,i,get_pix(i,j));
			set_pix(i,j,t);
		}
	}
}