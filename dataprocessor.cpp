#include "dataprocessor.h"

DataProcessor::DataProcessor(QObject *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onReplyFinished(QNetworkReply*)));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(requestData()));
}

void DataProcessor::startProcessing(QString address, int port)
{
    qDebug()<<"Получаем данные";
    url = QUrl("http://"+address);
    url.setPort(80);
    url.setPath("/sensor-value");

    timer->start(1000); // 1 second interval
}

void DataProcessor::stopProcessing()
{
    timer->stop();
}

void DataProcessor::requestData()
{
    QNetworkRequest request(url);
    manager->get(request);
}

void DataProcessor::onReplyFinished(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    qDebug()<<data;
    double value = data.toDouble();
    qDebug()<<value;
    emit newData(value);
}
