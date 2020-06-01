#include "taskiteminfo.h"
#include "ui_taskiteminfo.h"

#include "taskenum.h"
#include "dbsqlite.h"
#include "singleton.h"

TaskItemInfo::TaskItemInfo(QWidget *parent ,TaskItemModel *initTaskItemModel) :
    QWidget(parent),
    ui(new Ui::TaskItemInfo)
{
    ui->setupUi(this);
    setParent(parent);
    this->move(GetSystemMetrics(SM_CXSCREEN) - 420 ,+100);

    taskItemModel = initTaskItemModel;

    updateTaskItemInfo();
    setVisible(false);
}

TaskItemInfo::~TaskItemInfo()
{
    delete ui;
}


void TaskItemInfo::updateTaskItemInfo()
{
    ui->titileLineEdit->setText(taskItemModel->title);
    ui->contentTextEdit->setText(taskItemModel->content);
    ui->typeComboBox->setCurrentIndex(taskItemModel->taskType);
    ui->beginDateTimeEdit->setDateTime(taskItemModel->beginTime);
    ui->validDateTimeEdit_2->setDateTime(taskItemModel->validTime);
    ui->statusComboBox->setCurrentIndex(taskItemModel->taskStatus);
    ui->valid->setText(QString("%1").arg(taskItemModel->valid));
    ui->validUnit->setCurrentIndex(taskItemModel->validUnit);

    calcValidDateTime();
    saveItemInfoData();
}

void TaskItemInfo::on_save_clicked()
{
    saveItemInfoData();

    //保存数据
    dbSQLite* dbSql = Singleton<dbSQLite>::Instance();
    if(taskItemModel->id == "")
    {
        dbSql->insertTaskItem(*taskItemModel);
    }
    else
    {
        dbSql->updateTaskItem(*taskItemModel);
    }

    emit taskItemInfoChanged();
    this->setVisible(false);
}

QDateTime TaskItemInfo::calcValidDateTime()
{
    QDateTime qDateTime;

    //小时 天 周 月
    if(ui->validUnit->currentIndex() == 0)
    {
        qDateTime = ui->beginDateTimeEdit->dateTime().addSecs(ui->valid->text().toInt() * 60 * 60);
    }
    else if(ui->validUnit->currentIndex() == 1)
    {
        qDateTime = ui->beginDateTimeEdit->dateTime().addDays(ui->valid->text().toInt());
    }
    else if(ui->validUnit->currentIndex() == 2)
    {
        qDateTime = ui->beginDateTimeEdit->dateTime().addDays(ui->valid->text().toInt() * 7);
    }
    else if(ui->validUnit->currentIndex() == 3)
    {
        qDateTime = ui->beginDateTimeEdit->dateTime().addMonths(ui->valid->text().toInt());
    }
    ui->validDateTimeEdit_2->setDateTime(qDateTime);

    QMetaEnum tenum = QMetaEnum::fromType<taskEnum::taskStatus>();
    //判断任务状态
    if(ui->statusComboBox->currentIndex() != tenum.keysToValue("fnish"))
    {
        QDateTime curDateTime =QDateTime::currentDateTime();
        //
        qDebug() << ui->validDateTimeEdit_2->dateTime().secsTo(curDateTime);
        if(ui->validDateTimeEdit_2->dateTime().secsTo(curDateTime) >= 0)
        {
            ui->statusComboBox->setCurrentIndex(tenum.keyToValue("overTime"));
        }
        else if(ui->beginDateTimeEdit->dateTime() < curDateTime)
        {
            ui->statusComboBox->setCurrentIndex(tenum.keyToValue("underway"));
        }
        else if(ui->beginDateTimeEdit->dateTime() >= curDateTime)
        {
            ui->statusComboBox->setCurrentIndex(tenum.keyToValue("ready"));
        }
    }
    return qDateTime;
}

void TaskItemInfo::setStatus(int status)
{
    ui->statusComboBox->setCurrentIndex(status);
    this->taskItemModel->taskStatus = status;
}

void TaskItemInfo::on_valid_textChanged(const QString &arg1)
{
    calcValidDateTime();
}

void TaskItemInfo::on_validUnit_editTextChanged(const QString &arg1)
{
    calcValidDateTime();
}

void TaskItemInfo::on_validUnit_currentIndexChanged(int index)
{
    calcValidDateTime();
}

void TaskItemInfo::on_beginDateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    calcValidDateTime();
}

void TaskItemInfo::saveItemInfoData()
{
    taskItemModel->title = ui->titileLineEdit->text();
    taskItemModel->taskStatus = ui->statusComboBox->currentIndex();
    taskItemModel->taskType = ui->typeComboBox->currentIndex();
    taskItemModel->valid = ui->valid->text().toInt();
    taskItemModel->validUnit = ui->validUnit->currentIndex();
    taskItemModel->beginTime = ui->beginDateTimeEdit->dateTime();
    taskItemModel->validTime = ui->validDateTimeEdit_2->dateTime();
    taskItemModel->content = ui->contentTextEdit->toPlainText();
}
