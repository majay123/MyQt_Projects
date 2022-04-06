/*
 * 
 * 　　┏┓　　　┏┓+ +
 * 　┏┛┻━━━┛┻┓ + +
 * 　┃　　　　　　　┃ 　
 * 　┃　　　━　　　┃ ++ + + +
 *  ████━████ ┃+
 * 　┃　　　　　　　┃ +
 * 　┃　　　┻　　　┃
 * 　┃　　　　　　　┃ + +
 * 　┗━┓　　　┏━┛
 * 　　　┃　　　┃　　　　　　　　　　　
 * 　　　┃　　　┃ + + + +
 * 　　　┃　　　┃
 * 　　　┃　　　┃ +  神兽保佑
 * 　　　┃　　　┃    代码无bug　　
 * 　　　┃　　　┃　　+　　　　　　　　　
 * 　　　┃　 　　┗━━━┓ + +
 * 　　　┃ 　　　　　　　┣┓
 * 　　　┃ 　　　　　　　┏┛
 * 　　　┗┓┓┏━┳┓┏┛ + + + +
 * 　　　　┃┫┫　┃┫┫
 * 　　　　┗┻┛　┗┻┛+ + + +
 * 
 * 
 * 
 * ************Copyright 2022 MCD************
 * 
 * @version      : 
 * @Company      : HOPE
 * @Author       : MCD
 * @Date         : 2022-04-06 14:59:00
 * @LastEditors  : MCD
 * @LastEditTime : 2022-04-06 15:01:59
 * @FilePath     : /QT_MyXVideo/main.cpp
 * @Description  : 
 * 
 * ******************************************
 */

#include "xvideo.h"

#include <QApplication>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

int main(int argc, char *argv[])
{
#if 1 // show a pic
    Mat img = imread("/Users/mcd/Pictures/pap.er/2SfQsGX4Szg.jpg", -1);
    if(img.empty()) return -1;
    namedWindow("Example", cv::WINDOW_AUTOSIZE);
    imshow("Example", img);
    waitKey(0);
    destroyWindow("Example");
#else
    QApplication a(argc, argv);
    XVideo w;
    w.show();
    return a.exec();
#endif
}
