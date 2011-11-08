#include <iostream>
#include "cvhw.h"

int main ( )
{
	CVHW cvhw("C:\\Users\\Jie\\Dropbox\\lena.bmp",CV_8U);
  cvhw.init();
	cv::imshow("origin",cvhw.get_image());

	cv::Mat image = cvhw.get_image().clone();
  cvhw.binary(image);
  //cv::imshow("binary",image);
  //cvhw.BinaryDilation(image,cvhw.GetKernel(0));
  cvhw.BinaryErosion(image,cvhw.GetKernel(0));
  //cvhw.BinaryHitAndMiss(image,cvhw.GetKernel(1),cvhw.GetKernel(2));
  //cvhw.BinaryClosing(image,cvhw.GetKernel(0));
  cv::imshow("res",image);
  //cv::imwrite("C:\\Users\\Jie\\Dropbox\\lena_binary_dilation.bmp",image);
	cv::waitKey(0);
	return 0;
}