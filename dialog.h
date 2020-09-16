#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "plugin.h"
#include "pluginGlobal.h"
#include "pluginModule.h"
#include "pluginPlugin.h"
#include <QAbstractButton>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();



private:
    Ui::Dialog *ui;
    void initUI();

private:
    Plugin* plugin;
    PluginGlobal* pluginGlobal;
    PluginModule* pluginModule;
    PluginPlugin* pluginPlugin;
};
#endif // DIALOG_H
