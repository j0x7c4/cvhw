#include "cvhw.h"

int* CVHW::histogram_equalize(cv::Mat& t_image)
{
	int* intensity = histogram(t_image);
	int s[256];
	double ts[256];

	for ( int k=0 ; k<256 ; k++ )
	{
		ts[k] = 0;
		for ( int j = 0 ; j<=k ; j++ )
		{
			ts[k] += (double)intensity[j];
		}
		ts[k] = 255*ts[k]/t_image.rows/t_image.cols;
		s[k] = int(ts[k]);
		
	}
	for ( int i=0 ; i<t_image.rows ; i++ )
		for ( int j=0 ; j<t_image.cols ; j++ )
			set_pix(t_image,i,j,s[get_pix(t_image,i,j)]);
	delete intensity;
	return histogram(t_image);
}