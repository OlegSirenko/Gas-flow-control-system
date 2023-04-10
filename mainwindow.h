#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include "qcustomplot.h"

class DataReader;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void connectToServer();
    void updatePlot(double time, double voltage);

private:
    QTcpSocket *m_socket;
    DataReader *m_dataReader;
    QCustomPlot *m_plot;
};

#endif // MAINWINDOW_H
