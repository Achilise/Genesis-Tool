#include "pluginModule.h"
#include <QTextStream>
#include <QFile>

PluginModule::PluginModule(const QString name, const QString path,const QString type)
{
    createHerder(name,path,type);
    createSource(name,path,type);
}

void PluginModule::createHerder(const QString name, const QString path,const QString type)
{
    QString filePath = path+"/"+name+"Module.h";
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

    Stream<<"#ifndef "<<name_toUpper<<"MODULE_H"<<"\n";
    Stream<<"#define "<<name_toUpper<<"MODULE_H"<<"\n\r";
    Stream<<"#include "<<"\""<<name_tolower<<"_global.h\""<<"\n";
    Stream<<"#include "<<"\""<<name<<".h\""<<"\n";
    Stream<<"#include "<<"\"BModule.h\""<<"\n";
    Stream<<"#include "<<"\"BNode.h\""<<"\n";
    Stream<<"#include "<<"\"gadget/Menu.h\""<<"\n\r";
    Stream<<"class "<<name_toUpper<<"_EXPORT "<<_class<<"Module"<<" : public BModule"<<"\n";
    Stream<<"{"<<"\n";
    Stream<<"    Q_OBJECT"<<"\n\r";
    Stream<<"public:"<<"\n";
    Stream<<"    "<<"explicit "<<_class<<"Module"<<"();"<<"\n";
    Stream<<"    "<<"~"<<_class<<"Module"<<"();"<<"\n\r";
    Stream<<"    "<<"static "<<_class<<"Module"<<"* instance();"<<"\n\r";
    Stream<<"    "<<"virtual BNode* createNode(const BNode* parent) const override;"<<"\n";
    Stream<<"    "<<"virtual BNode* createNode(const BNode* parent,const void* data) const override;"<<"\n\r";
    Stream<<"    "<<"virtual Menu* createExplorerPopup(const BNode* node) override;"<<"\n";
    Stream<<"    "<<"virtual Menu* releaseExplorerPopup(Menu* menu) override;"<<"\n";
    Stream<<"    "<<"virtual void explorerAction(Menu* menu) override;"<<"\n";
    Stream<<"};"<<"\n\r";
    Stream<<"#endif"<<" // "<<name_toUpper<<"MODULE_H"<<"\n";

    file.close();
}

void PluginModule::createSource(const QString name, const QString path,const QString type)
{
    QString filePath = path+"/"+name+"Module.cpp";
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
    QString _classModule = _class+"Module";
    QString g_classModule = "g_"+_classModule+"Instance";

    Stream<<"#include "<<"\""<<name<<"Module.h\""<<"\n";
    Stream<<"#include "<<"\"common/Folder.h\""<<"\n";
    Stream<<"#include "<<"\"BProperty.h\""<<"\n\r";
    Stream<<"static "<<_classModule<<"* "<<g_classModule <<" = "<<"nullptr;"<<"\n\r";
    Stream<<_classModule<<"::"<<_classModule<<"()"<<"\n";
    Stream<<"    "<<": BModule(TYPE_"<<name_toUpper<<", "<<"\""<<_classModule<<"\")"<<"\n";
    Stream<<"{"<<"\n";
    Stream<<"    "<<"assert(!"<<g_classModule<<");"<<"\n\r";
    Stream<<"    "<<"REGISTER_PROPERTY"<<"(TYPE_"<<name_toUpper<<", "<<_struct<<");"<<"\n";
    Stream<<"    "<<"REGISTER_NODE"<<"(TYPE_"<<name_toUpper<<", "<<_class<<");"<<"\n\r";
    Stream<<"    "<<g_classModule<<" = this;"<<"\n";
    Stream<<"}"<<"\n\r";
    Stream<<_classModule<<"::~"<<_classModule<<"()"<<"\n";
    Stream<<"{"<<"\n";
    Stream<<"    "<<"assert("<<g_classModule<<");"<<"\n\r";
    Stream<<"    "<<"BModule* module;"<<"\n";
    Stream<<"    "<<"foreach(module, modules)"<<"\n";
    Stream<<"    {"<<"\n";
    Stream<<"        modules.removeOne(module);"<<"\n";
    Stream<<"        delete module;"<<"\n";
    Stream<<"    }"<<"\n\r";
    Stream<<"    "<<g_classModule<<" = nullptr;"<<"\n\r";
    Stream<<"    "<<"UNREGISTER_NODE"<<"(TYPE_"<<name_toUpper<<");"<<"\n";
    Stream<<"    "<<"UNREGISTER_PROPERTY"<<"(TYPE_"<<name_toUpper<<");"<<"\n";
    Stream<<"}"<<"\n\r";
    Stream<<_classModule<<"* "<<_classModule<<"::"<<"instance()"<<"\n";
    Stream<<"{"<<"\n";
    Stream<<"    "<<"assert("<<g_classModule<<");"<<"\n";
    Stream<<"    "<<"return "<<g_classModule<<";"<<"\n";
    Stream<<"}"<<"\n\r";
    Stream<<"BNode* "<<_classModule<<"::"<<"createNode(const BNode* parent) const"<<"\n";
    Stream<<"{"<<"\n";
    Stream<<"    "<<_struct<<" property;"<<"\n";
    Stream<<"    "<<"memset(&property, 0x00, sizeof("<<_struct<<"));"<<"\n\r";
    Stream<<"    "<<"return new "<<_class<<"(parent, &property);"<<"\n";
    Stream<<"}"<<"\n\r";
    Stream<<"BNode* "<<_classModule<<"::"<<"createNode(const BNode* parent, const void* data) const"<<"\n";
    Stream<<"{"<<"\n";
    Stream<<"    "<<"return new "<<_class<<"(parent, data);"<<"\n";
    Stream<<"}"<<"\n\r";
    Stream<<"Menu* "<<_classModule<<"::"<<"createExplorerPopup(const BNode* node)"<<"\n";
    Stream<<"{"<<"\n";
    Stream<<"    "<<"Menu* menu = new Menu(node);"<<"\n";
    Stream<<"    "<<"menu->insertAction(Action::NEWFOLDER);"<<"\n";
    Stream<<"    "<<"menu->insertSeparator();"<<"\n\r";
    Stream<<"    "<<"return menu;"<<"\n";
    Stream<<"}"<<"\n\r";
    Stream<<"Menu* "<<_classModule<<"::"<<"releaseExplorerPopup(Menu* menu)"<<"\n";
    Stream<<"{"<<"\n";
    Stream<<"    "<<"Action* action;"<<"\n";
    Stream<<"    "<<"while (menu->count())"<<"\n";
    Stream<<"    "<<"{"<<"\n";
    Stream<<"        "<<"action = menu->getAction(0);"<<"\n";
    Stream<<"        "<<"menu->removeAction(action);"<<"\n";
    Stream<<"    "<<"}"<<"\n\r";
    Stream<<"    "<<"delete menu;"<<"\n";
    Stream<<"    "<<"return nullptr;"<<"\n";
    Stream<<"}"<<"\n\r";
    Stream<< "void "<<_classModule<<"::"<<"explorerAction(Menu * menu)"<<"\n";
    Stream<<"{"<<"\n";
    Stream<<"}";
}

PluginModule::~PluginModule()
{

}
