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
 * @Date         : 2022-04-07 15:16:36
 * @LastEditors  : MCD
 * @LastEditTime : 2022-04-07 15:17:46
 * @FilePath     : /QT_MyXVideo/filter.cpp
 * @Description  : 
 * 
 * ******************************************
 */

#include <QThread>
#include <QMutex>
#include <QObject>

#include "imagepro.h"
#include "filter.h"

using namespace cv;

Filter::Filter()
{

}

Filter::~Filter()
{

}

CXFilter::CXFilter()
{

}

CXFilter::~CXFilter()
{

}

Filter *Filter::Get()
{
    static CXFilter cx;
    return &cx;
}