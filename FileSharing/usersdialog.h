#ifndef USERSDIALOG_H
#define USERSDIALOG_H

#include <QDialog>
#include "user.h"
#include <qlistwidget.h>
#include <qpushbutton.h>
#include "peer.h"


class UsersDialog : public QDialog
{
    Q_OBJECT

public:
    UsersDialog(User &u, QWidget *parent = 0);
    ~UsersDialog();
    Peer *selectedPeer;

public slots:
    void populateList();

private:
    User &myUser;
    QListWidget *userListWidget;
    QPushButton *okButton;
};

#endif // USERSDIALOG_H
