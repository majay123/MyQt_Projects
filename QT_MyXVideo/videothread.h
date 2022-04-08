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
 * @Date         : 2022-04-07 11:03:08
 * @LastEditors  : MCD
 * @LastEditTime : 2022-04-07 16:20:54
 * @FilePath     : /QT_MyXVideo/videothread.h
 * @Description  :
 *
 * ******************************************
 */

#ifndef VIDEOTHREAD
#define VIDEOTHREAD

#include <QMutex>
#include <QObject>
#include <QThread>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

class VideoThread : public QThread
{
    Q_OBJECT

  public:
    int fps = 0;
    int width = 0;
    int height = 0;

    static VideoThread *get()
    {
        static VideoThread vt;
        return &vt;
    }

    // 打开一号视频
    bool Open(const std::string file);

    void Play()
    {
        mutex.lock();
        isPlay = true;
        mutex.unlock();
    }

    void Pause()
    {
        mutex.lock();
        isWrite = true;
        mutex.unlock();
    }

    // 返回当前播放的位置
    double GetPos();

    // 跳转视频
    bool Seek(int frame);
    bool Seek(double pos);

    // 开始保存视频
    bool StartSave(const string filename, int width = 0, int height = 0);

    // 停止保存视频，写入视频帧的索引
    void StopSave();

    // 添加水印
    void SetMark(cv::Mat mark)
    {
        mutex.lock();
        this->mark = mark;
        mutex.unlock();
    }

    ~VideoThread();

    // 线程入口函数
    void run();

  protected:
    // 是否开始写视频
    bool isPlay = false;
    bool isWrite = false;

    cv::Mat mark;

    VideoThread();
    QMutex mutex;

  signals:
    // 显示原视频1图像
    void ViewImage1(cv::Mat mat);

    // 显示目标图像
    void ViewDes(cv::Mat mat);
};

#endif // !VIDEOTHREAD
