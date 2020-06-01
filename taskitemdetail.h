#ifndef TASKITEMDETAIL_H
#define TASKITEMDETAIL_H

#include <QWidget>
#include "taskitem.h"

namespace Ui {
class TaskItemDetail;
}

class TaskItemDetail : public QWidget
{
    Q_OBJECT

public:
    explicit TaskItemDetail(QWidget *parent = nullptr);
    ~TaskItemDetail();

    void updateTaskItemDetail(TaskItem taskItem);
private:
    Ui::TaskItemDetail *ui;
};

#endif // TASKITEMDETAIL_H
