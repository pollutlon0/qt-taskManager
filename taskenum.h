#ifndef TASKENUM_H
#define TASKENUM_H

#include <QObject>
#include <QMetaEnum>

class taskEnum : public QObject
{
    Q_OBJECT
public:
    explicit taskEnum(QObject *parent = nullptr);

    enum taskType{
        work = 0,
        task
    };

    enum taskStatus{
        ready = 0,
        underway,
        overTime,
        fnish
    };

    Q_ENUM(taskType)
    Q_ENUM(taskStatus)
signals:

};

#endif // TASKENUM_H
