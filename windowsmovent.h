#ifndef WINDOWSMOVENT_H
#define WINDOWSMOVENT_H

#include <QWidget>

namespace Ui {
class WindowsMovent;
}
#include <QMouseEvent>

class WindowsMovent : public QWidget
{
    Q_OBJECT

public:
    WindowsMovent(QWidget *parent = 0);
    ~WindowsMovent();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    Ui::WindowsMovent *ui;
    bool m_move;
    QPoint m_startPoint;
    QPoint m_windowPoint;
};

#endif // WINDOWSMOVENT_H
