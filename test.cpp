#include <iostream>
#include "cvhw.h"

int main ( )
{
	CVHW cvhw2("E:\\source\\CVHW\\lena.bmp",0);
	cv::imshow("origin",cvhw2.get_image());

	//cvhw1.upside_down();
	//cv::imshow("upside-down",cvhw1.get_image());


	//cvhw1.right_side_left();
	//cv::imshow("right-side-left",cvhw1.get_image());
	
	//cvhw1.diagonally_mirrored();
	//cv::imshow("diagonally mirrored",cvhw1.get_image());

	cvhw2.histogram();
	//cv::imshow("binary",cvhw2.get_image());

	cv::waitKey(0);
	return 0;
}