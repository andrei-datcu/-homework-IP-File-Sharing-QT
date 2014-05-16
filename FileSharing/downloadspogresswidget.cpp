#include "downloadspogresswidget.h"
#include <qprogressbar.h>
#include <qmessagebox.h>

DownloadsPogressWidget::DownloadsPogressWidget(QWidget *parent)
    : QTableWidget(0, 2, parent){

    QStringList tableHeaders;

    tableHeaders.append("File name");
    tableHeaders.append("Donwload progress");
    setHorizontalHeaderLabels(tableHeaders);
    setMinimumHeight(200);
}


void DownloadsPogressWidget::addFileProgressTrack (const QString &fileName,
                                                   const int filesize,
                                                   ClientFileThread *dThread){

    workingThreads[dThread] = this->rowCount();
    insertRow(this->rowCount());

    QTableWidgetItem *it = new QTableWidgetItem(fileName);
    setItem(this->rowCount() - 1, 0, it);
    
    QProgressBar *pb = new QProgressBar(this);
    pb->setMaximum(filesize);
    pb->setMinimum(0);
    setCellWidget(this->rowCount() - 1, 1, pb);

    connect(dThread, SIGNAL(gotBytes(int)), pb, SLOT(setValue(int)));
    connect(dThread, SIGNAL(ClientFileThread::connectionFailed(const QString&)), this, SLOT(showDisconnectError(const QString&)), Qt::BlockingQueuedConnection);
    connect(dThread, &ClientFileThread::finished, [this](){
        removeMutex.lock();
        ClientFileThread *sender = (ClientFileThread*) QObject::sender();
        removeRow(workingThreads[sender]);
        workingThreads.erase(sender);
        removeMutex.unlock();
    });
}


DownloadsPogressWidget::~DownloadsPogressWidget()
{

}

void DownloadsPogressWidget::showDisconnectError(const QString &path){

     QMessageBox::critical(NULL, "Error", "Connection failed! File " + path + " could not be downloaded. Probably user exited");
}