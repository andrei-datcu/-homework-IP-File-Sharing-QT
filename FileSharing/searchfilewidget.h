#ifndef SEARCHFILEWIDGET_H
#define SEARCHFILEWIDGET_H

#include <QWidget>
#include <qlineedit.h>
#include <qtablewidget.h>
#include <qpushbutton.h>
#include "user.h"
#include "downloadspogresswidget.h"

class SearchFileWidget : public QWidget
{
    Q_OBJECT

public:
    SearchFileWidget(User &u, DownloadsPogressWidget *pw, QWidget *parent = 0);
    ~SearchFileWidget();

private:
    User &myUser;
    QLineEdit *searchWordEdit;
    QPushButton *searchButton;
    QTableWidget *resultListWidget;
    DownloadsPogressWidget *progressWidget;
};

#endif // SEARCHFILEWIDGET_H
