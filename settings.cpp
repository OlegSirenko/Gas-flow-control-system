#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_apply_btn_clicked()
{

    QString address = ui->address_lineEdit->text();
    QString port = ui->port_lineEdit->text();

    if (address.isEmpty()){
        ui->address_lineEdit->setText("192.168.4.1");
        qDebug()<<"Адрес не может быть пустым";
        return;
    }
    if (port.isEmpty()){
        ui->port_lineEdit->setText("80");
        qDebug()<<"Порт не может быть пустым";
        return;
    }

    emit apply(address, port.toInt());
}

