#include <iostream>
#include "cvhw.h"

int main ( )
{
	CVHW cvhw("C:\\Users\\Jie\\Dropbox\\lena.bmp",CV_8U);
  cvhw.init();
	cv::imshow("origin",cvhw.get_image());

	cv::Mat image = cvhw.get_image().clone();
  //cvhw.binary(image);
  //cv::imshow("binary",image);
  //cvhw.GrayScaleDilation(image,cvhw.GetKernel(0));
  //cvhw.GrayScaleErosion(image,cvhw.GetKernel(0));
  //cvhw.GrayScaleOpening(image,cvhw.GetKernel(0));
  cvhw.GrayScaleClosing(image,cvhw.GetKernel(0));
  cv::imshow("res",image);
  cv::imwrite("C:\\Users\\Jie\\Dropbox\\lena_grayscale_closing.bmp",image);
	cv::waitKey(0);
	return 0;
}