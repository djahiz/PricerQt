#include "fenetretirage.h"

FenetreTirage::FenetreTirage(QString type, QString dim, double xm, double xM, double ym, double yM, double m, double s, int n) : QWidget(){
    m_type = type;
    m_dim = dim;
    m_xMin = std::min(xm,xM);
    m_xMax = std::max(xm,xM);
    m_yMin = std::min(ym,yM);
    m_yMax = std::max(ym,yM);
    m_moy = m;
    m_std = s;
    m_nbSimul = n;
    m_title = "title";

    serie = new QtCharts::QScatterSeries();
    m_series.push_back(serie);
    if(dim == "1d"){
        if(type == "uniforme")
            uniforme1d(serie,m_xMin,m_xMax,m_nbSimul);
        if(type == "normale")
            normale1d(serie,m_moy,m_std,m_nbSimul);
    }
    else{
        if(type == "uniforme")
            uniforme2d(serie,m_xMin,m_xMax,m_yMin,m_yMax,m_nbSimul);
        if(type == "normale")
            normale2d(serie,m_moy,m_std,m_nbSimul);
        if(type == "TIT")
            TIT2d(serie,m_nbSimul);
    }

    chart = new MyCharts(m_series,m_title,m_xMin,m_xMax,m_yMin,m_yMax);

    layout = new QGridLayout((QWidget*)this);
    layout->addWidget(chart, 0, 0);
    setLayout(layout);
}

FenetreTirage::~FenetreTirage(){
    delete chart;
}
