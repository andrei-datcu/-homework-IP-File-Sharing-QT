#ifndef DOWNLOADSPOGRESSWIDGET_H
#define DOWNLOADSPOGRESSWIDGET_H

#include <QTableWidget>
#include "clientfilethread.h"
#include <map>
#include <qmutex.h>

class DownloadsPogressWidget : public QTableWidget
{
    Q_OBJECT

public:
    DownloadsPogressWidget(QWidget *parent = 0);
    ~DownloadsPogressWidget();

    void addFileProgressTrack (const QString &fileName, const int filesize,
        ClientFileThread *dThread);


private:
    std::map<ClientFileThread*, int> workingThreads;
    QMutex removeMutex;

    private slots:
        void showDisconnectError(const QString &path);
};

#endif // DOWNLOADSPOGRESSWIDGET_H
