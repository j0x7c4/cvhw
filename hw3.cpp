#include "cvhw.h"

int* CVHW::histogram_equalize(cv::Mat& t_image)
{
	int* intensity = histogram(t_image);
	int s[256];
	for ( int k=0 ; k<256 ; k++ )
	{
		s[k] = 0;
		for ( int j = 0 ; j<=k ; j++ )
		{
			s[k] += intensity[j];
		}
		
		s[k] = int(((double)s[k]/t_image.cols/t_image.rows)*255.0);
		
	}
	for ( int i=0 ; i<t_image.rows ; i++ )
		for ( int j=0 ; j<t_image.cols ; j++ )
			set_pix(t_image,i,j,s[get_pix(t_image,i,j)]);
	delete intensity;
	return histogram(t_image);
}