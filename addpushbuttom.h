#ifndef ADDPUSHBUTTOM_H
#define ADDPUSHBUTTOM_H

#include <QWidget>

namespace Ui {
class AddPushButtom;
}

class MyFirstProject;
class AddPushButtom : public QWidget
{
    Q_OBJECT

public:
    explicit AddPushButtom(QWidget *parent = nullptr);
    ~AddPushButtom();

private slots:
    void on_pushButton_clicked();


signals:
    void addButtonPush();

private:
    Ui::AddPushButtom *ui;

    MyFirstProject *mainMenu;
};

#endif // ADDPUSHBUTTOM_H
