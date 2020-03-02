#include "Graph.h"

GraphicWindow::GraphicWindow(QDialog *parent) :
    QDialog(parent)
{
    setWindowTitle("Графики");
    //resize(1000,800);


    graphic1 = new QChart();
    graphic2 = new QChart();


    series1 = new QSplineSeries();
    series2 = new QSplineSeries();

    chartView1 = new QChartView(graphic1);
    chartView2 = new QChartView(graphic2);
    hlayout=new QHBoxLayout();
    time=0;

    yAxis1 = new QValueAxis;
    yAxis1->setRange(0, 3000);
    yAxis2 = new QValueAxis;
    yAxis2->setRange(0, 3000);

    xAxis1 = new QValueAxis;
    xAxis2 = new QValueAxis;

    connect(series1,SIGNAL(pointAdded(int)),this,SLOT(remove_point()));
    graphic_interface();
}

void GraphicWindow::ShowGraphics(uint param1, uint param2)
{
    time++;
    ShowGraphics_private(param1,param2);
}

void GraphicWindow::remove_point()
{
    qreal x = graphic1->plotArea().width() / yAxis1->tickCount();
    qreal y = (yAxis1->max() - yAxis1->min()) / yAxis1->tickCount();
  //  m_x += y;
   // m_y = QRandomGenerator::global()->bounded(5) - 2.5;
   // m_series->append(m_x, m_y);
    graphic1->scroll(x, 0);
    if(series1->count()>=100)
    {
        series1->remove(0);
        series2->remove(0);
    }
}
/*
void handleTimeout()
{
    qreal x = plotArea().width() / m_axisX->tickCount();
    qreal y = (m_axisX->max() - m_axisX->min()) / m_axisX->tickCount();
    m_x += y;
    m_y = QRandomGenerator::global()->bounded(5) - 2.5;
    m_series->append(m_x, m_y);
    scroll(x, 0);
    if (m_x == 100)
        m_timer.stop();
}*/

void GraphicWindow::graphic_interface()
{
    hlayout->addWidget(chartView1);
    hlayout->addWidget(chartView2);
    //QChart
    chartView1->setMinimumSize(200,200);
    chartView1->setChart(graphic1);
    chartView1->setRenderHint(QPainter::Antialiasing);


    chartView2->setMinimumSize(200,200);
    chartView2->setChart(graphic2);
    chartView2->setRenderHint(QPainter::Antialiasing);

    series1->setUseOpenGL(true);
    series1->setColor(Qt::red);
    series1->append(0, 0);

    series2->setUseOpenGL(true);
    series2->setColor(Qt::red);
    series2->append(0, 0);


//    addSeries(m_series);

//    addAxis(m_axisX,Qt::AlignBottom);
//    addAxis(m_axisY,Qt::AlignLeft);
//    m_series->attachAxis(m_axisX);
//    m_series->attachAxis(m_axisY);
//    m_axisX->setTickCount(5);
//    m_axisX->setRange(0, 10);
//    m_axisY->setRange(-5, 10);

    graphic1->setTheme(QChart::ChartThemeDark);
    graphic1->setAnimationOptions(QChart::AllAnimations);
    graphic1->addSeries(series1);
    graphic1->addAxis(yAxis1,Qt::AlignLeft);

    series1->attachAxis(yAxis1);
    //graphic1->setAxisY(yAxis1,series1);

    graphic1->legend()->hide();

    graphic2->setTheme(QChart::ChartThemeDark);
    graphic2->setAnimationOptions(QChart::AllAnimations);
    graphic2->addSeries(series2);
    graphic2->addAxis(yAxis2,Qt::AlignLeft);
    series2->attachAxis(yAxis2);
   // graphic2->setAxisY(yAxis2,series2);
    graphic2->legend()->hide();

    setLayout(hlayout);
    show();
}

void GraphicWindow::ShowGraphics_private(uint param1, uint param2)
{
    //QChart
    //graphic1->removeSeries(series1);
    //graphic1->addSeries(series1);
    series1->append(time ,param1);
    // graphic1->setAxisY(yAxis1,series1);
    //  graphic1->legend()->hide();

    // graphic2->removeSeries(series2);
    //graphic2->addSeries(series2);
    series2->append(time ,param2);
    // graphic2->setAxisY(yAxis2,series2);
    // graphic2->legend()->hide();
}

void GraphicWindow::closeEvent(QCloseEvent *)
{
    GraphicWindow::close();
}

GraphicWindow::~GraphicWindow()
{

    delete(chartView1);
    delete(chartView2);

    delete(series1);
    delete(series2);

    delete(graphic1);
    delete(graphic2);
    delete(hlayout);

    delete(yAxis1);
    delete(yAxis2);
}

