#include "mybutton.h"

MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{

}

void MyButton::changeText()
{
    static QString temp = this->text();
    QString target = "123";
    if(target != this->text()){
        this->setText(target);
    } else {
        this->setText(temp);
    }
}
