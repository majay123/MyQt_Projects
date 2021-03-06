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
 * @Date         : 2022-04-07 11:00:45
 * @LastEditors  : MCD
 * @LastEditTime : 2022-04-08 13:02:51
 * @FilePath     : /QT_MyXVideo/xvideo.cpp
 * @Description  :
 *
 * ******************************************
 */

#include "xvideo.h"
#include "./ui_xvideo.h"
#include "filter.h"
#include "imagepro.h"
#include "videothread.h"
#include "videowidget.h"

#include <QDebug>
#include <QFileDialog>
#include <string>

using namespace std;
using namespace cv;

static bool pressSlider = false;
static bool isMark = false;

XVideo::XVideo(QWidget *parent)
    : QWidget(parent), ui(new Ui::XVideo)
{
    ui->setupUi(this);
    // Qt默认不支持Mat类型传参，所以需要注册一个Mat类型
    qRegisterMetaType<cv::Mat>("cv::Mat");

    // 源视频显示信号
    connect(VideoThread::get(),
            SIGNAL(ViewImage1(cv::Mat)),
            ui->src1,
            SLOT(SetImage(cv::Mat)));
    // 输出视频显示信号
    connect(VideoThread::get(),
            SIGNAL(ViewDes(cv::Mat)),
            ui->des,
            SLOT(SetImage(cv::Mat)));
    
    // 默认显示播放按钮 隐藏暂停按钮
    on_pauseButton_clicked();
    startTimer(40);
}

XVideo::~XVideo()
{
    delete ui;
}

/*****************设置过滤器(用来添加任务)****************/

/**
 * @brief
 *
 * @param e
 */
void XVideo::timerEvent(QTimerEvent *e)
{
    if (pressSlider)
        return;
    double pos = VideoThread::get()->GetPos();
    ui->playSlider->setValue(pos * 100);
}


void XVideo::on_playSlider_sliderPressed()
{
    pressSlider = true;
}


void XVideo::on_playSlider_sliderReleased()
{
    pressSlider = false;
}


void XVideo::on_playButton_clicked()
{
    this->ui->pauseButton->show();
    this->ui->pauseButton->setGeometry(ui->playButton->geometry());
    VideoThread::get()->Play();
    this->ui->playButton->hide();
}


void XVideo::on_pauseButton_clicked()
{
    this->ui->playButton->show();
    this->ui->pauseButton->hide();
    VideoThread::get()->Pause();
}

/**
 * @brief 水印
 *
 */
void XVideo::on_exportButton_2_clicked()
{
    isMark = false;

    QString name = QFileDialog::getOpenFileName(this, "select image");
    if (name.isEmpty())
        return;

    std::string file = name.toLocal8Bit().data();
    cv::Mat mark = imread(file);
    if (mark.empty())
        return;
    VideoThread::get()->SetMark(mark);
    isMark = true;
}

/**
 * @brief 打开按钮的open
 *
 */
void XVideo::on_open1_clicked()
{
    qDebug() << "Open button";
    QString name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("请选择视频文件"));
    if (name.isEmpty())
        return;

    string file = name.toLocal8Bit().data();
    if (!VideoThread::get()->Open(file)) { // 这里新建一个进程播放视频
        QMessageBox::information(this, "error", name + "open failed!");
        return;
    }

    on_playButton_clicked();
}

/**
 * @brief 导出视频
 *
 */
void XVideo::on_exportButton_clicked()
{
    static bool isExport = false;

    // 停止导出
    if (isExport) {
        VideoThread::get()->StopSave();
        isExport = false;
        ui->exportButton->setText("开始导出");
        return;
    }

    QString name = QFileDialog::getSaveFileName(this, "save", "out1.avi");
    if (name.isEmpty())
        return;

    string filename = name.toLocal8Bit().data();
    // 开始导出
    int w = ui->width->value();
    int h = ui->height->value();

    if (VideoThread::get()->StartSave(filename, w, h)) {
        isExport = true;
        ui->exportButton->setText("停止导出");
    }
}

/**
 * @brief 设置过滤器
 *
 */
void XVideo::on_pushButton_clicked()
{
    Filter::Get()->Clear();

    // 图像金字塔
    bool isPy = false;
    int down = ui->pydown->value();
    int up = ui->pyup->value();

    // 高斯金字塔大于0
    if (down > 0) {
        isPy = true;
        Filter::Get()->Add(Task{
            TASK_PYDOWN,
            {(double)down}});
        int w = VideoThread::get()->width;
        int h = VideoThread::get()->height;
        for (int i = 0; i < up; i++) {
            h *= 2;
            w *= 2;
        }
        ui->width->setValue(w);
        ui->height->setValue(h);
    }

    // 拉普拉斯金字塔大于0
    if (up > 0) {
        isPy = true;

        Filter::Get()->Add(Task{
            TASK_PYUP,
            {(double)up}});
        int w = VideoThread::get()->width;
        int h = VideoThread::get()->height;

        for (int i = 0; i < down; i++) {
            h /= 2;
            w /= 2;
        }

        ui->width->setValue(w);
        ui->height->setValue(h);
    }

    // 调整视频尺寸
    double w = ui->width->value();
    double h = ui->height->value();

    if (!isPy && ui->width->value() > 0 && ui->height->value() > 0) {
        Filter::Get()->Add(Task{
            TASK_RESIZE,
            {w, h}});
    }

    // 设置亮度和对比度
    if (ui->birght->value() > 0 || ui->contrast->value() > 1) {
        Filter::Get()->Add(Task{
            TASK_GAIN,
            {(double)ui->birght->value(), (double)ui->contrast->value()}});
    }

    // 图像旋转
    if (ui->rotate->currentIndex() == 1)
        Filter::Get()->Add(Task{TASK_ROTATE90});
    else if (ui->rotate->currentIndex() == 2)
        Filter::Get()->Add(Task{TASK_ROTATE180});
    else if (ui->rotate->currentIndex() == 3)
        Filter::Get()->Add(Task{TASK_ROTATE270});

    // 图像镜像
    if (ui->flip->currentIndex() == 1)
        Filter::Get()->Add(Task{TASK_FLIPY});
    else if (ui->flip->currentIndex() == 2)
        Filter::Get()->Add(Task{TASK_FLIPY});
    else if (ui->flip->currentIndex() == 3)
        Filter::Get()->Add(Task{TASK_FLIPXY});

    // 水印
    if (isMark) {
        double x = ui->mx->value();
        double y = ui->my->value();
        double a = ui->ma->value();
        Filter::Get()->Add(Task{TASK_MARK,
                                {x, y, a}});
    }
}

/**
 * @brief 滑动条拖动
 *
 * @param pos
 */
void XVideo::on_playSlider_valueChanged(int value)
{
    qDebug() << "value: " << value;
    VideoThread::get()->Seek((double)value / 1000.0);
}

