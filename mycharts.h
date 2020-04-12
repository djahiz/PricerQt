#ifndef MYCHARTS_H
#define MYCHARTS_H

#include <vector>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLineSeries>
#include <QString>

class MyCharts : public QtCharts::QChartView {

    Q_OBJECT

public:
    MyCharts(std::vector<QtCharts::QScatterSeries*> series, QString title, double xMin, double xMax, double yMin, double yMax);
    MyCharts(std::vector<QtCharts::QLineSeries*> series, QString title, double xMin, double xMax, double yMin, double yMax);
    ~MyCharts();
    //void enableCursorValue();

private:
    QtCharts::QChart *graph;
    double m_xMin, m_xMax, m_yMin, m_yMax;
    QString m_title;
    std::vector<QtCharts::QScatterSeries*> m_series_s;
    std::vector<QtCharts::QLineSeries*> m_series_l;

};

#endif // MYCHARTS_H
