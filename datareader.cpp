#include "datareader.h"
#include <QJsonDocument>
#include <QJsonObject>

DataReader::DataReader(QTcpSocket *socket, QObject *parent)
    : QThread(parent), m_socket(socket) {}

void DataReader::run()
{
    while (m_socket->waitForReadyRead()) {
        QByteArray data = m_socket->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (!doc.isNull() && doc.isObject()) {
            QJsonObject obj = doc.object();
            if (obj.contains("Temperature")) {
                double time = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
                double temperature = obj["Temperature"].toDouble();
                emit dataReceived(time, temperature);
            }
        }
        else{
            qDebug()<<"Something went wrong";
        }
    }
}
