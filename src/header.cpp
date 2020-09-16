#include "header.h"
#include <QTextStream>
#include <QFile>

Header::Header(const QString name,const QString type)
{
    QString filePath = "D:/Tool/header.h";
    QFile file(filePath);

    if(!file.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        return;
    }

    QTextStream Stream(&file);
    QString head = name.toUpper()+"_H";
    QString _type = "TYPE_"+name.toUpper();
    QString _struct = name.toLower()+"_t";
    QChar Fist_ch = name.at(0).toUpper();
    QString Right_ch = name.right(name.size()-1);
    QString _class = Fist_ch + Right_ch;

    Stream<<"#ifndef "<< head;
    Stream<<"\n";
    Stream<<"#define "<< head;
    Stream<<"\n\r";
    Stream<<"#include "<<"\"material_global.h\"";
    Stream<<"\n";
    Stream<<"#include "<<"\"BPlugin.h\"";
    Stream<<"\n\r";
    Stream<<"#define "<<_type<<"            "<<type;
    Stream<<"\n\r";
    Stream<<"typedef struct {";
    Stream<<"\n";
    Stream<<"    char name[64];";
    Stream<<"\n";
    Stream<<"}"<<_struct<<";";
    Stream<<"\n\r";
    Stream<<"class MATERIAL_EXPORT "<<_class<<" : public BNode";
    Stream<<"\n";
    Stream<<"{";
    Stream<<"\n";
    Stream<<"    Q_OBJECT";
    Stream<<"\n\r";
    Stream<<"public:";
    Stream<<"\n";
    Stream<<"    explicit "<<_class<<"();";
    Stream<<"\n";
    Stream<<"    explicit "<<_class<<"(const BNode* parent, QString name, const "<<_struct <<" *property);";
    Stream<<"\n";
    Stream<<"    explicit "<<_class<<"(const BNode* parent, const void* data);";
    Stream<<"\n\r";
    Stream<<"public:";
    Stream<<"\n";
    Stream<<"    ~Complex();";
    Stream<<"\n\r";
    Stream<<"    static "<<_class<<"* instance();";
    Stream<<"\n";
    Stream<<"};";
    Stream<<"\n";
    Stream<< "#endif "; Stream<<"// "<<head;
    file.close();
    return;
}

Header::~Header()
{

}
