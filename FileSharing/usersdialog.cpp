#include "usersdialog.h"
#include <qlayout.h>
#include <qlistwidget.h>

UsersDialog::UsersDialog(User &u, QWidget *parent)
    : myUser(u), QDialog(parent){

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    userListWidget = new QListWidget(this);
    mainLayout->addWidget(userListWidget);

    okButton = new QPushButton("Ok", this);
    mainLayout->addWidget(okButton);
    connect(okButton, &QAbstractButton::clicked, [this](){

        for (auto item : userListWidget->selectedItems()){
            selectedPeer = new Peer(item->text(), myUser.userList[item->text()]);
            setResult(QDialog::Accepted);
            close();
            return;
        }


    });
}

void UsersDialog::populateList(){

    userListWidget->clear();
    for (auto uname : myUser.userList.keys()){
        QListWidgetItem *item = new QListWidgetItem(uname, userListWidget); 
    }
}

UsersDialog::~UsersDialog()
{

}
