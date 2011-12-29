#include "cvhw.h"
#define Q 1
#define R 0
#define S 2
void CVHW::DownSample( cv::Mat& source, int rows, int cols ) {
  cv::Mat res(rows,cols,source.type());
  int row_scale = source.rows/rows;
  int col_scale = source.cols/cols;
  for ( int i = 0 ; i<rows ; i++ ) {
    for ( int j=0 ; j<cols ; j++ ) {
      set_pix(res,i,j,get_pix(source,i*row_scale,j*col_scale));
    }
  }
  source = res;
}

int CVHW::H4(int b,int c, int d, int e) {
  if ( b==c && ( d!=b || e!=b ) ) return Q;
  if ( b==c && d==b && e==b ) return R;
  if ( b!=c ) return S;
  return -1;
}

int CVHW::F4(int a1, int a2, int a3, int a4) {
  if ( a1 == a2 && a1 == a3 && a1==a4 && a1==R ) return 5;
  int n=0;
  if ( a1 == Q ) n++;
  if ( a2 == Q ) n++;
  if ( a3 == Q ) n++;
  if ( a4 == Q ) n++;
  return n;
}

void CVHW::YokoiConnectivityNumber ( const cv::Mat& image , vector<string>& res) {
  cv::Mat t_image;
  image.copyTo(t_image);
  binary(t_image);
  int mv[8][2] = { 0,1, -1,0, 0,-1, 1,0, 1,1,-1,1, -1,-1, 1,-1 };
  int x[9],a[4];
  int rows = t_image.rows;
  int cols = t_image.cols;
  int tr,tc;

  res.resize(rows,string(cols,' '));

  for ( int i=0 ; i<rows ; i++ ) {
    for ( int j=0 ; j<cols ; j++ ) {
      x[0] = get_pix(t_image,i,j)/255;
      if ( x[0] == 0 ) continue;
      for ( int k=0 ; k<8 ; k++ ) {
        tr = i+mv[k][0];
        tc = j+mv[k][1];
        if ( tr< 0 || tr>=rows || tc<0 || tc>=cols ) 
          x[k+1] = 0;
        else
          x[k+1] = get_pix(t_image,tr,tc)/255;
      }
      a[0] = H4(x[0],x[1],x[6],x[2]);
      a[1] = H4(x[0],x[2],x[7],x[3]);
      a[2] = H4(x[0],x[3],x[8],x[4]);
      a[3] = H4(x[0],x[4],x[5],x[1]);
      res[i][j] = F4(a[0],a[1],a[2],a[3])+'0';
    }
  }
}