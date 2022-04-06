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
 * @Date         : 2022-02-10 15:40:32
 * @LastEditors  : MCD
 * @LastEditTime : 2022-02-14 11:03:27
 * @FilePath     : /test1/main.cpp
 * @Description  : 
 * 
 * ******************************************
 */

#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSplitter>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QApplication>
#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QListWidgetItem>
#include "main.moc"
#include "mylabel.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();
    //创建一个窗口，作为输入框的父窗口
    QWidget widget;
    //设置窗口的标题
    widget.setWindowTitle("QWidget窗口");
    widget.resize(500, 500);
    QListWidget listWidget(&widget);
    listWidget.resize(500, 400);
//    listWidget.setFont(QFont("宋体", 14));
    listWidget.addItem("C语言中文网");
    listWidget.addItem("http://c.biancheng.net");
    listWidget.addItem(new QListWidgetItem("Qt教程"));
	// listWidget.setCurrentRow(0);

    QMyLabel print;
    print.setText("选中内容");
    print.setParent(&widget);
    print.resize(500, 100);
    print.move(0, 400);
    print.setAlignment(Qt::AlignCenter);

    // QObject::connect(&listWidget, &QListWidget::currentTextChanged, &print, &QLabel::setText);
    QObject::connect(&listWidget, &QListWidget::itemClicked, &print, &QMyLabel::rsetText);

	// listWidget.setCurrentRow(0);
    widget.show();

    // QSplitter splitter;

	// //<1> 使用QStringList做内部模型
	// QListWidget * listLeft = new QListWidget();
	// QStringList list;
	// list << "98" << "99" << "100" << "101" << "102";
	// listLeft->addItems(list);
	// listLeft->sortItems();

	// //<2> 使用QListWidgetItem做内部模型
	// QListWidget * listRight = new QListWidget();
	// for (int i = 98; i < 103; i++) 
	// {
	// 	QWidget *w = new QWidget(listRight);
	// 	QHBoxLayout *layout = new QHBoxLayout(w);
	// 	QPushButton *button = new QPushButton("push button", w);
	// 	QCheckBox *check = new QCheckBox(QString::number(i), w);
	// 	layout->setContentsMargins(50, 0, 0, 0);
	// 	layout->addWidget(check);
	// 	layout->addWidget(button);
	// 	w->setLayout(layout);

	// 	QListWidgetItem * item = new QListWidgetItem;
	// 	item->setData(Qt::DisplayRole, i);
	// 	item->setSizeHint(QSize(200, 28));
	// 	listRight->addItem(item);
	// 	listRight->setItemWidget(item, w);
	// }
	// listRight->sortItems();

	// // 显示
	// splitter.addWidget(listLeft);
	// splitter.addWidget(listRight);
	// splitter.show();

    return a.exec();
}
