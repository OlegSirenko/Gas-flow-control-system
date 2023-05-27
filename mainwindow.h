#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dataprocessor.h"
#include <QThread>
#include <qcustomplot.h>
#include "settings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DataProcessor *dataProcessor;
    Settings *settings_window;
    QThread dataProcessorThread;
    QString default_address = "192.168.4.1";
    int default_port = 80;

public slots:
    void updateGraph(double data);
    void on_connected();
    void on_disconnected();
    void apply_settings(QString,int);
    void show_message_in_statubar(QString);

private slots:
    void on_connect_btn_clicked();
    void on_disconnect_btn_clicked();
    void on_sendHost_btn_clicked();
    void on_settings_btn_clicked();

signals:
    void startProcessing(QString, int);
    void stopProcessing();
    void sendKoeff(double koeff);
};
#endif // MAINWINDOW_H
