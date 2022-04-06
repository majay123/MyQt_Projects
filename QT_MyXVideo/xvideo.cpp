#include "xvideo.h"
#include "./ui_xvideo.h"

XVideo::XVideo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::XVideo)
{
    ui->setupUi(this);
}

XVideo::~XVideo()
{
    delete ui;
}

