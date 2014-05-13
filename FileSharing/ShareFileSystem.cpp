#include "ShareFileSystem.h"
#include "FileTree.h"
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qmessagebox.h>
#include <QDebug>


ShareFileSystem::ShareFileSystem(){

    //Just for debugging
    root = new FileTree(FileInfo("/", -1, true), NULL);
    root->addDirectory("andrei", "/");
    root->addDirectory("taygun", "/");
    root->addDirectory("documents", "/andrei/");
    root->addDirectory("taydocuments", "/taygun/");
    root->addFile("C:/Users/Andrei/Documents/ip/file-sharing/etapa3.pdf", "/andrei/documents");

}


ShareFileSystem::~ShareFileSystem(void){
    delete(root);
}

FileTree* ShareFileSystem::getRoot(){
    
    return root;
}

void ShareFileSystem::addFile(const QString &realFullPath, FileTree *directory){

    int id = directory->addFile(realFullPath);
    fileIds[id] = realFullPath;
}

void ShareFileSystem::removeTree(FileTree *t){
    t->removeTree();
//    delete t;
}

void ShareFileSystem::createFolder(const QString &folderName, FileTree *parent){

    new FileTree(FileInfo(folderName, -1, true), parent); 
}

void ShareFileSystem::getFilePath(int index)
{
	//TODO
}

QByteArray ShareFileSystem::toByteArray(){

    QJsonObject json;

    json["root"] = root->toJson();
    json["totalIndex"] = FileInfo::total;
    
    QJsonArray fullNames;

    for (const std::pair<int, QString> &file : fileIds){
        QJsonObject fjson;
        fjson["id"] = file.first;
        fjson["fullname"] = file.second;
        fullNames.append(fjson);
    }

    json["fileIds"] = fullNames;

    QJsonDocument jdoc (json);
    QByteArray result = jdoc.toJson();
    return jdoc.toJson();
}

void ShareFileSystem::saveToFile(const QString &fileName){

    QFile f(fileName);

    if (!f.open(QIODevice::WriteOnly)){
        QMessageBox::warning(0,"Error","Couldn't save filesystem!");
        return;
    }

    f.write(toByteArray());
}

void ShareFileSystem::fillFromBytesArray(const QByteArray &bytes){

    QJsonDocument jdoc(QJsonDocument::fromJson(bytes));
    
    QJsonObject json = jdoc.object();
    
    root = new FileTree(json["root"].toObject(), NULL);
    FileInfo::total = json["totalIndex"].toInt();

    QJsonArray filesArray = json["fileIds"].toArray();

    for (const QJsonValue &v : filesArray){
        QJsonObject info = v.toObject();
        fileIds[info["id"].toInt()] = info["fullname"].toString();
    }
}

ShareFileSystem::ShareFileSystem(const QString &fileName){

    QFile f(fileName);

    if (!f.open(QIODevice::ReadOnly)){
        QMessageBox::warning(0,"Error","Couldn't save filesystem!");
        root = new FileTree(FileInfo("/", -1, true), NULL);
        return;
    }

    fillFromBytesArray(f.readAll());
}

ShareFileSystem::ShareFileSystem(const QByteArray &bytes){

    fillFromBytesArray(bytes);
}