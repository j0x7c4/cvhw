#include "cvhw.h"
#define P 1
#define Q 0
int CVHW::F4( int a1 , int a2, int a3, int a4 , int g, int x ) {
  return ( a1+a2+a3+a4 == 1 ? g:x );
}

void CVHW::YokoiConnectivityNumber ( const cv::Mat& image , cv::Mat& res) {
  cv::Mat t_image;
  image.copyTo(t_image);
  
  int mv[8][2] = { 0,1, -1,0, 0,-1, 1,0, 1,1,-1,1, -1,-1, 1,-1 };
  int x[9],a[4];
  int rows = t_image.rows;
  int cols = t_image.cols;
  int tr,tc;

  image.copyTo(res);
  for ( int i=0 ; i<rows ; i++ ) {
    for ( int j=0 ; j<cols ; j++ ) {
      set_pix(res,i,j,255);
    }
  }

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
      set_pix(res,i,j,F4(a[0],a[1],a[2],a[3]));
    }
  }
}

bool CVHW::ConnectedShrink ( const cv::Mat& src ,cv::Mat& data, cv::Mat& dest ) {
  cv::Mat t_image;
  src.copyTo(t_image);
  bool flag = false;
  int mv[8][2] = { 0,1, -1,0, 0,-1, 1,0, 1,1,-1,1, -1,-1, 1,-1 };
  int x[9],a[4];
  int rows = t_image.rows;
  int cols = t_image.cols;
  int tr,tc;

  for ( int i=0 ; i<rows ; i++ ) {
    for ( int j=0 ; j<cols ; j++ ) {
      if ( get_pix(data,i,j) != P ) continue;
      x[0]=255;
      for ( int k=0 ; k<8 ; k++ ) {
        tr = i+mv[k][0];
        tc = j+mv[k][1];
        if ( tr< 0 || tr>=rows || tc<0 || tc>=cols ) 
          x[k+1] = 0;
        else
          x[k+1] = get_pix(t_image,tr,tc);
      }
      a[0] = H4(x[0],x[1],x[6],x[2])==1?1:0;
      a[1] = H4(x[0],x[2],x[7],x[3])==1?1:0;
      a[2] = H4(x[0],x[3],x[8],x[4])==1?1:0;
      a[3] = H4(x[0],x[4],x[5],x[1])==1?1:0;
      int t = F4(a[0],a[1],a[2],a[3],0,255);
      if ( t == 0 ) flag = true; 
      set_pix(t_image,i,j,t);
      
    }
  }
  t_image.copyTo(dest);
  return flag;
}

void CVHW::PairRelationship ( const cv::Mat& src , cv::Mat& dest ) {
  cv::Mat t_image;
  src.copyTo(t_image);
  int mv[8][2] = { 0,1, -1,0, 0,-1, 1,0, 1,1,-1,1, -1,-1, 1,-1 };
  int x[9],a[4];
  int rows = t_image.rows;
  int cols = t_image.cols;
  int tr,tc;

  src.copyTo(dest);
  for ( int i=0 ; i<rows ; i++ ) {
    for ( int j=0 ; j<cols ; j++ ) {
      set_pix(dest,i,j,255);
    }
  }

  for ( int i=0 ; i<rows ; i++ ) {
    for ( int j=0 ; j<cols ; j++ ) {
      x[0] = get_pix(t_image,i,j);
      if ( x[0] == 255 ) continue;
      if ( x[0] == 1 ) {
        int k;
        for ( k=0 ; k<4 ; k++ ) {
          tr = i+mv[k][0];
          tc = j+mv[k][1];
          if ( tr>= 0 && tr<rows && tc>=0 && tc<cols && get_pix(t_image,tr,tc) == 1) //find a neighbour is 1
            break;
        }
        if ( k<4 ) 
        {
          set_pix(dest,i,j,P); //possibly deletable 
          continue;
        }
      }
      set_pix(dest,i,j,Q);
    }
  }
}

void CVHW::Thinning ( const cv::Mat& src , cv::Mat& dest ) {
  cv::Mat data;
  cv::Mat t_image = src.clone();
  bool flag = true;
  binary(t_image);
  while ( flag ) {
    YokoiConnectivityNumber(t_image,data);
    PairRelationship(data,data);
    flag = ConnectedShrink(t_image,data,dest);
    t_image = dest.clone();
  }
}

