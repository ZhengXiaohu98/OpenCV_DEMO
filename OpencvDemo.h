#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class OpencvDemo
{
public:
	void colorSpace(Mat& img);
	void mat_creation(Mat& img);
	void pixel_visited(Mat& img);
	void image_arithmetics(Mat& img);
	void track_bar(Mat& img);
	void key_response(Mat& img);
	void color_map(Mat& img);
	void bitwise_operation();
	void split_merge(Mat& img);
	void colorSpaceUse(Mat& img);
	void pixel_statistic(Mat& img);
	void random_draw();
	void mouse_event(Mat& img);
	void image_normalization(Mat& img);
	void image_resize(Mat& img);
	void flip_image(Mat& img);
	void rotate_image(Mat& img);
	void video_demo();
	void calc_hist(Mat& img);
	void calc_hist_2D(Mat& img);
	void equalize_hist(Mat& img);
	void blur_img(Mat& img);
	void face_detection();
};