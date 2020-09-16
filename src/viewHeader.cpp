#include "viewHeader.h"
#include <QTextStream>
#include <QFile>

ViewHeader::ViewHeader(const QString name, const QString typeview)
{
    QString filePath = "D:/Tool/viewHeader.h";
    QFile file(filePath);

    if(!file.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        return;
    }

    QTextStream Stream(&file);
    QString head = (name+"View").toUpper()+"_H";
    QString typeView = "TYPE_";

    Stream<<"#ifndef "<<head;
    Stream<<"\n";
    Stream<<"#define "<<head;
    Stream<<"\n\r";
    Stream<<"#include "<<"\"material_global.h\"";
    Stream<<"\n";
    Stream<<"#include "<<"\"gadget/ViewportTree.h\"";
    Stream<<"\n\r";
    Stream<<"#define ";
}

ViewHeader::~ViewHeader()
{

}
