#ifndef TASKITEM_H
#define TASKITEM_H

#include <QWidget>
#include <QDate>
#include <QMetaEnum>

#include "taskiteminfo.h"
#include "taskitemmodel.h"

#include "taskiteminfo.h"
#include <QListWidget>
#include <QListWidgetItem>

namespace Ui {
class TaskItem;
}

class MyFirstProject;

class TaskItem : public QWidget
{
    Q_OBJECT

public:
    explicit TaskItem(TaskItemModel askItemModel ,MyFirstProject *mainMenu,QWidget *parent = nullptr );
    ~TaskItem();

    void updateTaskItem();
    void displayTaskItemInfo();
    void setItemColor(bool valid = true);
private slots:
    void on_taskDetail_clicked();

    void on_taskItemInfoChanged();

    void on_deleteTask_stateChanged(int arg1);
    void on_finshTask_stateChanged(int arg1);
signals:
    void updateMainMenu();
private:
    Ui::TaskItem *ui;

//    QWidget *parent;

    MyFirstProject *mainMenu;

    int oldTaskStutas;
public:
    TaskItemModel taskItemModel;

    TaskItemInfo * taskItemInfo;
};

#endif // TASKITEM_H
