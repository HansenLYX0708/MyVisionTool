// _CodeStudy.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv )
{
	namedWindow("exp3", WINDOW_AUTOSIZE);
	VideoCapture cap;
	cap.open(string(argv[1]));
	Mat frame;
	for (;;)
	{
		cap >> frame;
		if (frame.empty())
		{
			break;
		}
		imshow("exp3", frame);
		if (waitKey(33) >= 0)
		{
			break;
		}
	}
	Matx<float, 3, 3> a;
    return 0;
}

