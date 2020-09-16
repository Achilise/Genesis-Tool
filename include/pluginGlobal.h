#ifndef PLUGINGLOBAL_H
#define PLUGINGLOBAL_H

#include <QString>

class PluginGlobal
{
public:
    PluginGlobal(const QString name, const QString path,const QString type);
    ~PluginGlobal();

private:
    void createHerder(const QString name, const QString path,const QString type);
};
#endif // PLUGINGLOBAL_H
