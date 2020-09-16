#include "pluginPlugin.h"
#include <QTextStream>
#include <QFile>

PluginPlugin::PluginPlugin(const QString name, const QString path,const QString type)
{
    createHerder(name,path,type);
    createSource(name,path,type);
}

void PluginPlugin::createHerder(const QString name, const QString path,const QString type)
{
    QString filePath = path+"/"+name+"Plugin.h";
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

    Stream<<"#ifndef "<<name_toUpper<<"PLUGIN_H"<<"\n";
    Stream<<"#define "<<name_toUpper<<"PLUGIN_H"<<"\n\r";
    Stream<<"#include "<<"\""<<name_tolower<<"_global.h\""<<"\n";
    Stream<<"#include "<<"\""<<name_tolower<<"Module.h\""<<"\n";
    Stream<<"#include "<<"\"BPlugin.h\""<<"\n\r";
    Stream<<"#define "<<"IID_"<<name_toUpper<<"PLUGIN "<<"\"org.bunfly/"<<name_tolower<<"plugin/2.0\""<<"\n\r";
    Stream<<"class "<<name_toUpper<<"_EXPORT "<<_class<<"Plugin"<<" : public BPlugin"<<"\n";
    Stream<<"{"<<"\n";
    Stream<<"    Q_OBJECT"<<"\n";
    Stream<<"    Q_PLUGIN_METADATA"<<"(IID "<<"IID_"<<name_toUpper<<"PLUGIN"<<")"<<"\n\r";
    Stream<<"public:"<<"\n";
    Stream<<"    "<<_class<<"Plugin"<<"();"<<"\n";
    Stream<<"    "<<"~"<<_class<<"Plugin"<<"();"<<"\n\r";
    Stream<<"    "<<"virtual BModule* createModule() override;"<<"\n";
    Stream<<"    "<<"virtual BModule* releaseModule(BModule* module) override;"<<"\n";
    Stream<<"};"<<"\n";
    Stream<<"#endif"<<" // "<<name_toUpper<<"PLUGIN_H";

    file.close();
}

void PluginPlugin::createSource(const QString name, const QString path,const QString type)
{
    QString filePath = path+"/"+name+"Plugin.cpp";
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
    QString _classPlugin = _class+"Plugin";
    QString _classModule = _class+"Module";

    Stream<<"#include "<<"\""<<name_tolower<<"Plugin.h\""<<"\n";
    Stream<<"#include "<<"\""<<name_tolower<<"Module.h\""<<"\n";
    Stream<<"#include "<<"\""<<name_tolower<<".h\""<<"\n\r";

    Stream<<_classPlugin<<"::"<<_classPlugin<<"()"<<"\n";
    Stream<<"    "<<": "<<"BPlugin"<<"(TYPE_"<<name_toUpper<<", "<<"\""<<_classPlugin<<"\")"<<"\n";
    Stream<<"{"<<"\n";
    Stream<<"}"<<"\n\r";
    Stream<<_classPlugin<<"::~"<<_classPlugin<<"()"<<"\n";
    Stream<<"{"<<"\n";
    Stream<<"}"<<"\n\r";
    Stream<<"BModule* "<<_classPlugin<<"::"<<"createModule"<<"()"<<"\n";
    Stream<<"{"<<"\n";
    Stream<<"    "<<"return new "<<_classModule<<"();"<<"\n";
    Stream<<"}"<<"\n\r";
    Stream<<"BModule* "<<_classPlugin<<"::"<<"releaseModule"<<"(BModule* module)"<<"\n";
    Stream<<"{"<<"\n";
    Stream<<"    "<<"delete static_cast<"<<_classModule<<"*>(module);"<<"\n";
    Stream<<"    "<<"return nullptr;"<<"\n";
    Stream<<"}"<<"\n";

    file.close();
}

PluginPlugin::~PluginPlugin()
{

}
