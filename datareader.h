#ifndef DATAREADER_H
#define DATAREADER_H

#include <QThread>
#include <QTcpSocket>

class DataReader : public QThread
{
    Q_OBJECT

public:
    DataReader(QTcpSocket *socket, QObject *parent = nullptr);

signals:
    void dataReceived(double time, double voltage);

protected:
    void run() override;

private:
    QTcpSocket *m_socket;
};

#endif // DATAREADER_H
