#ifndef PLUGINPLUGIN_H
#define PLUGINPLUGIN_H

#include <QString>

class PluginPlugin
{
public:
    PluginPlugin(const QString name, const QString path,const QString type);
    ~PluginPlugin();
private:
    void createHerder(const QString name, const QString path,const QString type);
    void createSource(const QString name, const QString path,const QString type);
};
#endif // PLUGINPLUGIN_H
