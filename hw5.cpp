#include "cvhw.h"

void CVHW::GrayScaleDilation(cv::Mat& image,Kernel kernel){
  uchar max_intensity;
  int tx,ty,k;
  cv::Mat res(image.size(),CV_8U);
  for ( int i=0 ; i<image.rows ; i++ )
    for ( int j=0 ; j<image.cols; j++ ) {
      max_intensity=get_pix(image,i,j);
      for ( k = 0 ; k < kernel.num ; k++ ) {
        tx = i+kernel.neighbour[k].x;
        ty = j+kernel.neighbour[k].y;
        if ( tx>=0 && tx<res.rows && ty>=0 && ty<res.cols ) {
          max_intensity = max(max_intensity,get_pix(image,tx,ty));
        }
      }
      set_pix(res,i,j,max_intensity);
    }
  image = res;
}
void CVHW::GrayScaleErosion(cv::Mat& image,Kernel kernel) {
  uchar min_intensity;
  int tx,ty,k;
  cv::Mat res(image.size(),CV_8U);
  for ( int i=0 ; i<image.rows ; i++ )
    for ( int j=0 ; j<image.cols; j++ ) {
      min_intensity=get_pix(image,i,j);
      for ( k = 0 ; k < kernel.num ; k++ ) {
        tx = i+kernel.neighbour[k].x;
        ty = j+kernel.neighbour[k].y;
        if ( tx>=0 && tx<res.rows && ty>=0 && ty<res.cols ) {
          min_intensity = min(min_intensity,get_pix(image,tx,ty));
        }
      }
      set_pix(res,i,j,min_intensity);
    }
  image = res;
}
void CVHW::GrayScaleOpening(cv::Mat& image,Kernel kernel) {
  GrayScaleErosion(image,kernel);
  GrayScaleDilation(image,kernel);
}
void CVHW::GrayScaleClosing(cv::Mat& image,Kernel kernel) {
  GrayScaleDilation(image,kernel);
  GrayScaleErosion(image,kernel);
}