//"QMyListWidget.h"
#ifndef QMYLISTWIDGET_H
#define QMYLISTWIDGET_H

#include <QtGui>
#include <QListWidget>
#include <QApplication>
#include <QMouseEvent>

class QMyListWidget : public QListWidget
{
    Q_OBJECT

public:
    QMyListWidget(QWidget *parent);
    ~QMyListWidget();
protected:
//    //重写下面两个函数来完成从该部件中拖拽出去的操作.
//    void mousePressEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
//    //重写下面三个函数来完成接受外来拖拽的操作.
//    void dragEnterEvent(QDragEnterEvent *event);
//    void dragMoveEvent(QDragMoveEvent *event);
//    void dropEvent(QDropEvent *event);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    //记录拖拽的起点.
    QPoint m_dragPoint;
    //记录被拖拽的项.
    QListWidgetItem *m_dragItem;

    bool m_move;
    QPoint m_startPoint;
    QPoint m_windowPoint;
};

#endif // QMYLISTWIDGET_H
