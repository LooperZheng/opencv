#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "iostream"

//#include <IOSTREAM> // for test,��Ҫ�����ռ�std��������cout
using namespace std; //�����ռ�

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


	//ԭͼ�б任
	for (int i = 0; i < (H / 2); i++)
	for (int j = 0; j < W; j++)
	{
		elem1 = cvGet2D(src, 2 * i, j).val[0];  //ȡż����
		cvSet2D(temp3, i, j, elem1);          //�ϰ��
	}
	for (int i = 0; i < (H / 2); i++)
	for (int j = 0; j < W; j++)
	{
		elem1 = cvGet2D(src, (2 * i + 1), j).val[0]; //ȡ������
		elem2 = cvGet2D(src, 2 * i, j).val[0]; //ȡ��Ӧ��ż����
		cvSet2D(temp3, (H / 2) + i, j, elem1 - elem2);       //�°��
	}
	//ԭͼ�б任
	for (int j = 0; j < (W / 2); j++)
	for (int i = 0; i < H; i++)
	{
		elem1 = cvGet2D(src, i, 2 * j).val[0];  //ȡż����
		cvSet2D(temp1, i, j, elem1);        //����
	}

	for (int j = 0; j < (W / 2); j++)
	for (int i = 0; i < H; i++)
	{
		elem1 = cvGet2D(src, i, (2 * j + 1)).val[0];  //ȡ������
		elem2 = cvGet2D(src, i, 2 * j ).val[0];    //ȡ��Ӧ��ż����
		cvSet2D(temp1, i, W / 2 + j, elem1-elem2);  //�Ұ��
	}

	//���б任�������ٽ����б任
	for (int i = 0; i < (H/2); i++)
	for (int j = 0; j < W; j++)
	{
		elem1=cvGet2D(temp1, 2*i, j).val[0];  //ȡż����
		cvSet2D(temp2, i, j, elem1);          //�ϰ��
	}
	for (int i = 0; i < (H / 2); i++)
	for (int j = 0; j < W; j++)
	{
		elem1 = cvGet2D(temp1, (2 * i + 1), j).val[0]; //ȡ������
		elem2 = cvGet2D(temp1, 2 * i , j).val[0]; //ȡ��Ӧ��ż����
		cvSet2D(temp2, (H / 2) + i, j, elem1-elem2);       //�°��
	}

	cvNamedWindow("ԭͼ", 1);
	cvShowImage("ԭͼ", src);
	cvSaveImage("ԭͼ.bmp", src);
	cvNamedWindow("�б任", 1);
	cvShowImage("�б任", temp1);
	cvSaveImage("�б任.bmp", temp1);
	cvNamedWindow("�б任", 1);
	cvShowImage("�б任", temp3);
	cvSaveImage("�б任.bmp", temp3);
	cvNamedWindow("���б任", 1);
	cvShowImage("���б任", temp2);
	cvSaveImage("���б任.bmp", temp2);
	cvWaitKey(0);

	cvReleaseImage(&src);
	return 0;
}