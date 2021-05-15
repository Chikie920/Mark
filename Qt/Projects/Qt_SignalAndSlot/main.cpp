#include "widget.h"
#include "mybutton.h"
#include <QApplication>
#include <QPushButton>
#include "childwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w; //执行Widget的构造函数
    w.resize(600, 400);
    w.setWindowTitle("Hello Qt");

    QPushButton button_one(&w);
    button_one.move(25, 25);
    button_one.setText("Close");
    QObject::connect(&button_one, &QPushButton::clicked, &w, &Widget::close);
    /*
     *参一：信号发出者地址
     *参二：处理的信号 发送者的类名::信号名字
     *参三：信号接受者地址
     *参四：槽函数，信号接受者类的处理函数 &接收的类名::槽函数名字
     */

    /*
     *槽函数可以是任意的成员函数，普通全局函数，静态函数
     *槽函数需要和信号一致(参数, 返回值）
     *信号没有返回值，所槽函数一定没有返回值
     */

    MyButton button_two(&w);
    button_two.setText("Change");
    QObject::connect(&button_two, &QPushButton::clicked, &button_two, &MyButton::changeText);
    //由于参三与参四所属的类要一致，这里创建了一个buttom的类，参四函数为槽函数，即用于处理信号的函数

    w.show();
    return a.exec();
}
