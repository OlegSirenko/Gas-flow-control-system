#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->sendHost_btn->setEnabled(false);
    ui->plot_2->addGraph();

    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeFormat("hh:mm:ss");
    ui->plot_2->xAxis->setTicker(dateTimeTicker);
    ui->plot_2->xAxis->setTickLabelRotation(45);

    ui->plot_2->setInteraction(QCP::iRangeDrag, true);
    ui->plot_2->setInteraction(QCP::iRangeZoom, true);

    dataProcessor = new DataProcessor;
    dataProcessor->moveToThread(&dataProcessorThread);
    connect(&dataProcessorThread, &QThread::finished, dataProcessor, &QObject::deleteLater);


    //auto loading_gif = new QMovie();

    settings_window = new Settings;

    connect(this, SIGNAL(startProcessing(QString,int)), dataProcessor, SLOT(startProcessing(QString,int)));
    connect(this, &MainWindow::stopProcessing, dataProcessor, &DataProcessor::stopProcessing);
    //connect(this, SIGNAL(sendKoeff(double)), dataProcessor, SLOT(sendData(double)));


    connect(dataProcessor, &DataProcessor::newData, this, &MainWindow::updateGraph);
//    connect(dataProcessor, &DataProcessor::connected, this, &MainWindow::on_connected);
//    connect(dataProcessor, &DataProcessor::disconnected, this, &MainWindow::on_disconnected);
//    connect(dataProcessor, SIGNAL(connection_status_not_default(QString)), this, SLOT(show_message_in_statubar(QString)));
//    connect(settings_window, SIGNAL(apply(QString,int)), this, SLOT(apply_settings(QString,int)));

    dataProcessorThread.start();

}

MainWindow::~MainWindow()
{
    dataProcessorThread.quit();
    dataProcessorThread.wait();
    settings_window->window()->close();
    settings_window->close();
    delete ui;
}


void MainWindow::updateGraph(double data)
{
    double time = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
    ui->plot_2->graph(0)->addData(time, data);
    ui->plot_2->graph(0)->rescaleAxes();
    ui->plot_2->replot();
    qDebug()<<time<<data;
}

void MainWindow::on_connect_btn_clicked()
{
    ui->connect_btn->setEnabled(false);
    ui->statusbar->showMessage("Trying to connect...");
    emit startProcessing(default_address, default_port);
}


void MainWindow::on_disconnect_btn_clicked()
{
    emit stopProcessing();
}


void MainWindow::on_sendHost_btn_clicked()
{
    emit sendKoeff(3.0);
}


void MainWindow::on_connected(){
    ui->statusbar->showMessage("Connected");
    ui->sendHost_btn->setEnabled(true);
}


void MainWindow::on_disconnected(){
    ui->statusbar->showMessage("Disconnected");
    ui->sendHost_btn->setEnabled(false);

}

void MainWindow::on_settings_btn_clicked(){
    qDebug()<<ui->settings_btn->x()<< ui->settings_btn->y();
    settings_window->move(ui->settings_btn->x(), ui->settings_btn->y());
    settings_window->window()->showNormal();
}


void MainWindow::apply_settings(QString address_local, int port_local){
    emit stopProcessing();
    qDebug()<<"Reconnecting to "<< address_local<< port_local;
    emit startProcessing(address_local, port_local);
    default_address = address_local;
    default_port = port_local;

}

void MainWindow::show_message_in_statubar(QString message){
    if (message.contains("timed out")){
        ui->connect_btn->setEnabled(true);
    }
    ui->statusbar->showMessage(message);
}
