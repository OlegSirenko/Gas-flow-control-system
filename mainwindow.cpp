#include "mainwindow.h"
#include "datareader.h"
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_socket(new QTcpSocket(this))
{
    QWidget *centralWidget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    m_plot = new QCustomPlot;
    layout->addWidget(m_plot);

    QPushButton *connectButton = new QPushButton(tr("Connect"));
    layout->addWidget(connectButton);

    setCentralWidget(centralWidget);

    connect(connectButton, &QPushButton::clicked,
            this, &MainWindow::connectToServer);

    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeFormat("hh:mm:ss");
    m_plot->xAxis->setTicker(dateTimeTicker);
    m_plot->xAxis->setTickLabelRotation(45);
}

void MainWindow::connectToServer()
{
    m_socket->connectToHost("192.168.4.1", 80);
    if (m_socket->waitForConnected()) {
        m_dataReader = new DataReader(m_socket, this);
        connect(m_dataReader, &DataReader::dataReceived,
                this, &MainWindow::updatePlot);
        m_dataReader->start();
    }
}

void MainWindow::updatePlot(double time, double temperature)
{
    static QCPGraph *graph = nullptr;
    if (!graph) {
        graph = m_plot->addGraph();
        graph->setPen(QPen(Qt::blue));
        m_plot->xAxis->setLabel("Time");
        m_plot->yAxis->setLabel("Temperature");
        m_plot->rescaleAxes();
    }

    graph->addData(time, temperature);
    m_plot->rescaleAxes();
    m_plot->replot();
}
