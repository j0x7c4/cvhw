#include "cvhw.h"
int mv[8][2] = { 0,1,-1,0,0,-1,1,0,1,1,-1,1,-1,-1,1,-1 };
void CVHW::AddGaussianNoise ( const cv::Mat& src, cv::Mat& dest, int amp ) {
  cv::Mat temp = src.clone();
  int rows = temp.rows;
  int cols = temp.cols;
  cv::RNG rng;
  for ( int i = 0 ; i<rows ; i++ ) {
    uchar* row_pointer = temp.ptr(i);
    for ( int j=0 ; j<cols ; j++ ) {
      double rnd = rng.gaussian(1);
      int v = (int)row_pointer[j]+amp*rnd;
      row_pointer[j] = v;
    }
  }
  dest = temp;
}
void CVHW::AddSaltAndPepperNoise ( const cv::Mat& src, cv::Mat& dest, double threshold ){
  cv::Mat temp = src.clone();
  int rows = temp.rows;
  int cols = temp.cols;
  cv::RNG rng;
  for ( int i = 0 ; i<rows ; i++ ) {
    uchar* row_pointer = temp.ptr(i);
    for ( int j=0 ; j<cols ; j++ ) {
      double rnd = rng.uniform((double)0,(double)1);
      if ( rnd<threshold ) {
        row_pointer[j]=0;
      }
      else if ( rnd > 1-threshold ) {
        row_pointer[j]=255;
      }
    }
  }
  dest = temp;
}
void CVHW::BoxFilter ( const cv::Mat& src, cv::Mat& dest , int mask_size, const vector<vector<int>>& mask ){
  cv::Mat temp = src.clone();
  int sum = 0;
  for ( int i=0 ; i<mask_size ; i++ ) {
    for ( int j=0 ;j<mask_size; j++ ) {
      sum+=mask[i][j];
    }
  }
  int rows = temp.rows;
  int cols = temp.cols;
  int tr,tc;
  for ( int r = 0 ; r<rows ; r++ ) {
    uchar* row_pointer = temp.ptr(r);
    for ( int c=0 ; c<cols ; c++ ) {
      double t = 0;
      for ( int i=0 ; i<mask_size ; i++ ) {
        int offset_r = mask_size/2-i;
        tr = offset_r + r;//find the neighbour in image
        if ( tr<0 || tr>=rows ) continue;
        uchar* mask_row_pointer =temp.ptr(tr);
        for ( int j=0; j<mask_size ; j++ ) { 
          int offset_c = mask_size/2-j;
          tc = offset_c + c;
          if ( tc>=0 && tc<cols ) {
            t+=(double)mask[i][j]/(double)sum * (int)mask_row_pointer[tc];
          }
        }
      }
      row_pointer[c] = (uchar)t;
    }
  }
  dest = temp;
}
void CVHW::MedianFilter ( const cv::Mat &src, cv::Mat& dest, int mask_size , const vector<vector<int>>& mask){
  cv::Mat temp = src.clone();
  dest = temp.clone();
  int rows = temp.rows;
  int cols = temp.cols;
  int tr,tc;
  for ( int r = 0 ; r<rows ; r++ ) {
    uchar* row_pointer = dest.ptr(r);
    for ( int c=0 ; c<cols ; c++ ) {
      vector<int> neighbours;
      for ( int i=0 ; i<mask_size ; i++ ) {
        tr = mask_size/2-i+r;
        if ( tr<0 || tr>=rows ) continue;
        uchar* mask_row_pointer = temp.ptr(tr);
        for ( int j=0; j<mask_size ; j++ ) {
          tc = mask_size/2-j+c;
          if ( tc>=0 && tc<cols ) {
            neighbours.push_back((int)mask_row_pointer[tc]); //find neighbours
          }
        }
      }
      sort(neighbours.begin(),neighbours.end());
      row_pointer[c] = neighbours[neighbours.size()/2];
    }
  }
}
void CVHW::OpeningAndClosing ( const cv::Mat & src, cv::Mat& dest, Kernel kernel){
  cv::Mat temp = src.clone();
  GrayScaleOpening(temp,kernel);
  GrayScaleClosing(temp,kernel);
  dest = temp;
}
void CVHW::ClosingAndOpening ( const cv::Mat & src, cv::Mat& dest, Kernel kernel ){
  cv::Mat temp = src.clone();
  GrayScaleClosing(temp,kernel);
  GrayScaleOpening(temp,kernel);
  dest = temp;
}