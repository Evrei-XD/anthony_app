#include "Graph.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QDebug>

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series(0),
    m_axisX(new QValueAxis()),
    m_axisY(new QValueAxis()),
    m_step(0),
    m_x(9999),
    m_y(0)
{
    QObject::connect(&m_timer, &QTimer::timeout, this, &Chart::handleTimeout);
    m_timer.setInterval(30);

    setTheme(QChart::ChartThemeDark);

   // m_series = new QLineSeries(this);
    m_series = new QSplineSeries(this);
    QPen my_pen(Qt::red);
    my_pen.setWidth(5);
    m_series->setPen(my_pen);

    addSeries(m_series);

    addAxis(m_axisX,Qt::AlignBottom);
    addAxis(m_axisY,Qt::AlignLeft);
    axisX()->setVisible(false);
    m_series->attachAxis(m_axisX);
    m_series->attachAxis(m_axisY);
    m_axisX->setTickCount(5);
    m_axisX->setRange(0, 10000);
    m_axisY->setRange(0, 3000);

    m_timer.start();
}

Chart::~Chart()
{

}

void Chart::appendPoint(int y)
{
    m_y=y;
}

void Chart::handleTimeout()
{
    qreal x = plotArea().width() / 100;
    qreal y = (m_axisX->max() - m_axisX->min()) / 100;
    m_x += y;
    m_series->append(m_x, m_y);
    scroll(x, 0);
    if (m_series->count() == 10000)
    {
        m_series->remove(0);
    }
}
