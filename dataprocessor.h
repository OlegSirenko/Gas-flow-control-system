#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QUrl>

class DataProcessor : public QObject
{
    Q_OBJECT

public:
    DataProcessor(QObject *parent = nullptr);

public slots:
    void startProcessing(QString address, int port);
    void stopProcessing();

private slots:
    void requestData();
    void onReplyFinished(QNetworkReply *reply);

signals:
    void newData(double value);

private:
    QNetworkAccessManager *manager;
    QTimer *timer;
    QUrl url;
};

#endif // DATAPROCESSOR_H
