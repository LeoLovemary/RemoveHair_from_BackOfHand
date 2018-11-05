#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//����˼�룺���ǿ�ȣ�0-255��ͻȻ�仯��ģ�������򣬴�����һ���鹹�ľ��Σ�1x9���أ�����ͼ�� 
//���ھ��ε�ÿһ���ƶ�,��ȡ9����ֱ���أ������ǿ�ȵ�ͻȻ�����������������Ϊ30���������˲�ģ����̲���

int main()
{
    Mat image;
    image = imread("clahe.jpg", IMREAD_GRAYSCALE);
	imshow("src",image);
    if (image.data==NULL)
        cout << "Img not found" << endl;
    namedWindow("hand", WINDOW_AUTOSIZE);
    Mat orig = image.clone();
    threshold(image, image, 180, 255, THRESH_BINARY);

    int height = 8; 
    for(int x=0;x<image.cols;x++)  //����forѭ���趨1*8 �ľ��������ƶ��Ĺ켣
        for (int y = height / 2; y < image.rows - height / 2; y++)
        {
            int whiteToBlack = 0, blackToWhite = 0;
            for (int rectY = y - height / 2; rectY < y + height / 2 - 1; rectY++) //���for �ȽϾ��������ڲ������ص�ǰ���Ƿ�����������
                if (image.at<uchar>(rectY, x) > image.at<uchar>(rectY + 1, x) && image.at<uchar>(rectY, x) - image.at<uchar>(rectY + 1, x) > 30)
                    whiteToBlack++; //ͳ����������ͺ͸���
                else if (image.at<uchar>(rectY, x) < image.at<uchar>(rectY + 1, x) && image.at<uchar>(rectY + 1, x) - image.at<uchar>(rectY, x) > 30)
                    blackToWhite++;
            if (whiteToBlack > 0 && blackToWhite > 0)
                for (int rectY = y - height / 4; rectY < y + height / 4 - 1; rectY++)
            blur(orig(Rect(x, y - height / 2, 4, height + 1)), orig(Rect(x, y - height / 2, 4, height + 1)),Size(3,3)); //�Ե�ǰ�ľ��������ڲ������˲�ģ�����Ӷ��ﵽȥ����ë������
        }

    imshow("hand", orig);
    waitKey(0);
}
