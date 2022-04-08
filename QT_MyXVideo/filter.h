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
 * @LastEditTime : 2022-04-07 14:11:32
 * @FilePath     : /QT_MyXVideo/filter.h
 * @Description  :
 *
 * ******************************************
 */

#ifndef FILTER_H
#define FILTER_H

#include <QMutex>
#include <QObject>
#include <imagepro.h>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

using namespace std;

enum TaskType {
    TASK_NONE,
    TASK_GAIN,
    TASK_ROTATE90,
    TASK_ROTATE180,
    TASK_ROTATE270,
    TASK_FLIPX,
    TASK_FLIPY,
    TASK_FLIPXY,
    TASK_RESIZE,
    TASK_PYDOWN,
    TASK_PYUP,
    TASK_MARK,
};

struct Task {
    TaskType type;
    vector<double> para;
};

// 抽象类
class Filter : public QObject
{
    Q_OBJECT

  public:
    virtual cv::Mat filter(cv::Mat mat1, cv::Mat mat2) = 0;
    virtual void Add(Task task) = 0;
    virtual void Clear() = 0;
    static Filter *Get();
    virtual ~Filter();

  protected:
    Filter();
};

class CXFilter : public Filter
{
    Q_OBJECT

  public:
    CXFilter();
    ~CXFilter();
    vector<Task> tasks;
    QMutex mutex;

    virtual cv::Mat filter(cv::Mat mat1, cv::Mat mat2)
    {
        mutex.lock();
        ImagePro p;

        p.set(mat1, mat2);
        for (size_t i = 0; i < tasks.size(); i++) {
            switch (tasks[i].type) {
            case TASK_NONE:
                break;
            case TASK_GAIN:
                p.Gain(tasks[i].para[0], tasks[i].para[1]);
                break;
            case TASK_ROTATE90:
                p.Rotate90();
                break;
            case TASK_ROTATE180:
                p.Rotate180();
                break;
            case TASK_ROTATE270:
                p.Rotate270();
                break;
            case TASK_FLIPX:
                p.FlipX();
                break;
            case TASK_FLIPY:
                p.FlipY();
                break;
            case TASK_FLIPXY:
                p.FlipXY();
                break;
            case TASK_RESIZE:
                p.Resize(tasks[i].para[0], tasks[i].para[1]);
                break;
            case TASK_PYDOWN:
                p.PyDown(tasks[i].para[0]);
                break;
            case TASK_PYUP:
                p.PyUp(tasks[i].para[0]);
                break;
            case TASK_MARK:
                p.Mark(tasks[i].para[0], tasks[i].para[1], tasks[i].para[2]);
                break;
            default:
                break;
            }
        }
        cv::Mat re = p.Get();
        mutex.unlock();
        return re;
    }

    virtual void Add(Task task)
    {
        mutex.lock();
        tasks.push_back(task);
        mutex.unlock();
    }

    virtual void Clear()
    {
        mutex.lock();
        tasks.clear();
        mutex.unlock();
    }
};

#endif // !FILTER_H
