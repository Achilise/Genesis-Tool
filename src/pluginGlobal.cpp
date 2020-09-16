#include "pluginGlobal.h"
#include <QTextStream>
#include <QFile>

PluginGlobal::PluginGlobal(const QString name, const QString path,const QString type)
{
    createHerder(name,path,type);
}

void PluginGlobal::createHerder(const QString name, const QString path,const QString type)
{
    QString filePath = path+"/"+name+"_global.h";
    QFile file(filePath);

    if(!file.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        return;
    }

    QTextStream Stream(&file);
    QString name_toUpper = name.toUpper();
    QString name_tolower = name.toLower();
    QString _struct = name_tolower+"_t";
    QChar Fist_ch = name.at(0).toUpper();
    QString Right_ch = name.right(name.size()-1);
    QString _class = Fist_ch + Right_ch;

    Stream<<"#ifndef "<<name_toUpper<<"_GLOBAL_H"<<"\n";
    Stream<<"#define "<<name_toUpper<<"_GLOBAL_H"<<"\n\r";
    Stream<<"#include <QtCore/qglobal.h>"<<"\n\r";
    Stream<<"#if defined("<<name_toUpper<<"_LIBRARY)"<<"\n";
    Stream<<"#  define "<<name_toUpper<<"_EXPORT "<<"Q_DECL_EXPORT"<<"\n";
    Stream<<"#else"<<"\n";
    Stream<<"#  define "<<name_toUpper<<"_EXPORT "<<"Q_DECL_IMPORT"<<"\n";
    Stream<<"#endif"<<"\n\r";
    Stream<<"#endif"<<" // "<<name_toUpper<<"_GLOBAL_H";

    file.close();
}

PluginGlobal::~PluginGlobal()
{

}
