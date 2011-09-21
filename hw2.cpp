#include "cvhw.h"

//a binary image (threshold at 128)
void CVHW::binary(int threshold)
{
	int m = image.rows;
	int n = image.cols;
	//int a,b;
	//a=b=0;
	printf("binary\n");
	printf("Threshold is %d\n",threshold);
	for ( int i = 0 ; i<m ; i++ )
	{
		for ( int j = 0 ; j<n ; j++ )
		{
			//printf("%d ",get_pix(i,j));
			if ( get_pix(i,j)>=threshold )
			{
				//a++;
				set_pix(i,j,255);
			}
			else
			{
				//b++;
				set_pix(i,j,0);
			}
		}
	}
	//printf("%d,%d\n",a,b);
}