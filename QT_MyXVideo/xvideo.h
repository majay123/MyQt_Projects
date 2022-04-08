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
 * @Date         : 2022-04-08 12:39:14
 * @LastEditors  : MCD
 * @LastEditTime : 2022-04-08 12:51:18
 * @FilePath     : /QT_MyXVideo/xvideo.h
 * @Description  : 
 * 
 * ******************************************
 */

#ifndef XVIDEO_H
#define XVIDEO_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QMessageBox>
#include <QTimerEvent>
#include <QObject>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class XVideo; }
QT_END_NAMESPACE

class XVideo : public QWidget
{
    Q_OBJECT

public:
    XVideo(QWidget *parent = nullptr);
    ~XVideo();
    void timerEvent(QTimerEvent *e);

// public slots:
//     // 打开视频1按钮信号
//     void Open();
//     void SlidePress();
//     void SlideRelease();
//     // 滑动条拖动
//     void SetPos(int pos);
//     // 设置过滤器
//     void Set();
//     // 导出视频
//     void Export();

//     void Play();
//     void Pause();

//     void Mark();
private slots:
    // 打开视频1按钮信号
    void on_open1_clicked();

    void on_playSlider_sliderPressed();
    void on_playSlider_sliderReleased();
    // 滑动条拖动
    void on_playSlider_valueChanged(int value);

    //播放暂停
    void on_playButton_clicked();
    void on_pauseButton_clicked();
    // 水印
    void on_exportButton_2_clicked();

    // 导出视频
    void on_exportButton_clicked();
    // 设置过滤器
    void on_pushButton_clicked();


private:
    Ui::XVideo *ui;
};
#endif // XVIDEO_H
