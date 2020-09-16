#include "moduleHeader.h"
#include <QTextStream>
#include <QFile>

ModuleHeader::ModuleHeader(const QString name, const QString type)
{
    QString filePath = "D:/Tool/moduleHeader.h";
    QFile file(filePath);

    if(!file.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        return;
    }

    QTextStream Stream(&file);
    QString head = (name+"Module").toUpper()+"_H";
    QChar Fist_ch = name.at(0).toUpper();
    QString Right_ch = name.right(name.size()-1)+"Module";
    QString _class = Fist_ch + Right_ch;

    Stream<<"#ifndef "<<head;
    Stream<<"\n";
    Stream<<"#define "<<head;
    Stream<<"\n\r";
    Stream<<"#include "<<"\"material_global.h\"";
    Stream<<"\n";
    Stream<<"#include "<<"\"BModule.h\"";
    Stream<<"\n";
    Stream<<"#include "<<"\""<<name<<".h\"";
    Stream<<"\n\r";
    Stream<<"class MATERIAL_EXPORT "<<_class<<" : public BModule";
    Stream<<"\n";
    Stream<<"{";
    Stream<<"\n";
    Stream<<"    Q_OBJECT";
    Stream<<"\n\r";
    Stream<<"public:";
    Stream<<"\n";
    Stream<<"    explicit "<<_class<<"();";
    Stream<<"\n";
    Stream<<"    ~"<<_class<<"();";
    Stream<<"\n\r";
    Stream<<"    static "<<_class<<"* instance();";
    Stream<<"\n\r";
    Stream<<"    virtual BNode* createNode(const BNode* parent) const override;";
    Stream<<"\n";
    Stream<<"    virtual BNode* createNode(const BNode* parent, const void* data) const override;";
    Stream<<"\n\r";
    Stream<<"    virtual Viewport* createView(const BNode* node) override;";
    Stream<<"\n";
    Stream<<"    virtual Viewport* releaseView(Viewport* viewport) override;";
    Stream<<"\n";
    Stream<<"};";
    Stream<<"\n\r";
    Stream<< "#endif "; Stream<<"// "<<head;
    file.close();

}

ModuleHeader::~ModuleHeader()
{

}
