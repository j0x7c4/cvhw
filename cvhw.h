#include<core\core.hpp>
#include<highgui\highgui.hpp>

class CVHW
{
	cv::Mat image;
	void set_pix ( int , int , int  );
	uchar get_pix ( int , int );
public:

	CVHW(char*,int);
	~CVHW();
	cv::Mat get_image();
	//homework 1
	void upside_down();
	void right_side_left();
	void diagonally_mirrored();
};