#include<core\core.hpp>
#include<highgui\highgui.hpp>
#include<vector>
#include<set>
#include<map>
using namespace std;
//color define
#define GRAY 128

typedef struct bounding_box
{
	int sum_pixel;
	int top_left_x, top_left_y;
	int bottom_right_x, bottom_right_y;
	int centroid_x, centroid_y;
	bounding_box()
	{
		sum_pixel=0;
		top_left_x = top_left_y = bottom_right_x = bottom_right_y = -1; //null
	}
}BOUNDING_BOX;

typedef struct point {
  int x,y;
  point(int x_, int y_) {
    x=x_, y=y_;
  }
}Point;

typedef struct kernel {
  int num;
  vector<Point> neighbour;
}Kernel;


class CVHW
{
	cv::Mat origin_image;
	void set_pix ( cv::Mat&, int , int , int  );
	uchar get_pix ( cv::Mat&, int , int );
	void mark_centroid(cv::Mat&,int,int,int);
	//run-length algorithm varibles
	int runs;
	int* row_start;
	int* row_end;
	int* row;
	int* start_col;
	int* end_col;
	int* perm_label;
	int* label;
	int* next;
	int* eq_class;

	void count_run(cv::Mat);
	void initialize_run_table( cv::Mat );
	void make_equivalent(int , int);
	void initialize_equiv();
	void run_length(cv::Mat&, int);

	void classic_connected_components( );
  vector<Kernel> Kernels;
public:
	
	CVHW(char*,int flag=0);
	~CVHW();
  void init();
  Kernel GetKernel(int);
	cv::Mat get_image();
	void save_work(char*);
	//homework 1
	void upside_down( cv::Mat& );
	void right_side_left(cv::Mat&);
	void diagonally_mirrored(cv::Mat&);
	//homework 2
	void binary(cv::Mat&,int threshold=128);
	int* histogram(cv::Mat&);
	void connected_components(cv::Mat& , int threshold=500, int flag = 4 );
	void draw_connected_components ( cv::Mat&, BOUNDING_BOX& );
	//homework 3
  int* histogram_equalize(cv::Mat&);
  //homework 4
  void BinaryDilation(cv::Mat&,Kernel);
  void BinaryErosion(cv::Mat&,Kernel);
  void BinaryOpening(cv::Mat&,Kernel);
  void BinaryClosing(cv::Mat&,Kernel);
  void BinaryHitAndMiss(cv::Mat&,Kernel,Kernel);
};



