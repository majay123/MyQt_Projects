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

public slots:
    // 打开视频1按钮信号
    void Open();
    void SlidePress();
    void SlideRelease();
    // 滑动条拖动
    void SetPos(int pos);
    // 设置过滤器
    void Set();
    // 到处视频
    void Export();

    void Play();
    void Pause();

    void Mark();
private:
    Ui::XVideo *ui;
};
#endif // XVIDEO_H
