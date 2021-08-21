/****************
* OPENCV DEMO   *
* Xiaohu Zheng  *
* 8/10/2021     *
*****************/
#include "OpencvDemo.h"

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
	Mat img = imread("D:/Visual Studio/OpenCV/Images/2.jpg");
	if (img.empty())
	{
		cout << "Cannot load image..." << endl;
		return -1;
	}
	namedWindow("Original Image", WINDOW_AUTOSIZE);
	imshow("Original Image", img);

	OpencvDemo demo;
	//demo.colorSpace(img);
	//demo.mat_creation(img);
	//demo.pixel_visited(img);
	//demo.image_arithmetics(img);
	//demo.track_bar(img);
	//demo.key_response(img);
	//demo.color_map(img);
	//demo.bitwise_operation();
	//demo.split_merge(img);
	//demo.colorSpaceUse(img);
	//demo.pixel_statistic(img);
	//demo.random_draw();
	//demo.mouse_event(img);
	//demo.image_normalization(img);
	//demo.image_resize(img);
	//demo.flip_image(img);
	//demo.rotate_image(img);
	//demo.video_demo();
	//demo.calc_hist(img);
	//demo.calc_hist_2D(img);
	//demo.equalize_hist(img);
	//demo.blur_img(img);
	demo.face_detection();

	waitKey(0);
	destroyAllWindows();

	return 0;
}