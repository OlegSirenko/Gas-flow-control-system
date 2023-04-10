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
        QJsonObject obj = doc.object();
        double time = obj["time"].toDouble();
        double voltage = obj["Voltage"].toDouble();
        emit dataReceived(time, voltage);
    }
}
