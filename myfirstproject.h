#ifndef MYFIRSTPROJECT_H
#define MYFIRSTPROJECT_H

#include <QMainWindow>
#include "taskitem.h"
#include "dbsqlite.h"
#include <QListWidgetItem>
#include "taskitem.h"
#include "addpushbuttom.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMouseEvent>
#include <QMetaEnum>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MyFirstProject; }
QT_END_NAMESPACE

class AddPushButtom;

class MyFirstProject : public QMainWindow
{
    Q_OBJECT

public:
    MyFirstProject(QWidget *parent = nullptr);
    ~MyFirstProject();

    void resizeFixedSize();

    void clearTaskItem();

    void pushBackTaskItem(TaskItem &taskItem);

    void insertTaskItem(TaskItem &taskItem);

    void updateTimer();

    void on_update();

    void removeListWidget(TaskItem *taskItem);

    void showMessage(QString message);

    void showMessage_NewStatus(TaskItemModel taskItemModel);

    void initSystemTrayMenu();

    void systemTrayMenu();

private slots:
    void on_action_3_triggered();

    void on_addButtomPressed();

    void on_refreshButtomPressed();
    void on_actionasdf_triggered();


    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);

    void on_timer_updateStatus();

    void QTimerEvent(int timeId);

    void on_tray1_triggered();
    void on_tray2_triggered();

protected:
//    void mousePressEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);

public:
    Ui::MyFirstProject *ui;

    AddPushButtom addPushButtom;

    QSystemTrayIcon *mSysTrayIcon;

    QMenu *m_menu;
    QAction *m_action1;
    QAction *m_action2;

    bool m_move;
    QPoint m_startPoint;
    QPoint m_windowPoint;

    QList<QTimer*> timerList;
};
#endif // MYFIRSTPROJECT_H
