#include "childwindow.h"

childWindow::childWindow(QWidget *parent) : QWidget(parent)
{
    w1.resize(600, 400);
    w1.setWindowTitle("childWindow");
    button_four.setText("返回主窗口");
}
