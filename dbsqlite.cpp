#include "dbsqlite.h"
//#include "QStringL"

dbSQLite::dbSQLite()
{

}

//dbSQLite::~dbSQLite()
//{
//    closeDataBase();
//}

bool dbSQLite::openDataBase()
{
    //建立并打开数据库
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("MyDataBase.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        qDebug() << "Succeed to connect database." ;
    }

    //创建表格
    QSqlQuery sql_query;
    if(!sql_query.exec("create table task(id INTEGER primary key AUTOINCREMENT, title var, task_type int ,task_status int ,valid int ,valid_unit int ,begin_date datetime ,valid_date datetime ,content text)"))
    {
        qDebug() << "Error: Fail to create table."<< sql_query.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
}

//void dbSQLite::createTable()
//{
//    //创建表格
//    QSqlQuery sql_query;
//    if(!sql_query.exec("create table student(id int primary key, name text, age int)"))
//    {
//        qDebug() << "Error: Fail to create table."<< sql_query.lastError();
//    }
//    else
//    {
//        qDebug() << "Table created!";
//    }
//}

//void dbSQLite::insertData()
//{

//    //插入数据
//    if(!sql_query.exec("INSERT INTO student VALUES(1, \"Wang\", 23)"))
//    {
//        qDebug() << sql_query.lastError();
//    }
//    else
//    {
//        qDebug() << "inserted Wang!";
//    }
//    if(!sql_query.exec("INSERT INTO student VALUES(2, \"Li\", 23)"))
//    {
//        qDebug() << sql_query.lastError();
//    }
//    else
//    {
//        qDebug() << "inserted Li!";
//    }

//    //修改数据
//    sql_query.exec("update student set name = \"QT\" where id = 1");
//    if(!sql_query.exec())
//    {
//        qDebug() << sql_query.lastError();
//    }
//    else
//    {
//        qDebug() << "updated!";
//    }

//    //查询数据
//    sql_query.exec("select * from student");
//    if(!sql_query.exec())
//    {
//        qDebug()<<sql_query.lastError();
//    }
//    else
//    {
//        while(sql_query.next())
//        {
//            int id = sql_query.value(0).toInt();
//            QString name = sql_query.value(1).toString();
//            int age = sql_query.value(2).toInt();
//            qDebug()<<QString("id:%1    name:%2    age:%3").arg(id).arg(name).arg(age);
//        }
//    }

//    //删除数据
//    sql_query.exec("delete from student where id = 1");
//    if(!sql_query.exec())
//    {
//        qDebug()<<sql_query.lastError();
//    }
//    else
//    {
//        qDebug()<<"deleted!";
//    }

//    //删除表格
//    sql_query.exec("drop table student");
//    if(sql_query.exec())
//    {
//        qDebug() << sql_query.lastError();
//    }
//    else
//    {
//        qDebug() << "table cleared";
//    }
//}

void dbSQLite::closeDataBase()
{
    //关闭数据库
    database.close();
}

void dbSQLite::insertTaskItem(TaskItemModel taskItemModel)
{
    QString sql = QString("INSERT INTO task VALUES(null, '%1', %2 ,%3 ,%4 ,%5 ,datetime('%6') ,datetime('%7') ,'%8')").arg(taskItemModel.title).arg(taskItemModel.taskType).arg(taskItemModel.taskStatus).arg(taskItemModel.valid).arg(taskItemModel.validUnit).arg(taskItemModel.beginTime.toString(Qt::ISODate)).arg(taskItemModel.validTime.toString(Qt::ISODate)).arg(taskItemModel.content);
    qDebug() << sql;
    //插入数据
    QSqlQuery sql_query;
    if(!sql_query.exec(sql))
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "insert success!";
    }
}

void dbSQLite::deleteTaskItem(QString id)
{
    QString sql = QString("delete from task where id = %1").arg(id);
    qDebug() << sql;
    //删除
    QSqlQuery sql_query;
    if(!sql_query.exec(sql))
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "delete success!";
    }
}

void dbSQLite::updateTaskItem(TaskItemModel taskItemModel)
{
    QString sql = QString("update task set title = '%1',task_type = %2 ,task_status = %3 ,valid = %4 ,valid_unit = %5 ,begin_date = datetime('%6') ,valid_date = datetime('%7') ,content = '%8' where id = %9").arg(taskItemModel.title).arg(taskItemModel.taskType).arg(taskItemModel.taskStatus).arg(taskItemModel.valid).arg(taskItemModel.validUnit).arg(taskItemModel.beginTime.toString(Qt::ISODate)).arg(taskItemModel.validTime.toString(Qt::ISODate)).arg(taskItemModel.content).arg(taskItemModel.id);
    qDebug() << sql;
    //修改数据
    QSqlQuery sql_query;
    if(!sql_query.exec(sql))
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "insert success!";
    }
}
QList<TaskItemModel> dbSQLite::queryTaskItems(int taskType ,int taskStatus)
{
    QList<TaskItemModel> taskItemModels;

    QString sql = "";

    if(taskType != -1)
    {
        sql += QString(" and task_type = %1 ").arg(taskType);
    }
    if(taskStatus != -1)
    {
        sql += QString(" and task_status = %1 ").arg(taskStatus);
    }

    qDebug() << sql;

    //查询数据
    QSqlQuery sql_query;
    sql_query.exec(QString("select * from task where 1 = 1 %1 order by valid_date").arg(sql));
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            TaskItemModel taskItemModel;
            taskItemModel.id = sql_query.value(0).toString();
            taskItemModel.title =sql_query.value(1).toString();
            taskItemModel.taskType =sql_query.value(2).toInt();
            taskItemModel.taskStatus =sql_query.value(3).toInt();
            taskItemModel.valid =sql_query.value(4).toInt();
            taskItemModel.validUnit =sql_query.value(5).toInt();
            taskItemModel.beginTime =QDateTime().fromString(sql_query.value(6).toString() ,Qt::ISODate);
            taskItemModel.validTime =QDateTime().fromString(sql_query.value(7).toString() ,Qt::ISODate);
            taskItemModel.content =sql_query.value(8).toString();

//            qDebug()<< sql_query.value(6).toString();
            taskItemModels.push_back(taskItemModel);
        }
    }

    return taskItemModels;
}
