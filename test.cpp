#include <iostream>
#include "cvhw.h"

int main ( )
{
	CVHW cvhw1("C:\\Users\\Jie\\Dropbox\\lena.bmp",0);
	cv::imshow("origin",cvhw1.get_image());

	cv::Mat* image1 = cvhw1.connected_components();
	cv::imshow("connected_componetns",*image1);
	delete image1;

	cv::imshow("origin2",cvhw1.get_image());
	/*
	cv::Mat* image2 = cvhw1.binary();
	cv::imshow("binary",*image2);
	delete image2;

	cv::Mat* image3 = cvhw1.upside_down();
	cv::imshow("upsidedown",*image3);
	delete image3;
	*/
	

	//CVHW cvhw2("C:\\Users\\Jie\\Dropbox\\lena.bmp",0);
	//cvhw2.diagonally_mirrored();
	//cv::imshow("upside-down",cvhw2.get_image());
	//cv::imwrite("C:\\Users\\Jie\\Dropbox\\lena_diagonally_mirrored.bmp",cvhw2.get_image());

	//cvhw1.right_side_left();
	//cv::imshow("right-side-left",cvhw1.get_image());
	
	//cvhw1.diagonally_mirrored();
	//cv::imshow("diagonally mirrored",cvhw1.get_image());
	/*
	int* a = cvhw2.histogram();
	FILE* f = fopen("histogram.csv","w");
	for ( int i=0 ; i<256; i++ )
	{
		fprintf(f,"%d,",i);
	}
	fprintf(f,"\n");
	for ( int i=0 ; i<256 ; i++ )
	{
		fprintf(f,"%d,",a[i]);
	}
	fclose(f);
	delete a;

	//cv::imshow("binary",cvhw2.get_image());
	*/
	//cvhw1.connected_components();
	//cv::imshow("boundingbox",cvhw1.get_image());
	cv::waitKey(0);
	return 0;
}