#ifndef DBSQLITE_H
#define DBSQLITE_H

#include <QMutex>
#include <QScopedPointer>
//添加头文件
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "taskitemmodel.h"

//dbSQLite* inst = Singleton<dbSQLite>::Instance();
class dbSQLite
{
public:
    dbSQLite();
//    ~dbSQLite();

public:
    QSqlDatabase database;

    bool openDataBase();
    void closeDataBase();

    void insertTaskItem(TaskItemModel taskItemModel);
    void deleteTaskItem(QString id);
    void updateTaskItem(TaskItemModel taskItemModel);
    QList<TaskItemModel> queryTaskItems(int taskType = -1,int taskStatus = -1);
};

#endif // DBSQLITE_H
