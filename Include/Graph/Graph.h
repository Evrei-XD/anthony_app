#ifndef GRAPH_H
#define GRAPH_H

#include <QtCharts/QChart>
#include <QtCore/QTimer>

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

//![1]
class Chart: public QChart
{
    Q_OBJECT
public:
    Chart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    virtual ~Chart();

public slots:
    void handleTimeout();
    void appendPoint(int y);

private:
    QTimer m_timer;
  //  QLineSeries *m_series;
    QSplineSeries *m_series;
    QStringList m_titles;
    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
    int time;
    qreal m_step;
    qreal m_x;
    qreal m_y;
};
//![1]

#endif /* CHART_H */
