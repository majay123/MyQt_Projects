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
 * @Date         : 2022-04-07 09:10:30
 * @LastEditors  : MCD
 * @LastEditTime : 2022-04-07 10:12:49
 * @FilePath     : /MyQt_Projects/QT_MyXVideo/videowidget.h
 * @Description  : 
 * 
 * ******************************************
 */

#ifndef VIDEOWIDGET
#define VIDEOWIDGET

#include <QOpenGLWidget>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <QImage>
#include <QObject>

class VideoWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    VideoWidget(QWidget *p);
    void paintEvent(QPaintEvent *e);
    virtual ~VideoWidget();

public slots:
    void SetImage(cv::Mat mat);

protected:
    QImage img;
};

#endif // !VIDEOWIDGET
