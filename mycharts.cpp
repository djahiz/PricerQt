#include "mycharts.h"

MyCharts::MyCharts(std::vector<QtCharts::QScatterSeries*> series, QString title, double xMin, double xMax, double yMin, double yMax) : QtCharts::QChartView() {
    m_xMin = xMin;
    m_xMax = xMax;
    m_yMin = yMin;
    m_yMax = yMax;
    m_title = title;
    graph = new QtCharts::QChart();
    m_series_s = series;

    graph->legend()->hide();
    for(int i(0);i<m_series_s.size();i++)
        graph->addSeries(m_series_s[i]);

    graph->createDefaultAxes();

    graph->axisX()->setRange(m_xMin, m_xMax);
    if(m_yMin != m_yMax)
        graph->axisY()->setRange(m_yMin, m_yMax);

    graph->setTitle("m_title");

    setChart(graph);
    setRenderHint(QPainter::Antialiasing);
}

MyCharts::MyCharts(std::vector<QtCharts::QLineSeries*> series, QString title, double xMin, double xMax, double yMin, double yMax) : QtCharts::QChartView() {
    m_xMin = xMin;
    m_xMax = xMax;
    m_yMin = yMin;
    m_yMax = yMax;
    m_title = title;
    graph = new QtCharts::QChart();
    m_series_l = series;

    graph->legend()->hide();
    for(int i(0);i<m_series_l.size();i++)
        graph->addSeries(m_series_l[i]);

    graph->createDefaultAxes();

    graph->axisX()->setRange(m_xMin, m_xMax);
    if(m_yMin != m_yMax)
        graph->axisY()->setRange(m_yMin, m_yMax);

    graph->setTitle("m_title");

    setChart(graph);
    setRenderHint(QPainter::Antialiasing);
}

MyCharts::~MyCharts(){
    delete graph;
}

/*void MyCharts::enableCursorValue(){
    connect(graph,SIGNAL(hovered()),this,SLOT(hide()));
}*/
