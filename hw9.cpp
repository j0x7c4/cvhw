#include "cvhw.h"
void CVHW::RobertsOperator ( const cv::Mat& src, cv::Mat& dest, int threshold ) {
  int m1[2][2] = {-1,0,0,1};
  int m2[2][2] = {0,-1,1,0}; 
  int rows = src.rows;
  int cols = src.cols;
  const uchar *row_pointer, *next_row_pointer;
  uchar* temp_row_pointer;
  int r11,r12,r21,r22,r1,r2,g;
  cv::Mat temp(rows,cols,0);
  for (int r=0; r<rows ; r++ ) {
    temp_row_pointer = temp.ptr(r);
    for (int c=0; c<cols ; c++ ){
      temp_row_pointer[c]=255;
    }
  }
  for ( int r=0 ; r<rows-1 ; r++ ) {
    row_pointer = src.ptr(r);
    next_row_pointer = src.ptr(r+1);
    temp_row_pointer = temp.ptr(r);
    for ( int c=0 ; c<cols-1; c++ ) {
      r11 = row_pointer[c];
      r12 = next_row_pointer[c+1];
      r21 = row_pointer[c+1];
      r22 = next_row_pointer[c];
      r1 = m1[0][0]*r11+m1[1][1]*r12;
      r2 = m2[0][1]*r21+m2[1][0]*r22;
      g = r1*r1 + r2*r2;
      if ( g>threshold*threshold )
        temp_row_pointer[c]= 0;
    }
  }
  dest = temp;
}

void CVHW::PrewittEdgeDetector ( const cv::Mat& src, cv::Mat& dest, int threshold ) {
  int m1[3][3] = {-1,-1,-1,0,0,0,1,1,1}, m2[3][3] = {-1,0,1,-1,0,1,-1,0,1};
  int rows = src.rows;
  int cols = src.cols;
  cv::Mat temp(rows,cols,0);
  uchar* temp_row_pointer;
  int cr = 1, cc=1;
  int p1,p2,g ,tr,tc;
  for (int r=0; r<rows ; r++ ) {
    temp_row_pointer = temp.ptr(r);
    for (int c=0; c<cols ; c++ ){
      temp_row_pointer[c]=255;
    }
  }
  for ( int r = 1 ; r<rows-1 ; r++ ) {
    temp_row_pointer = temp.ptr(r);
    for ( int c=1 ; c<cols-1 ; c++ ){ 
      //calc p1 and p2;
      p1 = p2 = 0;
      for ( int i=0 ; i<3 ; i++ ) {
        int tr = i-cr + r;
        const uchar* p = src.ptr(tr);
        for ( int j=0 ; j<3 ; j++ ) {
          int tc = j-cc + c;
          p1 += m1[i][j]*p[tc];
          p2 += m2[i][j]*p[tc];
        }
      }
      g = p1*p1+p2*p2;
      if ( g>threshold*threshold ) 
        temp_row_pointer[c] = 0;
    }
  }
  dest = temp;
}
void CVHW::SobelEdgeDetector ( const cv::Mat& src, cv::Mat& dest, int threshold ){
  int m1[3][3] = {-1,-2,-1,0,0,0,1,2,1}, m2[3][3] = {-1,0,1,-2,0,2,-1,0,1};
  int rows = src.rows;
  int cols = src.cols;
  cv::Mat temp(rows,cols,0);
  const uchar *row_pointer, *next_row_pointer;
  uchar* temp_row_pointer;
  int cr = 1, cc=1;
  int s1,s2,g ,tr,tc;
  for (int r=0; r<rows ; r++ ) {
    temp_row_pointer = temp.ptr(r);
    for (int c=0; c<cols ; c++ ){
      temp_row_pointer[c]=255;
    }
  }
  for ( int r = 1 ; r<rows-1 ; r++ ) {
    temp_row_pointer = temp.ptr(r);
    for ( int c=1 ; c<cols-1 ; c++ ){ 
      //calc s1 and s2;
      s1 = s2 = 0;
      for ( int i=0 ; i<3 ; i++ ) {
        int tr = i-cr + r;
        const uchar* p = src.ptr(tr);
        for ( int j=0 ; j<3 ; j++ ) {
          int tc = j-cc + c;
          s1 += m1[i][j]*p[tc];
          s2 += m2[i][j]*p[tc];
        }
      }
      g = s1*s1+s2*s2;
      if ( g>threshold*threshold ) 
        temp_row_pointer[c] = 0;
    }
  }
  dest = temp;
}
void CVHW::FreiAndChenGradientOperator ( const cv::Mat& src, cv::Mat& dest, int threshold ){
  double m1[3][3] = {-1,-sqrt(2.0),-1,0,0,0,1,sqrt(2.0),1}, m2[3][3] = {-1,0,1,-sqrt(2.0),0,sqrt(2.0),-1,0,1};
  int rows = src.rows;
  int cols = src.cols;
  cv::Mat temp(rows,cols,0);
  const uchar *row_pointer, *next_row_pointer;
  uchar* temp_row_pointer;
  int cr = 1, cc=1,tr,tc;
  double f1,f2,g ;
  for (int r=0; r<rows ; r++ ) {
    temp_row_pointer = temp.ptr(r);
    for (int c=0; c<cols ; c++ ){
      temp_row_pointer[c]=255;
    }
  }
  for ( int r = 1 ; r<rows-1 ; r++ ) {
    temp_row_pointer = temp.ptr(r);
    for ( int c=1 ; c<cols-1 ; c++ ){ 
      //calc f1 and f2;
      f1 = f2 = 0;
      for ( int i=0 ; i<3 ; i++ ) {
        int tr = i-cr + r;
        const uchar* p = src.ptr(tr);
        for ( int j=0 ; j<3 ; j++ ) {
          int tc = j-cc + c;
          f1 += m1[i][j]*p[tc];
          f2 += m2[i][j]*p[tc];
        }
      }
      g = f1*f1+f2*f2;
      if ( g>threshold*threshold ) 
        temp_row_pointer[c] = 0;
    }
  }
  dest = temp;
}
int GetGradientManitude3 ( int r, int c , int cr, int cc, int k[][3] ,const cv::Mat& src ) {
  int g = 0;
  for ( int i=0 ; i<3 ; i++ ) {
    int tr = i-cr + r;
    const uchar* p = src.ptr(tr);
    for ( int j=0 ; j<3 ; j++ ) {
      int tc = j-cc + c;
      g += k[i][j]*p[tc];
    }
  }
  return g;
}
int GetGradientManitude5 ( int r, int c , int cr, int cc, int k[][5] ,const cv::Mat& src ) {
  int g = 0;
  for ( int i=0 ; i<5 ; i++ ) {
    int tr = i-cr + r;
    const uchar* p = src.ptr(tr);
    for ( int j=0 ; j<5 ; j++ ) {
      int tc = j-cc + c;
      g += k[i][j]*p[tc];
    }
  }
  return g;
}
void CVHW::KirschCompassOperator ( const cv::Mat& src, cv::Mat& dest, int threshold ){
  int k0[3][3] = {-3,-3,5,-3,0,5,-3,-3,5}, k1[3][3] = {-3,5,5,-3,0,5,-3,-3,-3}, k2[3][3] = {5,5,5,-3,0,-3,-3,-3,-3},\
   k3[3][3] = {5,5,-3,5,0,-3,-3,-3,-3}, k4[3][3] = {5,-3,-3,5,0,-3,5,-3,-3}, k5[3][3] = {-3,-3,-3,5,0,-3,5,5,-3},\
   k6[3][3] = {-3,-3,-3,-3,0,-3,5,5,5}, k7[3][3] = {-3,-3,-3,-3,0,5,-3,5,5};
  int rows = src.rows;
  int cols = src.cols;
  cv::Mat temp(rows,cols,0);
  const uchar *row_pointer, *next_row_pointer;
  uchar* temp_row_pointer;
  int cr = 1, cc=1;
  int g ,tr,tc,tg;
  for (int r=0; r<rows ; r++ ) {
    temp_row_pointer = temp.ptr(r);
    for (int c=0; c<cols ; c++ )temp_row_pointer[c]=255;
  }
  for ( int r = 1 ; r<rows-1 ; r++ ) {
    temp_row_pointer = temp.ptr(r);
    for ( int c=1 ; c<cols-1 ; c++ ){ 
      g = MININT;
      tg = GetGradientManitude3(r,c,cr,cc,k0,src); if ( tg>g ) g=tg;
      tg = GetGradientManitude3(r,c,cr,cc,k1,src); if ( tg>g ) g=tg;
      tg = GetGradientManitude3(r,c,cr,cc,k2,src); if ( tg>g ) g=tg;
      tg = GetGradientManitude3(r,c,cr,cc,k3,src); if ( tg>g ) g=tg;
      tg = GetGradientManitude3(r,c,cr,cc,k4,src); if ( tg>g ) g=tg;
      tg = GetGradientManitude3(r,c,cr,cc,k5,src); if ( tg>g ) g=tg;
      tg = GetGradientManitude3(r,c,cr,cc,k6,src); if ( tg>g ) g=tg;
      tg = GetGradientManitude3(r,c,cr,cc,k7,src); if ( tg>g ) g=tg;
      if ( g>threshold ) temp_row_pointer[c] = 0;
    }
  }
  dest = temp;
}
void CVHW::RobinsonCompassOperator ( const cv::Mat& src, cv::Mat& dest, int threshold ){
  int r0[3][3] = {-1,0,1,-2,0,2,-1,0,1}, r1[3][3] = {0,1,2,-1,0,1,-2,-1,0}, r2[3][3] = {1,2,1,0,0,0,-1,-2,-1},\
   r3[3][3] = {2,1,0,1,0,-1,0,-1,-2}, r4[3][3] = {1,0,-1,2,0,-2,1,0,-1}, r5[3][3] = {0,-1,-2,1,0,-1,2,1,0},\
   r6[3][3] = {-1,-2,-1,0,0,0,1,2,1}, r7[3][3] = {-2,-1,0,-1,0,1,0,1,2};
  int rows = src.rows;
  int cols = src.cols;
  cv::Mat temp(rows,cols,0);
  const uchar *row_pointer, *next_row_pointer;
  uchar* temp_row_pointer;
  int cr = 1, cc=1;
  int g ,tr,tc,tg;
  for (int r=0; r<rows ; r++ ) {
    temp_row_pointer = temp.ptr(r);
    for (int c=0; c<cols ; c++ )temp_row_pointer[c]=255;
  }
  for ( int r = 1 ; r<rows-1 ; r++ ) {
    row_pointer = src.ptr(r);
    temp_row_pointer = temp.ptr(r);
    for ( int c=1 ; c<cols-1 ; c++ ){ 
      g = MININT;
      tg = GetGradientManitude3(r,c,cr,cc,r0,src); if ( tg>g ) g=tg;
      tg = GetGradientManitude3(r,c,cr,cc,r1,src); if ( tg>g ) g=tg;
      tg = GetGradientManitude3(r,c,cr,cc,r2,src); if ( tg>g ) g=tg;
      tg = GetGradientManitude3(r,c,cr,cc,r3,src); if ( tg>g ) g=tg;
      if ( g>threshold ) temp_row_pointer[c] = 0;
    }
  }
  dest = temp;
}
void CVHW::NevatiaBabuOperator ( const cv::Mat& src, cv::Mat& dest, int threshold ){
  int r0[5][5] = {100,100,100,100,100,100,100,100,100,100,0,0,0,0,0,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100}, \
      r1[5][5] = {100,100,100,100,100,100,100,100,78,-32,100,92,0,-92,-100,32,-78,-100,-100,-100,-100,-100,-100,-100,-100},\
      r2[5][5] = {100,100,100,32,-100,100,100,92,-78,-100,100,100,0,-100,-100,100,78,-92,-100,-100,100,-32,-100,-100,-100},\
      r3[5][5] = {-100,-100,0,100,100,-100,-100,0,100,100,-100,-100,0,100,100,-100,-100,0,100,100,-100,-100,0,100,100},\
      r4[5][5] = {-100,32,100,100,100,-100,-78,92,100,100,-100,-100,0,100,100,-100,-100,-92,78,100,-100,-100,-100,-32,100},\
      r5[5][5] = {100,100,100,100,100,-32,78,100,100,100,-100,-92,0,92,100,-100,-100,-100,-78,32,-100,-100,-100,-100,-100};
  int rows = src.rows;
  int cols = src.cols;
  cv::Mat temp(rows,cols,0);
  uchar* temp_row_pointer;
  int cr = 1, cc=1;
  int g ,tr,tc,tg;
  for (int r=0; r<rows ; r++ ) {
    temp_row_pointer = temp.ptr(r);
    for (int c=0; c<cols ; c++ )temp_row_pointer[c]=255;
  }
  for ( int r = 2 ; r<rows-2 ; r++ ) {
    temp_row_pointer = temp.ptr(r);
    for ( int c=2 ; c<cols-2 ; c++ ){ 
      g = MININT;
      tg = GetGradientManitude5(r,c,2,2,r0,src); if ( tg>g ) g=tg;
      tg = GetGradientManitude5(r,c,2,2,r1,src); if ( tg>g ) g=tg;
      tg = GetGradientManitude5(r,c,2,2,r2,src); if ( tg>g ) g=tg;
      tg = GetGradientManitude5(r,c,2,2,r3,src); if ( tg>g ) g=tg;
      tg = GetGradientManitude5(r,c,2,2,r4,src); if ( tg>g ) g=tg;
      tg = GetGradientManitude5(r,c,2,2,r5,src); if ( tg>g ) g=tg;
      if ( g>threshold ) temp_row_pointer[c] = 0;
    }
  }
  dest = temp;
}