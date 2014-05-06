#ifndef DOWNLOADWINDOW_H
#define DOWNLOADWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_downloadwindow.h"

class DownloadWindow : public QMainWindow
{
    Q_OBJECT

public:
    DownloadWindow(QWidget *parent = 0);
    ~DownloadWindow();

private:
    Ui::DownloadWindowClass ui;
};

#endif // DOWNLOADWINDOW_H
