#include<core\core.hpp>
#include<highgui\highgui.hpp>
#include<vector>
#include<set>
#include<map>
class CVHW
{
	cv::Mat image;
	
	void set_pix ( int , int , int  );
	uchar get_pix ( int , int );

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

	void count_run();
	void initialize_run_table( );
	void make_equivalent(int , int);
	void initialize_equiv();
	void run_length();

	void classic_connected_components( );
public:
	
	CVHW(char*,int flag=0);
	~CVHW();
	cv::Mat get_image();
	void save_work(char*);
	//homework 1
	void upside_down();
	void right_side_left();
	void diagonally_mirrored();
	//homework 2
	void binary(int threshold=128);
	int* histogram();
	void connected_components(int threshold=500);
	void make_bounding_box ();
};

struct bounding_box
{
	int top_left_x, top_left_y;
	int width, height;
	int centroid_x, centroid_y;
};