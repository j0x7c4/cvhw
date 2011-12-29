#include <iostream>
#include "cvhw.h"
using namespace cv;
int main ( )
{
	CVHW cvhw("C:\\Users\\Jie\\Dropbox\\lena.bmp",CV_8U);
  Mat image = cvhw.get_image().clone();
  Mat res;
  cvhw.RobertsOperator(image,res,12);
  imwrite("C:\\Users\\Jie\\Documents\\CVHW\\hw9\\RobertsOperator_12.bmp",res);
  cvhw.PrewittEdgeDetector(image,res,24);
  imwrite("C:\\Users\\Jie\\Documents\\CVHW\\hw9\\PrewittEdgeDetector_24.bmp",res);
  cvhw.SobelEdgeDetector(image,res,38);
  imwrite("C:\\Users\\Jie\\Documents\\CVHW\\hw9\\SobelEdgeDetector_38.bmp",res);
  cvhw.FreiAndChenGradientOperator(image,res,30);
  imwrite("C:\\Users\\Jie\\Documents\\CVHW\\hw9\\FreiAndChenGradientOperator_30.bmp",res);
  cvhw.KirschCompassOperator(image,res,135);
  imwrite("C:\\Users\\Jie\\Documents\\CVHW\\hw9\\KirschCompassOperator_135.bmp",res);
  cvhw.RobinsonCompassOperator(image,res,43);
  imwrite("C:\\Users\\Jie\\Documents\\CVHW\\hw9\\RobinsonCompassOperator_43.bmp",res);
  cvhw.NevatiaBabuOperator(image,res,12500);
  imwrite("C:\\Users\\Jie\\Documents\\CVHW\\hw9\\NevatiaBabuOperator_12500.bmp",res);
  imshow("res",res);
  waitKey(0);
	return 0;
}