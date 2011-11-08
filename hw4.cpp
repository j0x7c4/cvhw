#include "cvhw.h"

using namespace std;

void CVHW::BinaryDilation(cv::Mat& image,Kernel kernel) {
  int tx,ty,k;
  cv::Mat res(image.size(),CV_8U);
  //initilize
  for (int i=0 ; i<res.rows ; i++) 
    for (int j=0 ; j<res.rows; j++ ) 
      set_pix(res,i,j,0);
  for ( int i=0 ; i<image.rows ; i++ )
    for ( int j=0 ; j<image.cols; j++ ) {
      if ( get_pix(image,i,j) == 255 ) {
        for ( k = 0 ; k < kernel.num ; k++ ) {
          tx = i+kernel.neighbour[k].x;
          ty = j+kernel.neighbour[k].y;
          if ( tx<0 || tx>=res.rows || ty<0 || ty>=res.cols ) {
            set_pix(res,i,j,255);// edge
            break;
          }
        }
        if ( k<kernel.num ) continue;
        for ( int k = 0 ; k < kernel.num ; k++ ) {
          tx = i+kernel.neighbour[k].x;
          ty = j+kernel.neighbour[k].y;
          set_pix(res,tx,ty,255);
        }
      }
    }
  image = res;
}

void CVHW::BinaryErosion(cv::Mat& image,Kernel kernel) {
  int tx,ty;
  int k;
  cv::Mat res(image.size(),CV_8U);
  //initilize
  for (int i=0 ; i<res.rows ; i++) 
    for (int j=0 ; j<res.rows; j++ ) 
      set_pix(res,i,j,0);
  for ( int i=0 ; i<image.rows ; i++ )
    for ( int j=0 ; j<image.cols; j++ ) {      
      for ( k = 0 ; k < kernel.num ; k++ ) {
        tx = i+kernel.neighbour[k].x;
        ty = j+kernel.neighbour[k].y;
        if ( tx<0 || tx>=res.rows || ty<0 || ty>=res.cols ) {
          set_pix(res,i,j,255); //edge
          break;
        }
        if ( get_pix(image,tx,ty)!=255 )
          break;
      }
      if ( k==kernel.num ) {
        set_pix(res,i,j,255);
      }
    }
  image = res;
}

void CVHW::BinaryOpening(cv::Mat& image,Kernel kernel) {
  BinaryErosion(image,kernel);
  BinaryDilation(image,kernel);
}

void CVHW::BinaryClosing(cv::Mat& image,Kernel kernel) {
  BinaryDilation(image,kernel);
  BinaryErosion(image,kernel);
}

void CVHW::BinaryHitAndMiss(cv::Mat& image,Kernel kernel_j, Kernel kernel_k) {
  int tx,ty,k;
  cv::Mat a = image.clone();
  cv::Mat ac = image.clone();
  cv::Mat res(image.size(),CV_8U);
  //inverse
  for ( int i=0 ; i<ac.rows ; i++) 
    for ( int j=0 ; j<ac.cols ; j++ ){
      set_pix(ac,i,j,255-get_pix(ac,i,j));
    }
  //A-J
  BinaryErosion(a,kernel_j);
  //AC-K
  BinaryErosion(ac,kernel_k);
  for ( int i=0 ; i<res.rows;  i++) 
    for ( int j=0 ; j<res.cols; j++ ) {
      int t1 = get_pix(a,i,j);
      int t2 = get_pix(ac,i,j);
      if ( t1==255 && t2==255 )
        set_pix(res,i,j,255);
      else
        set_pix(res,i,j,0);
    }
  image = res;
}