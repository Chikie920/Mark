#include "mybuttom.h"

MyButtom::MyButtom(QWidget *parent) : QPushButton(parent)
{

}

void MyButtom::changeText()
{
    static QString temp = this->text();
    QString target = "123";
    if(target != this->text()){
        this->setText(target);
    } else {
        this->setText(temp);
    }
}
