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
 * @Date         : 2022-04-07 10:17:37
 * @LastEditors  : MCD
 * @LastEditTime : 2022-04-07 10:22:48
 * @FilePath     : /QT_MyXVideo/videowidget.cpp
 * @Description  : 
 * 
 * ******************************************
 */
#include "videowidget.h"
#include <QPainter>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

/**
 * @brief Construct a new Video Widget:: Video Widget object
 * 
 * @param p 
 */
VideoWidget::VideoWidget(QWidget *p):QOpenGLWidget(p)
{

}


/**
 * @brief 
 * 
 * @param e 
 */
void VideoWidget::paintEvent(QPaintEvent *e)
{
    QPainter p;

    p.begin(this);
    p.drawImage(QPoint(0, 0), img);
    p.end();
}


VideoWidget::~VideoWidget()
{

}

// mat是视频中每一帧的图像
void VideoWidget::SetImage(Mat mat)
{
    //建立QImage图像
    if(img.isNull()) {
        uchar *buf = new uchar[width() * height() * 3];
        img = QImage(buf, width(), height(), QImage::Format_RGB888);
    }
    Mat des;
    cv::resize(mat, des, cv::Size(img.size().width(), img.size().height()));

    // 设置图像颜色格式
    cv::cvtColor(des, des, COLOR_BGR2RGB);

    // 将Mat mat的图像拷贝到QImage上
    // img.bits()表示img的内存，mat.data表示mat的图像指针
    memcpy(img.bits(), des.data, des.cols * des.rows * des.elemSize());
    update();
}




