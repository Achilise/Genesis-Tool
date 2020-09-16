#ifndef PLUGINMODULE_H
#define PLUGINMODULE_H

#include <QString>

class PluginModule
{
public:
    PluginModule(const QString name, const QString path,const QString type);
    ~PluginModule();
private:
    void createHerder(const QString name, const QString path,const QString type);
    void createSource(const QString name, const QString path,const QString type);
};
#endif // PLUGINMODULE_H
