#include "addpushbuttom.h"
#include "ui_addpushbuttom.h"

AddPushButtom::AddPushButtom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddPushButtom)
{
    ui->setupUi(this);
}

AddPushButtom::~AddPushButtom()
{
    delete ui;
}

void AddPushButtom::on_pushButton_clicked()
{
    emit addButtonPush();
}
