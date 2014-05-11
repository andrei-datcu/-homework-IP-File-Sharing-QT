#include "FileTree.h"
#include <qstringlist.h>
#include <vector>
#include <algorithm>
#include <qjsonarray.h>

const QString FileTree::delim = "/";
int FileInfo::total = 0;

FileTree::FileTree(FileInfo finfo, FileTree* parent) :
    finfo(finfo), parent(parent){

    if (parent != NULL) {
        parent->addChild(this);
    }
}

void FileTree::addChild(FileTree *child) {
    children.push_back(child);
}

FileTree* FileTree::childAt(int index){
    return children.at(index);
}

void FileTree::addFileIt(const FileInfo &finfo,
                         const QList<QString>::iterator &begin,
                         const QList<QString>::iterator &end) {

    if (begin == end) { //Daca lista e goala begin==end
        new FileTree(finfo, this);
        return;
    }

    for(FileTree *ch : children) {
        if (ch->getName() == *begin)
            return ch->addFileIt(finfo, begin + 1, end);
    }

}

int FileTree::addFile(const QString &realPath,
                       const QString &fullPath) {
    QStringList list = fullPath.split(delim, QString::SkipEmptyParts);
    FileInfo fi(realPath);
    addFileIt(fi, list.begin(), list.end());
    
    return fi.index;
}

void FileTree::addDirectory(const QString &dirName,
                            const QString &fullPath) {

    QStringList list = fullPath.split(delim, QString::SkipEmptyParts);
    FileInfo fi(dirName, 0, true);
    addFileIt(fi, list.begin(), list.end());
}

QString FileTree::getName() {
    return finfo.name;
}

FileTree::~FileTree(void){
    for (FileTree* ch : children)
        delete ch;
}

int FileTree::childCount() const{

    return children.size();
}

int FileTree::myIndexInParentList() const{

    //Daca am parinte returneaza al catelea dintre copii lui sunt

    if (parent){
        int index;
        for (index = 0; index < parent->children.size(); ++index){
            if (parent->children[index] == this)
                return index;
        }
    }
    return -1;
}

FileTree* FileTree::getTreeIt(const QList<QString>::iterator &begin,
                              const QList<QString>::iterator &end){

    if (begin == end)
        return this; //chiar eu sunt

    for (FileTree *c : children)
        if (c->finfo.name == *begin)
            return getTreeIt(begin + 1, end);

    //Daca ajung aici inseamna ca n-am gasit nimic
    return NULL;
}

FileTree* FileTree::getTreeFromPath(const QString &path){
    /* Functie care primeste un path (in sistemul de fisiere VIRTUAL */

    QStringList list = path.split(delim, QString::SkipEmptyParts);
    return getTreeIt(list.begin(), list.end());
}

void FileTree::removeTree(){

    for (auto it = this->parent->children.begin();
            it < this->parent->children.end(); ++it){
                if (*it == this){
                    parent->children.erase(it);
                    return;
                }
    }
}

QJsonObject FileTree::toJson(){

    QJsonObject result;
    QJsonArray cJson;

    result["info"] = finfo.toJson();

    for (FileTree* c : children)
        cJson.append(c->toJson());

    result["children"] = cJson;
    return result;
}


FileTree::FileTree(const QJsonObject &json, FileTree *parent):
        finfo(json["info"].toObject()){

    this->parent = parent;
    QJsonArray cJson = json["children"].toArray();

    for (const QJsonValue &v : cJson)
        this->addChild(new FileTree(v.toObject(), this));
}