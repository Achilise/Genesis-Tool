#include "plugin.h"
#include <QTextStream>
#include <QFile>

Plugin::Plugin(const QString name, const QString path,const QString type)
{
    createHerder(name,path,type);
    createSource(name,path,type);
}

void Plugin::createHerder(const QString name, const QString path,const QString type)
{
    QString filePath = path+"/"+name+".h";
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

    Stream<<"#ifndef "<<name_toUpper<<"_H"<<"\n";
    Stream<<"#define "<<name_toUpper<<"_H"<<"\n\r";
    Stream<<"#include "<<"\""<<name_tolower<<"_global.h\""<<"\n";
    Stream<<"#include "<<"\"BNode.h\""<<"\n\r";
    Stream<<"#define "<<"TYPE_"<<name_toUpper<<"        "<<type<<"\n";
    Stream<<"typedef struct {"<<"\n";
    Stream<<"    char name[64];"<<"\n";
    Stream<<"    int32_t type;"<<"\n";
    Stream<<"}"<<name<<"_t;"<<"\n\r";
    Stream<<"class "<<name_toUpper<<"_EXPORT "<<_class<<" : public BNode"<<"\n";
    Stream<<"{"<<"\n";
    Stream<<"    Q_OBJECT"<<"\n\r";
    Stream<<"public:"<<"\n";
    Stream<<"    "<<_class<<"();"<<"\n";
    Stream<<"    "<<_class<<"(const BNode* parent, const "<<_struct<<"* property);"<<"\n";
    Stream<<"    "<<_class<<"(const BNode* parent, const void* data);"<<"\n\r";
    Stream<<"    "<<"~"<<_class<<"();"<<"\n\r";
    Stream<<"    "<<"static "<<_class<<"* instance();"<<"\n";
    Stream<<"private:"<<"\n";
    Stream<<"};"<<"\n\r";
    Stream<<"#endif"<<" // "<<name_toUpper<<"_H";

    file.close();
}

void Plugin::createSource(const QString name, const QString path,const QString type)
{
    QString filePath = path+"/"+name+".cpp";
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
    QString g_class = "g_"+_class+"Instance";

    Stream<<"#include "<<"\""<<name_tolower<<".h\""<<"\n";
    Stream<<"#include "<<"\"BProperty.h\""<<"\n";
    Stream<<"#include "<<"\"Befunlog.h\""<<"\n\r";
    Stream<<"static "<<_class<<"* "<<g_class<<" = "<<"nullptr;"<<"\n\r";
    Stream<<_class<<"::"<<_class<<"()"<<"\n";
    Stream<<"    "<<": "<<"BNode(TYPE_"<<name_toUpper<<", \""<<_class<<"\")"<<"\n";
    Stream<<"{"<<"\n";
    Stream<<"    "<<"assert(!"<<g_class<<");"<<"\n";
    Stream<<"    "<<g_class<<" = "<<"this;"<<"\n\r";
    Stream<<"    "<<"BEFUN_INFO"<<"(\"0x%04X: 0x%08X, %s created\", type, id, tc(className));"<<"\n";
    Stream<<"}"<<"\n\r";
    Stream<<_class<<"::"<<_class<<"(const BNode* parent, const "<<_struct<<"* property)"<<"\n";
    Stream<<"   "<<": "<<"BNode"<<"(parent, TYPE_"<<name_toUpper<<", "<<"\""<<_class<<"\""<<", false, property)"<<"\n";
    Stream<<"{"<<"\n";
    Stream<<"    "<<"assert(parent);"<<"\n";
    Stream<<"    "<<"assert("<<g_class<<");"<<"\n\r";
    Stream<<"    "<<"setCategories(BNode::GENUS_PLUGIN);"<<"\n";
    Stream<<"}"<<"\n\r";
    Stream<<_class<<"::"<<_class<<"(const BNode* parent, const void* data)"<<"\n";
    Stream<<"    "<<": "<<"BNode"<<"(parent, data)"<<"\n";
    Stream<<"{"<<"\n";
    Stream<<"    "<<"assert(parent);"<<"\n";
    Stream<<"    "<<"assert("<<g_class<<");"<<"\n";
    Stream<<"}"<<"\n\r";
    Stream<<_class<<"::~"<<_class<<"()"<<"\n";
    Stream<<"{"<<"\n";
    Stream<<"    "<<"//assert("<<g_class<<");"<<"\n\r";
    Stream<<"    "<<"if (this == "<<g_class<<")"<<"\n";
    Stream<<"    "<<"{"<<"\n";
    Stream<<"        "<<g_class<<" = "<<"nullptr;"<<"\n";
    Stream<<"    "<<"}"<<"\n";
    Stream<<"}"<<"\n\r";
    Stream<<_class<<"* "<<_class<<"::"<<"instance()"<<"\n";
    Stream<<"{"<<"\n";
    Stream<<"    "<<"assert("<<g_class<<");"<<"\n";
    Stream<<"    "<<"return "<<g_class<<";"<<"\n";
    Stream<<"}"<<"\n";

    file.close();
}

Plugin::~Plugin()
{

}
