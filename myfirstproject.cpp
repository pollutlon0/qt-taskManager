#include "myfirstproject.h"
#include "ui_myfirstproject.h"
#include <QMetaEnum>
#include <QDebug>
#include "taskenum.h"
#include "Singleton.h"

MyFirstProject::MyFirstProject(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyFirstProject)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    //        ui->listWidget->setAttribute(Qt::WA_TransparentForMouseEvents);

    setMouseTracking(true);

    ui->listWidget->setMouseTracking(true);

    //窗口透明
    setAttribute(Qt::WA_TranslucentBackground, true);

    //设置窗口位置
    this->move(GetSystemMetrics(SM_CXSCREEN) - 400 ,+100);

    //新建QSystemTrayIcon对象
    mSysTrayIcon = new QSystemTrayIcon(this);

    //新建托盘要显示的icon
    QIcon icon = QIcon(":/resources/icon/icon_59081.ico");
    //将icon设到QSystemTrayIcon对象中
    mSysTrayIcon->setIcon(icon);
    //当鼠标移动到托盘上的图标时，会显示此处设置的内容
    mSysTrayIcon->setToolTip(QObject::trUtf8("任务列表"));
    mSysTrayIcon->show();

    //给QSystemTrayIcon添加槽函数
    connect(mSysTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));

    initSystemTrayMenu();

    dbSQLite* dbSql = Singleton<dbSQLite>::Instance();
    dbSql->openDataBase();

    //插入listWidget
    //关键代码;
    QListWidgetItem *newItem = new QListWidgetItem();       //创建一个newItem

    ui->listWidget->addItem(newItem);
    ui->listWidget->setItemWidget(newItem ,&addPushButtom);

    on_update();

    connect(&addPushButtom ,SIGNAL(addButtonPush()) ,this ,SLOT(on_addButtomPressed()) ,Qt::DirectConnection);

    //给是否移动的标志初始化为false.
    m_move = false;

    //    //背景图片
    //    QPixmap pixmap(":/resources/icon/back.jpg");

    //    QPalette palette;

    //    palette.setBrush(backgroundRole(), QBrush(pixmap));

    //    setPalette(palette);

    //定时任务

    //按钮组
//    ui->groupBox->setVisible(false);

}

MyFirstProject::~MyFirstProject()
{
    delete ui;
    delete mSysTrayIcon;

    delete m_menu;
    delete m_action1;
    delete m_action2;
}

void MyFirstProject::resizeFixedSize()
{
    int height = ui->listWidget->count() * 70;

    if(height > 270)
    {
        height = 270;
    }
    //设置窗口大小
    setFixedSize(400 ,height);
}

void MyFirstProject::on_action_3_triggered()
{
    //    ui->label->setText("菜单按下");
}

//void MyFirstProject::on_pushButton_clicked()
//{
//    //    QMetaEnum tenum = QMetaEnum::fromType<taskEnum::taskEnum1>();
//    //    qDebug() << tenum.isValid();//判断是否有效
//    //    qDebug() << tenum.name();//枚举名字
//    //    qDebug() << tenum.scope();//范围
//    //    //获取枚举数量，根据序号获取字符串
//    //    for(int i = 0; i < tenum.keyCount(); i++)
//    //            qDebug() << tenum.key(i);
//    //    //根据字符串获取值
//    //    qDebug() << tenum.keyToValue("one");
//    //    //根据值获取字符串
//    //    qDebug() << tenum.valueToKey(2);
//    //    //根据序号获取值
//    //    for(int i = 0; i < tenum.keyCount(); i++)
//    //        qDebug() << tenum.value(i);


//    TaskItem *buddy=new TaskItem();   //创建一个自己定义的信息类

//    //    buddy->title = ui->listWidget->count();
//    buddy->taskItemModel.title = "代办任务";
//    buddy->updateTaskItem();

//    addTaskItem(*buddy);
//}
void MyFirstProject::clearTaskItem()
{
    while(ui->listWidget->count() >1)
    {
        ui->listWidget->takeItem(0);
    }
}

void MyFirstProject::pushBackTaskItem(TaskItem &taskItem)
{
    //关键代码;
    QListWidgetItem *newItem = new QListWidgetItem();       //创建一个newItem

    ui->listWidget->addItem(newItem);
    ui->listWidget->setItemWidget(newItem ,&taskItem);
}

void MyFirstProject::insertTaskItem(TaskItem &taskItem)
{
    //关键代码;
    QListWidgetItem *newItem = new QListWidgetItem();       //创建一个newItem

    ui->listWidget->insertItem(ui->listWidget->count()-1,newItem);
    ui->listWidget->setItemWidget(newItem ,&taskItem);
}

void MyFirstProject::updateTimer()
{
    //停止计时器
    for(int i =0; i <timerList.count(); i++)
    {
        timerList.at(i)->stop();
    }
    timerList.clear();

    //创建新的计时器
    for(int i =0; i < ui->listWidget->count()-1 ;i++)
    {
        QMetaEnum tenum = QMetaEnum::fromType<taskEnum::taskStatus>();
        //计算定时时间
        QListWidgetItem *item = ui->listWidget->item(i);
        TaskItem *taskItem =(TaskItem*) ui->listWidget->itemWidget(item);

        if(taskItem->taskItemModel.taskStatus == tenum.keyToValue("underway"))
        {
            qint64 timerSec = QDateTime::currentDateTime().secsTo(taskItem->taskItemModel.validTime);
            qDebug() << "定时时间:" << timerSec;

            if(timerSec <= 0)
            {
                break;
            }

            QTimer *timer = new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT(on_timer_updateStatus()));
            timer->start(1000 * timerSec);            //1 分钟
            timerList.push_back(timer);
        }

    }
}
void MyFirstProject::on_update()
{
    dbSQLite* dbSql = Singleton<dbSQLite>::Instance();
    QList<TaskItemModel> taskItemModels = dbSql->queryTaskItems();

    clearTaskItem();

    for(int i =0; i < taskItemModels.count(); i++)
    {
        TaskItem *taskItem = new TaskItem(taskItemModels.at(i) ,this);
        insertTaskItem(*taskItem);
    }

    resizeFixedSize();
}

void MyFirstProject::on_addButtomPressed()
{
    TaskItemModel taskItemModel;
    TaskItem *taskItem = new TaskItem(taskItemModel ,this);
    insertTaskItem(*taskItem);

//    taskItem->taskItemInfo->updateTaskItemInfo();
//    taskItem->updateTaskItem();
    taskItem->taskItemInfo->show();
}

void MyFirstProject::on_refreshButtomPressed()
{
    on_update();
}

void MyFirstProject::removeListWidget(TaskItem *taskItem)
{
    for(int i =0; i < ui->listWidget->count() -1; i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        TaskItem *widget =(TaskItem*) ui->listWidget->itemWidget(item);

        if(taskItem->taskItemModel.id == widget->taskItemModel.id)
        {
            ui->listWidget->takeItem(i);
        }
    }
}

void MyFirstProject::on_actionasdf_triggered()
{
    //隐藏程序主窗口
    this->hide();

    //在系统托盘显示此对象
    mSysTrayIcon->show();
}

void MyFirstProject::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    //    qDebug() << reason;

    switch(reason){
    case QSystemTrayIcon::Context:
        systemTrayMenu();
        break;
    case QSystemTrayIcon::Trigger:
        //单击托盘图标
        this->show();
        break;
    case QSystemTrayIcon::DoubleClick:
        //双击托盘图标
        //双击后显示主程序窗口
        this->show();
        //        mSysTrayIcon->hide();
        break;
    default:
        break;
    }
}

void MyFirstProject::on_timer_updateStatus()
{
    qDebug() << "定时时间到";

    for(int i =0; i <ui->listWidget->count() -1; i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        TaskItem *widget =(TaskItem*) ui->listWidget->itemWidget(item);
        widget->updateTaskItem();
    }
}

void MyFirstProject::QTimerEvent(int timeId)
{
    qDebug() << "timeId" << timeId;
}

void MyFirstProject::showMessage(QString message)
{
    mSysTrayIcon->showMessage("",//消息窗口标题
                              message,//消息内容
                              QSystemTrayIcon::MessageIcon::Information,//消息窗口图标
                              5000);//消息窗口显示时长
}

void MyFirstProject::showMessage_NewStatus(TaskItemModel taskItemModel)
{
    QMetaEnum tenum = QMetaEnum::fromType<taskEnum::taskStatus>();

    QString message = QString("[%1]:%2").arg(taskItemModel.title).arg(tenum.valueToKey(taskItemModel.taskStatus));
    showMessage(message);
}

void MyFirstProject::initSystemTrayMenu()
{
    m_menu = new QMenu(this);
    m_action1 = new QAction(m_menu);
    m_action2 = new QAction(m_menu);

    m_action1->setText("Show Window");
    m_action2->setText("退出");

    m_menu->addAction(m_action1);
    m_menu->addAction(m_action2);

    connect(m_action1, &QAction::triggered, this, &MyFirstProject::on_tray1_triggered);
    connect(m_action2, &QAction::triggered, this, &MyFirstProject::on_tray2_triggered);

    mSysTrayIcon->setContextMenu(m_menu);
}

void MyFirstProject::systemTrayMenu()
{
    m_menu->show();
}

void MyFirstProject::on_tray1_triggered()
{
    showMessage("action 1");
}

void MyFirstProject::on_tray2_triggered()
{
    this->close();
}

//void MyFirstProject::mousePressEvent(QMouseEvent *event)
//{
//    //当鼠标左键点击时.
//    if (event->button() == Qt::LeftButton)
//    {
//        m_move = true;
//        //记录鼠标的世界坐标.
//        m_startPoint = event->globalPos();
//        //记录窗体的世界坐标.
//        m_windowPoint = this->frameGeometry().topLeft();
//    }
//}
//void MyFirstProject::mouseMoveEvent(QMouseEvent *event)
//{
//    if (event->buttons() & Qt::LeftButton)
//    {
//        //移动中的鼠标位置相对于初始位置的相对位置.
//        QPoint relativePos = event->globalPos() - m_startPoint;
//        //然后移动窗体即可.
//        this->move(m_windowPoint + relativePos );
//    }
//}
//void MyFirstProject::mouseReleaseEvent(QMouseEvent *event)
//{
//    if (event->button() == Qt::LeftButton)
//    {
//        //改变移动状态.
//        m_move = false;
//    }
//}
