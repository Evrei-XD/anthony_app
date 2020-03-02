#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QtWidgets>
#include <QLogValueAxis>
#include <QSplineSeries>
#include <QValueAxis>
#include <QChart>
#include <QChartView>

using namespace QtCharts;

class GraphicWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GraphicWindow(QDialog *parent = nullptr);
    ~GraphicWindow();

    void ShowGraphics(uint param1, uint param2);

private:
    void closeEvent(QCloseEvent *);

    void ShowGraphics_private(uint param1, uint param2);

    void graphic_interface();

    QChart *graphic1;
    QChart *graphic2;

    QValueAxis *yAxis1;
    QValueAxis *yAxis2;
    QValueAxis *xAxis1;
    QValueAxis *xAxis2;

    unsigned long long int time;

    QChartView *chartView1;
    QChartView *chartView2;

    QSplineSeries *series1;
    QSplineSeries *series2;

    QHBoxLayout *hlayout;
private slots:
    void remove_point();
};

#endif // GRAPH_H
