//"QMyListWidget.cpp"
#include "QMyListWidget.h"
#include <QDropEvent>
#include <QWidget>
#include "myfirstproject.h"

QMyListWidget::QMyListWidget(QWidget *parent)
    : QListWidget(parent)
{
    //设置QListWidget接受拖拽.
    this->setAcceptDrops(true);
}

QMyListWidget::~QMyListWidget()
{

}
void QMyListWidget::mousePressEvent(QMouseEvent *event)
{
    //当鼠标左键点击时.
    if (event->button() == Qt::LeftButton)
    {
        m_move = true;
        //记录鼠标的世界坐标.
        m_startPoint = event->globalPos();
        //记录窗体的世界坐标.
//        m_windowPoint = this->frameGeometry().topLeft();
        m_windowPoint = qobject_cast<MyFirstProject*>(parentWidget()->parentWidget())->frameGeometry().topLeft();
    }
}
void QMyListWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //移动中的鼠标位置相对于初始位置的相对位置.
        QPoint relativePos = event->globalPos() - m_startPoint;
        //然后移动窗体即可.
//        this->move(m_windowPoint + relativePos );
        qobject_cast<MyFirstProject*>(parentWidget()->parentWidget())->move(m_windowPoint + relativePos );
    }
}
void QMyListWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //改变移动状态.
        m_move = false;
    }
}

////重写鼠标点击操作.
//void QMyListWidget::mousePressEvent(QMouseEvent *event)
//{
//    //确保左键拖拽.
//    if (event->button() == Qt::LeftButton)
//    {
//        //先保存拖拽的起点.
//        m_dragPoint = event->pos();
//        //保留被拖拽的项.
//        m_dragItem = this->itemAt(event->pos());
//    }
//    //保留原QListWidget部件的鼠标点击操作.
//    QListWidget::mousePressEvent(event);
//}

//void QMyListWidget::mouseMoveEvent(QMouseEvent *event)
//{
//    //确保按住左键移动.
//    if (event->buttons() & Qt::LeftButton)
//    {
//        QPoint temp = event->pos() - m_dragPoint;
//        //只有这个长度大于默认的距离,才会被系统认为是形成拖拽的操作.
//        if (temp.manhattanLength() > QApplication::startDragDistance())
//        {
//            QDrag *drag = new QDrag(this);
//            QMimeData *mimeData = new QMimeData;
//            mimeData->setText(m_dragItem->text());
//            drag->setMimeData(mimeData);
//            auto action = drag->exec(Qt::CopyAction | Qt::MoveAction);

//            if (action == (Qt::CopyAction) || (action == Qt::MoveAction))
//            {
//                //当成功拖拽后，删除拖拽项.
//                auto i = this->takeItem(this->row(m_dragItem));
//                delete i;
//            }
//        }
//    }
//    QListWidget::mouseMoveEvent(event);
//}

//void QMyListWidget::dragEnterEvent(QDragEnterEvent *event)
//{
//    //设置动作为移动动作.
//    event->setDropAction(Qt::MoveAction);
//    //然后接受事件.这个一定要写.
//    event->accept();
//}
//void QMyListWidget::dragMoveEvent(QDragMoveEvent *event)
//{
//    event->setDropAction(Qt::MoveAction);
//    event->accept();
//}
////当拖拽项被放下时的操作.
//void QMyListWidget::dropEvent(QDropEvent *event)
//{
//    QString str = event->mimeData()->text();
//    if (!str.isEmpty())
//    {
//        //找到当前鼠标位置在部件中的项.
//        auto item = this->itemAt(event->pos());
//        //
//        if (!item)
//            this->addItem(str);
//        else
//            this->insertItem(this->row(item),str);

//        event->setDropAction(Qt::MoveAction);
//        event->accept();
//    }
//}
