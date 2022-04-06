#ifndef XVIDEO_H
#define XVIDEO_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class XVideo; }
QT_END_NAMESPACE

class XVideo : public QWidget
{
    Q_OBJECT

public:
    XVideo(QWidget *parent = nullptr);
    ~XVideo();

private:
    Ui::XVideo *ui;
};
#endif // XVIDEO_H
