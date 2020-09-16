#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Plug-in generation tool");
    this->setGeometry(500,200,800,400);
    initUI();
}

void Dialog::initUI()
{

}

void Dialog::on_buttonBox_accepted()
{
    QString name = ui->lineEdit->text();
    QString path = ui->lineEdit_2->text();
    if(name.isEmpty()||path.isEmpty())
    {
        QString dlgTitle = "waring";
        QString strInfo = "The name or path cannot be empty ！";
        QMessageBox::warning(this,dlgTitle,strInfo);
        return;
    }

     plugin = new Plugin(name,path,"0x4001");
     pluginGlobal = new PluginGlobal(name,path,"0x4001");
     pluginModule = new PluginModule(name,path,"0x4001");
     pluginPlugin = new PluginPlugin(name,path,"0x4001");
}

void Dialog::on_buttonBox_rejected()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
}


Dialog::~Dialog()
{
    delete pluginPlugin;
    delete pluginModule;
    delete pluginGlobal;
    delete plugin;
    delete ui;
}
