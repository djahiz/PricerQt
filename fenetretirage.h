#ifndef FENETRETIRAGE_H
#define FENETRETIRAGE_H

#include <QWidget>
#include <QGridLayout>
#include <QtCharts/QScatterSeries>
#include "alea.h"
#include "qalea.h"
#include "mycharts.h"
#include <vector>

class FenetreTirage : public QWidget {
public:
    FenetreTirage(QString type, QString dim, double xm, double xM, double ym, double yM, double m, double s, int n);
    ~FenetreTirage();

private:
    QString m_type, m_dim, m_title;
    QtCharts::QScatterSeries *serie;
    double m_xMin, m_xMax, m_yMin, m_yMax, m_moy, m_std;
    int m_nbSimul;
    MyCharts *chart;
    QGridLayout *layout;
    std::vector<QtCharts::QScatterSeries*> m_series;

};

#endif // FENETRETIRAGE_H
