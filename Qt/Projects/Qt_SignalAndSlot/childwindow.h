#ifndef CHILDWINDOW_H
#define CHILDWINDOW_H

#include <QWidget>
#include <QPushButton>

class childWindow : public QWidget
{
    Q_OBJECT
public:
    explicit childWindow(QWidget *parent = nullptr);

signals:
    /*信号必须由signals关键字来声明
     * 信号没有返回值，但可以有参数
     *信号就是函数的声明，只需声明无需定义
     *使用
     */

private:
    QPushButton button_four;

};

#endif // CHILDWINDOW_H
