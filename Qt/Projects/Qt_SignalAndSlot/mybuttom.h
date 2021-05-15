#ifndef MYBUTTOM_H
#define MYBUTTOM_H

#include <QWidget>
#include <QPushButton>

class MyButtom : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButtom(QWidget *parent = nullptr);
    void changeText();

signals:


};

#endif // MYBUTTOM_H
