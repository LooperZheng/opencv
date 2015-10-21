#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "iostream"

//#include <IOSTREAM> // for test,需要命名空间std，才能用cout
using namespace std; //命名空间

int main(int argc, char* argv[])
{
	IplImage* src;
	IplImage* temp1;
	IplImage* temp2;
	IplImage* temp3;
	double elem1;
	double elem2;
	src = cvLoadImage("pic.bmp",CV_LOAD_IMAGE_GRAYSCALE);
	if (!src)
	{
		cout << "can not load the image : " << endl;
	}

	temp1 = cvCreateImage(cvGetSize(src), 8, 1);
	temp2 = cvCreateImage(cvGetSize(src), 8, 1);
	temp3 = cvCreateImage(cvGetSize(src), 8, 1);
	int H = src->height;
	int W = src->width;


	//原图行变换
	for (int i = 0; i < (H / 2); i++)
	for (int j = 0; j < W; j++)
	{
		elem1 = cvGet2D(src, 2 * i, j).val[0];  //取偶数行
		cvSet2D(temp3, i, j, elem1);          //上半边
	}
	for (int i = 0; i < (H / 2); i++)
	for (int j = 0; j < W; j++)
	{
		elem1 = cvGet2D(src, (2 * i + 1), j).val[0]; //取奇数行
		elem2 = cvGet2D(src, 2 * i, j).val[0]; //取对应的偶数行
		cvSet2D(temp3, (H / 2) + i, j, elem1 - elem2);       //下半边
	}
	//原图列变换
	for (int j = 0; j < (W / 2); j++)
	for (int i = 0; i < H; i++)
	{
		elem1 = cvGet2D(src, i, 2 * j).val[0];  //取偶数列
		cvSet2D(temp1, i, j, elem1);        //左半边
	}

	for (int j = 0; j < (W / 2); j++)
	for (int i = 0; i < H; i++)
	{
		elem1 = cvGet2D(src, i, (2 * j + 1)).val[0];  //取奇数列
		elem2 = cvGet2D(src, i, 2 * j ).val[0];    //取对应的偶数列
		cvSet2D(temp1, i, W / 2 + j, elem1-elem2);  //右半边
	}

	//在列变换基础上再进行行变换
	for (int i = 0; i < (H/2); i++)
	for (int j = 0; j < W; j++)
	{
		elem1=cvGet2D(temp1, 2*i, j).val[0];  //取偶数行
		cvSet2D(temp2, i, j, elem1);          //上半边
	}
	for (int i = 0; i < (H / 2); i++)
	for (int j = 0; j < W; j++)
	{
		elem1 = cvGet2D(temp1, (2 * i + 1), j).val[0]; //取奇数行
		elem2 = cvGet2D(temp1, 2 * i , j).val[0]; //取对应的偶数行
		cvSet2D(temp2, (H / 2) + i, j, elem1-elem2);       //下半边
	}

	cvNamedWindow("原图", 1);
	cvShowImage("原图", src);
	cvSaveImage("原图.bmp", src);
	cvNamedWindow("列变换", 1);
	cvShowImage("列变换", temp1);
	cvSaveImage("列变换.bmp", temp1);
	cvNamedWindow("列变换", 1);
	cvShowImage("行变换", temp3);
	cvSaveImage("行变换.bmp", temp3);
	cvNamedWindow("行列变换", 1);
	cvShowImage("行列变换", temp2);
	cvSaveImage("行列变换.bmp", temp2);
	cvWaitKey(0);

	cvReleaseImage(&src);
	return 0;
}