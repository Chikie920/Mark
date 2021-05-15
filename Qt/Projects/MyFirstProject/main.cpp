#include "widget.h" //包含自定义窗口类

#include <QApplication> //应用程序类
#include <QWidget> //窗口控件基类
#include <QPushButton> //添加按钮头文件

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //有且只有一个应用程序类的对象
    Widget w; //Widget继承Qwidget类
    w.resize(600, 400); //设置窗口大小
    w.setWindowTitle("Hello Qt"); //窗口标题
    QPushButton button_one;
    button_one.setText("This is a button");
    button_one.setParent(&w); //设置按钮父对象，父对象显示时，子对象自动显示，窗口关闭时和父类一起析构
    button_one.move(100, 100);
    QPushButton button_two(&w); //通过构造函数传参设置父对象
    button_two.setText("button_two");


    w.show(); //界面显示，窗口默认时隐藏的，需要人为显示
    return a.exec(); //让程序一直执行，等待用户操作，点击x触发消息关闭
}
