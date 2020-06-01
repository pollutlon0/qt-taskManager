#include "myfirstproject.h"

#include <QApplication>
#include "Singleton.h"
#include"windows.h"

HWND findDesktopIconWnd();
static BOOL enumUserWindowsCB(HWND hwnd, LPARAM lParam);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //桌面句柄
    MyFirstProject* w = new MyFirstProject();

    //    HWND hdesktop = findDesktopIconWnd();

    WId wid = w->winId();

    HWND desktopHwnd = findDesktopIconWnd();
    if (desktopHwnd)
    {
        SetParent((HWND)wid, desktopHwnd);
    }


    //    SetParent((HWND)wid, desktopHwnd);

    //设置为父窗口
    w->show();

    return a.exec();
}



static BOOL enumUserWindowsCB(HWND hwnd, LPARAM lParam)
{
    long wflags = GetWindowLong(hwnd, GWL_STYLE);
    if (!(wflags & WS_VISIBLE)) return TRUE;

    HWND sndWnd;
    if (!(sndWnd = FindWindowEx(hwnd, NULL, L"SHELLDLL_DefView", NULL)))
        return TRUE;

    HWND targetWnd;
    if (!(targetWnd = FindWindowEx(sndWnd, NULL, L"SysListView32", L"FolderView")))
        return TRUE;

    HWND* resultHwnd = (HWND*)lParam;
    *resultHwnd = targetWnd;
    //*resultHwnd = hwnd;//set to workerW
    return FALSE;
}

HWND findDesktopIconWnd()
{
    HWND resultHwnd = NULL;
    EnumWindows((WNDENUMPROC)enumUserWindowsCB, (LPARAM)&resultHwnd);
    return resultHwnd;
}
