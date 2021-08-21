#include "OpencvDemo.h"

//This fucntion will pass a Mat object, then convert the original image
//to a gray scale image and a Hsv scale img by using "cvtColor" function
void OpencvDemo::colorSpace(Mat& img)
{
	Mat gray_img, hsv_img;
	cvtColor(img, gray_img, COLOR_BGR2GRAY);
	cvtColor(img, hsv_img, COLOR_BGR2HSV);
	namedWindow("Gray Scale", WINDOW_AUTOSIZE);
	namedWindow("Hsv Scale", WINDOW_AUTOSIZE);
	imshow("Gray Scale", gray_img);
	imshow("Hsv Scale", hsv_img);
}

//this function will test copyTo() fucntion and clone() function, aka "deep copy"
//it will also use zeros/ones to create an empty image
void OpencvDemo::mat_creation(Mat& img)
{
	Mat img1, img2;
	img1 = img.clone(); //using clone(), will return a new mat object
	img.copyTo(img2); //img2 is now a new Mat object as the same as img
	//notice img3 is like a pointer to img, it is not a new object
	//if we change the content of img, img3 will change as well
	Mat img3 = img;

	namedWindow("Clone image", WINDOW_AUTOSIZE);
	namedWindow("copyTo image", WINDOW_AUTOSIZE);
	imshow("Clone image", img1);
	imshow("copyTo image", img2);

	//using zeros to create a empty imgae;
	Mat img4 = Mat::zeros(Size(512, 512), CV_8UC3);
	cout << "Width: " << img4.cols << "  Height: " << img4.rows << "  Channels: " << img4.channels() << endl;
	//cout << img4 << endl;
	img4 = Scalar(255, 0, 0);
	//cout << "Image after giving values" << endl;
	//cout << img4 << endl;
	namedWindow("Empty image", WINDOW_AUTOSIZE);
	imshow("Empty image", img4);
}


//this function will visted each pixel value and then invert it
//it uses two ways to traverse the image matrix
void OpencvDemo::pixel_visited(Mat& img)
{
	//we will read every pixel value then invert it
	int width = img.cols, height = img.rows;
	int dim = img.channels(); //channels / dimentions

	//traverse by index
	/*for (int row = 0; row < height; ++row)
	{
		for (int col = 0; col < width; ++col)
		{
			if (dim == 1) // if the image only have one channel
			{
				int pv = img.at<uchar>(row, col);
				img.at<uchar>(row, col) = 255 - pv;
			}
			if (dim == 3) // if the image have three channels (RGB)
			{
				Vec3b bgr = img.at<Vec3b>(row, col);
				img.at<Vec3b>(row, col)[0] = 255 - bgr[0];
				img.at<Vec3b>(row, col)[1] = 255 - bgr[1];
				img.at<Vec3b>(row, col)[2] = 255 - bgr[2];
			}
		}
	}*/

	//traverse by pointer
	for (int row = 0; row < height; ++row)
	{
		uchar* cur = img.ptr<uchar>(row);
		for (int col = 0; col < width; ++col)
		{
			if (dim == 1) // if the image only have one channel
			{
				int pv = *cur;
				*cur = 255 - pv;
				++cur;
			}
			if (dim == 3) // if the image have three channels (RGB)
			{
				*cur++ = 255 - *cur;
				*cur++ = 255 - *cur; 
				*cur++ = 255 - *cur;
			}
		}
	}
	
	namedWindow("pv image");
	imshow("pv image", img);
}

//this function will introduce how to do
//mutiplication, division, addtion and substraction on an image;
void OpencvDemo::image_arithmetics(Mat& img)
{
	Mat dest = Mat::zeros(img.size(), img.type());
	Mat img1 = Mat::zeros(img.size(), img.type());
	img1 = Scalar(50, 50, 50);

	//addtion
	/*add(img, img1, dest);
	namedWindow("Addition", WINDOW_AUTOSIZE);
	imshow("Addition", dest);*/

	//substraction
	/*subtract(img, img1, dest);
	namedWindow("Substraction", WINDOW_AUTOSIZE);
	imshow("Substraction", dest);*/

	//division
	/*divide(img, img1, dest);
	namedWindow("Division", WINDOW_AUTOSIZE);
	imshow("Division", dest);*/

	//mutiplication
	/*multiply(img, img1, dest);
	namedWindow("Mutiplication", WINDOW_AUTOSIZE);
	imshow("Mutiplication", dest);*/

	//addtion/substraction is just adding the pixel value from img and src to the destination
	int width = img.cols, height = img.rows;
	for (int row = 0; row < height; ++row)
	{
		uchar* ptr_dest = dest.ptr<uchar>(row); //pointer of destination
		uchar* ptr_img = img.ptr<uchar>(row);   //pointer of the original image
		uchar* ptr_img1 = img1.ptr<uchar>(row); //pointer of the scalar image
		for (int col = 0; col < width; ++col)
		{
			//saturate_cast<uchar> will keep the pixel value in the accepted range 0 - 255
			*ptr_dest = saturate_cast<uchar>(*ptr_img + *ptr_img1);
			++ptr_dest, ++ptr_img, ++ptr_img1;
			*ptr_dest = saturate_cast<uchar>(*ptr_img + *ptr_img1);
			++ptr_dest, ++ptr_img, ++ptr_img1;
			*ptr_dest = saturate_cast<uchar>(*ptr_img + *ptr_img1);
			++ptr_dest, ++ptr_img, ++ptr_img1;
		}
	}
	namedWindow("Addtion by pv visit", WINDOW_AUTOSIZE);
	imshow("Addtion by pv visit", dest);
}

//the following functions will create a track bar
//we can slide the track bar to change the brightness;
static void on_brightness(int b, void* img)
{
	/*Mat original_img = *((Mat*)img);
	Mat value_img = Mat::zeros(original_img.size(), original_img.type());
	Mat display_img = Mat::zeros(original_img.size(), original_img.type());
	int val = b - 50;
	addWeighted(original_img, 1.0, value_img, 0, val, display_img);
	imshow("Trackbar image", display_img);*/

	//An easier way
	Mat original_img = *((Mat*)img);
	Mat display_img;
	int val = b - 50;
	original_img.convertTo(display_img, -1, 1.0, val);
	imshow("Trackbar image", display_img);
}

//addWeighted(InputAry1, weight of InputAry1, InputAry2, weight of InputAry2, gamma(value added to each pixel), destination)
static void on_contrast(int c, void* img)
{
	/*Mat original_img = *((Mat*)img);
	Mat value_img = Mat::zeros(original_img.size(), original_img.type());
	Mat display_img = Mat::zeros(original_img.size(), original_img.type());
	double contrast = c / 100.0;
	addWeighted(original_img, contrast, value_img, 0, 0, display_img);
	imshow("Trackbar image", display_img);*/

	//An easier way
	Mat original_img = *((Mat*)img);
	Mat display_img;
	double contrast = c / 100.0;
	original_img.convertTo(display_img, -1, contrast, 0);
	imshow("Trackbar image", display_img);
}

void OpencvDemo::track_bar(Mat& img)
{
	namedWindow("Trackbar image", WINDOW_AUTOSIZE);
	const int MAX_BRIGHTNESS = 100;
	const int MAX_CONTRASTNESS = 200;
	int brightness = 50;
	int contrast = 100;
	createTrackbar("Brightness", "Trackbar image", &brightness, MAX_BRIGHTNESS, on_brightness, (void*)(&img));
	createTrackbar("Contrastness", "Trackbar image", &contrast, MAX_CONTRASTNESS, on_contrast, (void*)(&img));
}


//This function will demostrat how users can interact with the image by using keyboard
void OpencvDemo::key_response(Mat& img)
{
	Mat dest;
	namedWindow("Key response image", WINDOW_AUTOSIZE);
	while (1)
	{
		int key = waitKey(50);
		if (key == 27)
		{
			break;
		}
		else if ((char)(key) == 'o' || (char)(key) == 'O')
		{
			imshow("Key response image", img);
		}
		else if ((char)(key) == 'g' || (char)(key) == 'G')
		{
			cvtColor(img, dest, COLOR_BGR2GRAY);
			imshow("Key response image", dest);
		}
		else if ((char)(key) == 'h' || (char)(key) == 'H')
		{
			cvtColor(img, dest, COLOR_BGR2HSV);
			imshow("Key response image", dest);
		}
	}
}

//this function will show the effect of opencv color map
void OpencvDemo::color_map(Mat& img)
{
	int colorMap[] = {
		  COLORMAP_AUTUMN,
		  COLORMAP_BONE,
		  COLORMAP_JET,
		  COLORMAP_WINTER,
		  COLORMAP_RAINBOW,
		  COLORMAP_OCEAN,
		  COLORMAP_SUMMER,
		  COLORMAP_SPRING,
		  COLORMAP_COOL,
		  COLORMAP_HSV,
		  COLORMAP_PINK, 
		  COLORMAP_HOT,
		  COLORMAP_PARULA, 
		  COLORMAP_MAGMA,
		  COLORMAP_INFERNO,
		  COLORMAP_PLASMA,
		  COLORMAP_VIRIDIS,
		  COLORMAP_CIVIDIS,
		  COLORMAP_TWILIGHT,
		  COLORMAP_TWILIGHT_SHIFTED,
		  COLORMAP_TURBO,
		  COLORMAP_DEEPGREEN
	};

	Mat dest;
	namedWindow("Color map image", WINDOW_AUTOSIZE);
	int i = 0;
	while (1)
	{
		if (waitKey(1000) == 27) break;
		applyColorMap(img, dest, colorMap[i]);
		i = (i + 1) % 21;
		imshow("Color map image", dest);
	}
}

//this function demostrate the bitwise operation amoung images
void OpencvDemo::bitwise_operation()
{
	Mat img1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat img2 = Mat::zeros(Size(256, 256), CV_8UC3);
	rectangle(img1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);
	rectangle(img2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);
	imshow("Image1", img1);
	imshow("Image2", img2);

	Mat dest;
	//bitwise_and
	//bitwise_and(img1, img2, dest);

	//bitwise_or
	//bitwise_or(img1, img2, dest);

	//bitwise_xor
	//bitwise_xor(img1, img2, dest);

	//bitwise_not
	//bitwise_not(img1, dest);

	imshow("Bitwise operation", dest);
}

//The following function will demostrate how to split and merge images
void OpencvDemo::split_merge(Mat& img)
{
	vector<Mat> v;
	split(img, v);
	imshow("Blue channel", v[0]);
	imshow("Green channel", v[1]);
	imshow("Red channel", v[2]);

	//notice the above code actually didn't show the difference between these three color channels
	//We can then do the following, the following will keep the Red channel
	Mat dest;
	v[0] = v[1] = 0; //red
	//v[0] = v[2] = 0; //Green
	//v[1] = v[2] = 0; //blue
	merge(v, dest);
	imshow("Merged Red Channel", dest);
}

//this function demostrate how to change the color space
//then use inRange() function get the target mask;
//It will get the area with the color that is in that color range, and will have the value of 1(white)
//the other unselected part will have the value of 0(black)
//which is also the reason we need to negate the mask before we use it as our mask
void OpencvDemo::colorSpaceUse(Mat& img)
{
	Mat hsv_img;
	cvtColor(img, hsv_img, COLOR_BGR2HSV); //change the color space to HSV
	Mat mask;
	inRange(hsv_img, Scalar(35,43,46), Scalar(77,255,255), mask); //get all the area mask without green
	imshow("Mask image", mask);

	Mat dest = Mat::zeros(img.size(), img.type());
	dest = Scalar(0, 255, 255);
	mask = ~mask; //negate the mask image, same as bitwise_not(mask, mask);
	img.copyTo(dest, mask);
	imshow("Result image", dest);
}

//this function demostrate how to anylize the statistic of an image
//it will be using minMaxLoc() and meanStdDev() function to get the statistic
void OpencvDemo::pixel_statistic(Mat& img)
{
	double minV, maxV;
	Point minLoc, maxLoc;
	vector<Mat> v;
	split(img, v);
	for (int i = 0; i < v.size(); ++i)
	{
		minMaxLoc(v[i], &minV, &maxV, &minLoc, &maxLoc);
		cout << "Channel #" << i << "  Min_value: " << minV << "  Max_value: " << maxV << "  Min_value_loc:" << minLoc << "  Max_value_loc:" << maxLoc << endl;
	}

	Mat mean, stddev;
	meanStdDev(img, mean, stddev);
	for (int i = 0; i < 3; ++i)
	{
		cout << "Mean value at Channel#" << i << ": " << mean.at<double>(i,0) << endl;
		cout << "Std deviation at Channel#" << i << ": " << stddev.at<double>(i,0) << endl;
	}
}

void OpencvDemo::random_draw()
{
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	RNG rng(12345);
	int width = canvas.cols, height = canvas.rows;

	while (1)
	{
		if (waitKey(10) == 27) break;
		//reset the canvas
		canvas = Scalar(0, 0, 0);

		int x1 = rng.uniform(0, width), y1 = rng.uniform(0, height);
		int x2 = rng.uniform(0, width), y2 = rng.uniform(0, height);
		//randomly draw a line
		line(canvas, Point(x1, y1), Point(x2, y2), Scalar(rng.uniform(0, 255), 
			rng.uniform(0, 255), rng.uniform(0, 255)), 1, LINE_8, 0);

		//randomly draw a circle
		circle(canvas, Point(x2, y2), 20, Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255)), 1, LINE_8, 0);

		//randomly draw a rectangle
		rectangle(canvas, Rect(x1, y1, 20, 20), Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255)), 1, LINE_8, 0);
		
		//randomly draw a ellipse
		ellipse(canvas, RotatedRect(Point(x1 + 20, y1 + 20), Size(20, 40), 0), Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255)), 1, LINE_8);

		//randomly draw a triangle
		int x3 = rng.uniform(0, width), y3 = rng.uniform(0, height);
		vector<Point> pts = { Point(x1, y1), Point(x2, y2) , Point(x3, y3) };
		polylines(canvas, pts, true, Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255)), 1, LINE_8);

		imshow("My Canvas", canvas);
	}
}

//the following function demostrate how to create mouse event
Point sp(-1, -1);
Point ep(-1, -1);
Mat temp;
//callback function
static void on_mouse(int event_type, int x, int y, int flag, void* userdata)
{
	Mat img = *((Mat*)userdata);
	if (event_type == EVENT_LBUTTONDOWN)
	{
		sp.x = x;
		sp.y = y;
		cout << "Clicked on: " << sp << endl;
	}
	else if (event_type == EVENT_LBUTTONUP)
	{
		ep.x = x;
		ep.y = y;
		if (ep.x > sp.x && ep.y > sp.y)
		{
			Rect rect(sp, ep);
			rectangle(img, rect, Scalar(0, 0, 255), 2, LINE_8, 0);
			imshow("Mouse event demo", img);
			//to show the selected area
			imshow("ROI area", temp(rect));
			 
			//the mousemove event will draw accidently if we don't attempt to reset the point value
			//so we set the point to negative to indicate weather we want to draw the rect
			sp.x = sp.y = -1;
		}
	}
	else if (event_type == EVENT_MOUSEMOVE)
	{
		ep.x = x;
		ep.y = y;
		//also need to check if the start point is clicked
		if (ep.x > sp.x && ep.y > sp.y && sp.x > 0 && sp.y > 0)
		{
			temp.copyTo(img); // get the original image
			Rect rect(sp, ep);
			rectangle(img, rect, Scalar(0, 0, 255), 2, LINE_8, 0);
			imshow("Mouse event demo", img);
		}
	}
}

void OpencvDemo::mouse_event(Mat& img)
{
	temp = img.clone();
	namedWindow("Mouse event demo", WINDOW_AUTOSIZE);
	namedWindow("ROI area", WINDOW_AUTOSIZE); // this window is for selected area
	setMouseCallback("Mouse event demo", on_mouse,(void*)(&img));
	imshow("Mouse event demo", img);
}

//image normalization demo
void OpencvDemo::image_normalization(Mat& img)
{
	Mat dest;
	//convert the type of the image to float first
	img.convertTo(img, CV_32F);
	//normalize the image: so the pixel value will between 0.0 - 1.0
	normalize(img, dest, 1.0, 0, NORM_MINMAX, -1);
	imshow("Normalized image", dest);
}

//The following function demostrate how to resize an image in Opencv
double scale = 1;
static void on_resize(int event_type, int x, int y, int flag, void* userdata)
{
	Mat img = *((Mat*)userdata);
	int w = img.cols, h = img.rows;
	if (event_type == EVENT_MOUSEWHEEL)
	{
		if (getMouseWheelDelta(flag) > 0)
			scale += 0.1;
		else
			scale -= 0.1;
		//using bliner to resize the image
		//val = 0.5 (zoomin by 0.5 scale) val = 2 (zoomout by 2 scale)
		resize(img, img, Size(w * scale, h * scale), 0, 0, INTER_LINEAR);
		imshow("Resized Image", img);
	}
}

void OpencvDemo::image_resize(Mat& img)
{
	namedWindow("Resized Image", WINDOW_AUTOSIZE);
	setMouseCallback("Resized Image", on_resize, (void*)(&img));
	imshow("Resized Image", img);
}

//demostrate how to flip the image -- (0, 1, -1)
void OpencvDemo::flip_image(Mat& img)
{
	Mat dest;
	//flip(img, dest, 0); // filp the img along x-axis
	flip(img, dest, 1); // filp the img along y-axis
	//flip(img, dest, -1); // filp the img along diagnals(rotate by 180 degrees)
	imshow("Fliped Image", dest);
}

//demostrate how to rotate the imgae
void OpencvDemo::rotate_image(Mat& img)
{
	//this code has a problem, this can only rotate the imgae by a factor of 90.
	//the following code will solve the issue
	/*
	Mat dest;
	//we can change the rotate code to rotate the image respectively
	//ROTATE_90_COUNTERCLOCKWISE == rotate 270 clockwise
	rotate(img, dest, ROTATE_90_CLOCKWISE);
	imshow("Rotated Image", dest);
	*/

	/*
	//this code can rotate the image by any degree
	//but notice the size of the window is not automatically adjusted
	Mat dest, M;
	int w = img.cols, h = img.rows;
	M = getRotationMatrix2D(Point2f(w / 2, h / 2), 45, 1.0); //be careful this needs to be Point2f!
	warpAffine(img, dest, M, img.size(), INTER_LINEAR, 0, Scalar(255, 0, 0));
	imshow("Rotated Image", dest);
	*/

	//in order to fix the problem above, we need to do some calculation
	Mat dest, M;
	int w = img.cols, h = img.rows;
	M = getRotationMatrix2D(Point2f(w / 2, h / 2), 45, 1.0);
	//to get the sincos value of the angle, must be abs value
	double cos = abs(M.at<double>(0, 0)); //cos value is located at 0,0
	double sin = abs(M.at<double>(0, 1)); //sin value is located at 0,1
	//calculate the new height and new width
	int nw = w * cos + h * sin;
	int nh = w * sin + h * cos;
	M.at<double>(0, 2) += (nw/2 - w/2);
	M.at<double>(1, 2) += (nh/2 - h/2);
	//rotated the image
	warpAffine(img, dest, M, Size(nw, nh), INTER_LINEAR, 0, Scalar(255, 0, 0));
	imshow("New rotated image", dest);
}

//this function demostrate how to open default camera and load video.
void OpencvDemo::video_demo()
{
	//pass 0 means using default camera
	//pass "D:/path" can load a video
	VideoCapture cap(0);
	
	//we can get the information of the video by using the get function and pass the corresponding ID
	//get information of the video
	int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);
	int frame_count = cap.get(CAP_PROP_FRAME_COUNT);
	double fps = cap.get(CAP_PROP_FPS);
	cout << "Frame width: " << frame_width << endl;
	cout << "Frame height: " << frame_height << endl;
	cout << "Frame count: " << frame_count << endl;
	cout << "Frames per second: " << fps << endl;

	//we can also save a video by define a videowriter object
	//notice """20""" is the user defined FPS since we are using the default camera
	//and the fps returns 0 as shown which cannot be used to generate recorded video
	VideoWriter vw("D:/test.mp4", cap.get(CAP_PROP_FOURCC), 20, Size(frame_width, frame_height), true);

	Mat frame;
	int mode = 1;
	while (1)
	{
		//read an empty frame, then we need to break the loop, usually mark the end of the video
		if (!cap.read(frame))
			break;
		int key = waitKey(10);
		char ch = key;

		//if the user has pressed O then reset the mode back to original
		if (ch == 'O' || ch == 'o')
			mode = 1;
		//If the user pressed H or h, then we convert the color space to HSV
		else if (ch == 'H' || ch == 'h')
			mode = 2;
		//if the user pressed G or g, then we convert the color space to GRAY
		else if (ch == 'G' || ch == 'g')
			mode = 3;

		if(mode == 2)
			cvtColor(frame, frame, COLOR_BGR2HSV);
		else if(mode == 3)
			cvtColor(frame, frame, COLOR_BGR2GRAY);

		imshow("Video demo", frame);

		vw.write(frame);

		//the user has pressed ESC key to quit
		if (waitKey(10) == 27)
			break;
	}

	//need to release the file
	cap.release();
	vw.release();
}

//this function demostrate how to draw the histogram of an image
void OpencvDemo::calc_hist(Mat& img)
{
	//split the img into 3 channels
	vector<Mat> bgr_planes;
	split(img, bgr_planes);

	int histsize = 256;
	float range[] = { 0, 256 };
	const float* histRange[] = { range };

	//calling the calcHist function to calculate the histgram
	Mat b_hist, g_hist, r_hist;
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histsize, histRange, true, false);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histsize, histRange, true, false);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histsize, histRange, true, false);

	//create a canvas for drawing the lines later
	int hist_w = 512, hist_h = 400;
	Mat histDiagram = Mat::zeros(hist_h, hist_w, CV_8UC3);
	int bin_w = cvRound((double)hist_w / histsize);

	//need to normalize the image
	normalize(b_hist, b_hist, 0, histDiagram.rows ,NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histDiagram.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histDiagram.rows, NORM_MINMAX, -1, Mat());

	//draw the histgram
	for (int i = 1; i < histsize; ++i)
	{
		line(histDiagram, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i-1))),
			Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))), 
			Scalar(255,0,0), 2, LINE_8, 0);
		line(histDiagram, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))), 
			Scalar(0, 255, 0), 2, LINE_8, 0);
		line(histDiagram, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))), 
			Scalar(0, 0, 255), 2, LINE_8, 0);
	}

	imshow("Histgram Image", histDiagram);
}

//this function will show how to calculate two dimentional histogram
void OpencvDemo::calc_hist_2D(Mat& img)
{
	Mat hsv_img, hist_img;
	cvtColor(img, hsv_img, COLOR_BGR2HSV);
	//histsize for two channels
	int hbins = 30, sbins = 32;
	int hist_bins[] = { hbins, sbins };
	float h_range[] = { 0, 180 };
	float s_range[] = { 0, 256 };
	const float* hist_ranges[] = { h_range, s_range };
	int hist_channels[] = { 0, 1 };
	calcHist(&hsv_img, 1, hist_channels, Mat(), hist_img, 2, hist_bins, hist_ranges, true, false);

	//normalizing the hist_img we get from last step, so we need max value of pixel to do that
	double maxV = 0;
	minMaxLoc(hist_img, 0, &maxV, 0, 0);
	int scale = 10;
	Mat hist_2D_img = Mat::zeros(sbins * scale, hbins * scale, CV_8UC3);
	for (int h = 0; h < hbins; ++h)
	{
		for (int s = 0; s < sbins; ++s)
		{
			float binVal = hist_img.at<float>(h, s);
			int intensity = cvRound(binVal * 255 / maxV);
			rectangle(hist_2D_img, Point(h * scale, s * scale),
				Point((h + 1) * scale - 1, (s + 1) * scale - 1),
				Scalar::all(intensity), -1);
		}
	}
	//we can also apply color_map to make the hist_2d_img more readable
	//applyColorMap(hist_2D_img, hist_2D_img, COLORMAP_JET);
	imshow("Histdiagram2D", hist_2D_img);
}

//this function demostrate how to use use function to do histogram equalization
void OpencvDemo::equalize_hist(Mat& img)
{
	//Fisrt thing we need to know is that this function can only apply to single channel
	//for the reason above, we need to convert the RGB img to gray scale first
	Mat gray_img, dest;
	cvtColor(img, gray_img, COLOR_RGB2GRAY);
	equalizeHist(gray_img, dest);
	imshow("Gray scale", gray_img);
	imshow("Equalized image", dest);

	//In case we also want to know how to equalize an RGB imgae;
	Mat hsv_img;
	cvtColor(img, hsv_img, COLOR_RGB2HSV);
	vector<Mat> v;
	split(hsv_img, v);
	equalizeHist(v[2], v[2]);
	merge(v, hsv_img);
	cvtColor(hsv_img, hsv_img, COLOR_HSV2RGB);
	imshow("Equalized RGB image", hsv_img);
}

//the following function demostrate how to blur an image using different  ways
void OpencvDemo::blur_img(Mat& img)
{
	Mat dest_box, dest_gaussian, dest_bilateral;

	//Box blur
	blur(img, dest_box, Size(3, 3), Point(-1, -1));
	imshow("Box Blur image", dest_box);
	
	//gaussian blur
	//this function will calculate the size of the window based on sigma, in our case 15
	//however, if we already have a window size, lets say (3,3), then it will ignore the sigma value
	GaussianBlur(img, dest_gaussian, Size(0, 0), 5);
	imshow("Gaussian Blur image", dest_gaussian);

	//bilateral filter
	//this kind of blur will also take color space into account
	//the effect of this function will erase the noise in the image
	bilateralFilter(img, dest_bilateral, 0, 100, 10);
	imshow("Bilateral Filer image", dest_bilateral);
}

//this is a face detection program
//we will use the opencv resourse file to detect our faces
void OpencvDemo::face_detection()
{
	//open our defalt camera
	VideoCapture cap(0);

	if (!cap.isOpened())
	{
		cout << "Cannot open camera..." << endl;
		return;
	}
	
	//define a CascadeClassifier object, then load the resource file
	CascadeClassifier faceCascade;
	faceCascade.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml");

	if (faceCascade.empty())
	{
		cout << "Cannot load the resource file..." << endl;
		return;
	}

	Mat frame;
	while (1)
	{
		cap.read(frame);
		vector<Rect> faceRects;
		faceCascade.detectMultiScale(frame, faceRects, 1.1, 10);
		int n = faceRects.size();
		for (int i = 0; i < n; ++i)
		{
			rectangle(frame, faceRects[i], Scalar(0, 0, 255), 2, LINE_8, 0);
			imshow("Face detection", frame);
		}

		//if the user press ESC, then quit the loop
		if (waitKey(10) == 27)
			break;
	}
}