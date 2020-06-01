#ifndef TASKITEMMODEL_H
#define TASKITEMMODEL_H

#include <QMetaType>
#include <QString>
#include <QDateTime>

class TaskItemModel
{
public:
    TaskItemModel();

    QString createId();

public:
    QString id = "";
    QString title   = "标题";
    int taskType    = 0;
    int taskStatus  = 0;
    int valid       = 1;
    int validUnit   = 0;
    QDateTime   beginTime   = QDateTime::currentDateTime();
    QDateTime   validTime   = QDateTime::currentDateTime();
    QString content = "";
};

//Q_DECLARE_METATYPE(TaskItemModel);

#endif // TASKITEMMODEL_H
