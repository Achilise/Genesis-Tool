#ifndef PLUGIN_H
#define PLUGIN_H

#include <QString>

class Plugin
{
public:
    Plugin(const QString name, const QString path,const QString type);
    ~Plugin();

private:
    void createHerder(const QString name, const QString path,const QString type);
    void createSource(const QString name, const QString path,const QString type);
};
#endif // PLUGIN_H
