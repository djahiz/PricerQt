#ifndef FENETREPRICECALLPUT_H
#define FENETREPRICECALLPUT_H

#include <QWidget>
#include <QGridLayout>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include "blackscholes.h"
#include <vector>
#include <algorithm>
#include <QLabel>
#include "alea.h"
#include "montecarlo.h"
#include "mycharts.h"
#include <QCheckBox>
#include <QPushButton>
#include <QMdiSubWindow>
#include <QMdiArea>

class FenetrePriceCallPut : public QWidget {

    Q_OBJECT

public:
    FenetrePriceCallPut(QMdiArea *p, QString type, double S0, double K, double r, double std, double T, int nbSimul);

public slots:
    void displayDelta();
    void displayGamma();
    void displayVega();
    void displayTheta();
    void displayRho();

private:
    QString m_type;
    QtCharts::QScatterSeries *serie_price, *serie_IC_min, *serie_IC_max;
    double m_S0, m_K, m_r, m_std, m_T, m_prix_BS, m_prix_MC;
    int m_nbSimul;
    QGridLayout *layout;
    QVBoxLayout *result, *greeks;
    QPushButton *delta, *gamma, *vega, *theta, *rho;
    std::vector<QtCharts::QScatterSeries*> m_series;
    MyCharts *chart;
    QMdiArea *parent;

};

#endif // FENETREPRICECALLPUT_H
