#ifndef TASKITEMINFO_H
#define TASKITEMINFO_H

#include <QWidget>
#include <taskitemmodel.h>
#include <windows.h>


namespace Ui {
class TaskItemInfo;
}

class TaskItemInfo : public QWidget
{
    Q_OBJECT

public:
    explicit TaskItemInfo(QWidget *parent = nullptr ,TaskItemModel *initTaskItemModel =nullptr);
    ~TaskItemInfo();

    void updateTaskItemInfo();

    QDateTime calcValidDateTime();

    void setStatus(int status);

    void saveItemInfoData();
private slots:
    void on_save_clicked();

    void on_valid_textChanged(const QString &arg1);

    void on_validUnit_editTextChanged(const QString &arg1);

    void on_validUnit_currentIndexChanged(int index);

    void on_beginDateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

signals:
    void taskItemInfoChanged();

private:
    Ui::TaskItemInfo *ui;

public:
    QString id;
    TaskItemModel *taskItemModel;
};

#endif // TASKITEMINFO_H
