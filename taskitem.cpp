#include "taskitem.h"
#include "ui_taskitem.h"

#include "taskiteminfo.h"
#include "taskenum.h"
#include "myfirstproject.h"
#include "singleton.h"

TaskItem::TaskItem(TaskItemModel taskItemModel ,MyFirstProject *mainMenu, QWidget *parent)  :
    QWidget(parent),
    ui(new Ui::TaskItem)
{
    ui->setupUi(this);
    this->mainMenu = mainMenu;
    this->taskItemModel = taskItemModel;

    taskItemInfo = new TaskItemInfo(parent ,&this->taskItemModel);
    taskItemInfo->setVisible(false);

    QMetaObject::Connection reult = connect(taskItemInfo ,SIGNAL(taskItemInfoChanged()) ,this ,SLOT(on_taskItemInfoChanged()) ,Qt::DirectConnection);

    oldTaskStutas = taskItemModel.taskStatus;
    updateTaskItem();
}

TaskItem::~TaskItem()
{
    delete ui;
    delete taskItemInfo;
}

void TaskItem::updateTaskItem()
{
    ui->taskDetail->setText(this->taskItemModel.title);

    this->taskItemInfo->updateTaskItemInfo();

    setItemColor();

    if(oldTaskStutas != this->taskItemModel.taskStatus)
    {
        dbSQLite* db = Singleton<dbSQLite>::Instance();
        db->updateTaskItem(this->taskItemModel);

        mainMenu->showMessage_NewStatus(this->taskItemModel);
    }
    oldTaskStutas = taskItemModel.taskStatus;

    this->mainMenu->updateTimer();
    this->mainMenu->resizeFixedSize();
}

void TaskItem::on_taskDetail_clicked()
{
    //    taskItemDetail->updateTaskItemDetail(this);
    //    taskItemDetail->setVisible(true);

    displayTaskItemInfo();
    //    taskItemDetail.update
}

void TaskItem::on_taskItemInfoChanged()
{
    updateTaskItem();
    //    emit updateMainMenu();
    //    MyFirstProject* w = Singleton<MyFirstProject>::Instance();
    //    w->update();
}
void TaskItem::displayTaskItemInfo()
{
    taskItemInfo->updateTaskItemInfo();
    taskItemInfo->show();
}

void TaskItem::on_deleteTask_stateChanged(int arg1)
{
    //勾上是2
    if(arg1 == 2)
    {
        dbSQLite *sql = Singleton<dbSQLite>::Instance();
        sql->deleteTaskItem(this->taskItemModel.id);

        setItemColor(false);
        mainMenu->removeListWidget(this);
    }
}

void TaskItem::on_finshTask_stateChanged(int arg1)
{
    QMetaEnum tenum = QMetaEnum::fromType<taskEnum::taskStatus>();

    //勾上是2
    if(arg1 == 2)
    {
        this->taskItemInfo->setStatus(tenum.keyToValue("fnish"));
    }
    else if(arg1 == 0)
    {
        this->taskItemInfo->setStatus(tenum.keyToValue("underway"));
    }
    updateTaskItem();
    //    mainMenu->showMessage_NewStatus(this->taskItemModel);

    dbSQLite* db = Singleton<dbSQLite>::Instance();
    db->updateTaskItem(this->taskItemModel);
}

void TaskItem::setItemColor(bool valid)
{
    //设置任务颜色
    //rgb(118, 118, 118)    灰色
    //rgb(225, 225, 225)    白色
    //rgb(231, 105, 111)    红色
    //rgb(49, 222, 40)      绿色
    //rgb(219, 221, 65)     黄色
    QMetaEnum tenum = QMetaEnum::fromType<taskEnum::taskStatus>();
    QString itemColor = "white";
    if(valid == false)
    {
        itemColor = "rgb(118, 118, 118)";
    }
    else if(this->taskItemModel.taskStatus == tenum.keyToValue("ready"))
    {
        itemColor = "rgb(225, 225, 225)";
    }
    else if(this->taskItemModel.taskStatus == tenum.keysToValue("underway"))
    {
        itemColor = "rgb(219, 221, 65)";
    }
    else if(this->taskItemModel.taskStatus == tenum.keysToValue("overTime"))
    {
        itemColor = "rgb(231, 105, 111)";
    }
    else if(this->taskItemModel.taskStatus == tenum.keysToValue("fnish"))
    {
        itemColor = "rgb(49, 222, 40)";
        ui->finshTask->setChecked(true);
    }

    this->setStyleSheet(QString("QWidget{  \n" \
                                "    background-color: %1;  \n" \
                                "    color:black;  \n" \
                                "    border:none;\n" \
                                "\t\theight: 30px;  \n" \
                                "}    \n"
                                "  \n" \
                                "QWidget::item:hover{  \n" \
                                "    background:rgb(252,240,193)  \n" \
                                "}  \n" \
                                "  \n" \
                                "QWidget::item:selected{  \n" \
                                "    background:rgb(252,233,161);  \n" \
                                "    color:black;  \n" \
                                "}\n" \
                                "QWidget::QCheckBox\n" \
                                "{\n" \
                                "\topacity: 0;\n" \
                                "\tborder:none;\n" \
                                "}").arg(itemColor));
}
