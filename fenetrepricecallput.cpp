#include "fenetrepricecallput.h"

FenetrePriceCallPut::FenetrePriceCallPut(QMdiArea *p, QString type, double S0, double K, double r, double std, double T, int nbSimul) : QWidget(), m_type(type), m_S0(S0), m_K(K), m_r(r), m_std(std), m_T(T), m_nbSimul(nbSimul){

    parent = p;
    layout = new QGridLayout((QWidget*)this);

    serie_price = new QtCharts::QScatterSeries();
    serie_IC_min = new QtCharts::QScatterSeries();
    serie_IC_max = new QtCharts::QScatterSeries();

    m_series.push_back(serie_price);
    m_series.push_back(serie_IC_min);
    m_series.push_back(serie_IC_max);

    m_prix_BS = prixBS(m_type,m_S0,m_K,m_T,m_r,m_std);
    MonteCarlo mc(m_type,m_S0,m_K,m_r,m_std,m_T,m_nbSimul,20);
    mc.callPutVanilla();
    m_prix_MC = *(mc.getTabPrice().end()-1);
    for(int i(0);i<mc.getTabPrice().size();i++){
        serie_IC_min->append((i+1)*m_nbSimul/20,*(mc.getTabICMin().begin()+i));
        serie_price->append((i+1)*m_nbSimul/20,*(mc.getTabPrice().begin()+i));
        serie_IC_max->append((i+1)*m_nbSimul/20,*(mc.getTabICMax().begin()+i));
    }

    chart = new MyCharts(m_series,QString("toto"),0,m_nbSimul,floor(*std::min_element(mc.getTabICMin().begin(),mc.getTabICMin().end())),ceil(*std::max_element(mc.getTabICMax().begin(),mc.getTabICMax().end())));

    result = new QVBoxLayout();
    result->addWidget(new QLabel(m_type));
    result->addWidget(new QLabel(QString("S0: %1").arg(m_S0)));
    result->addWidget(new QLabel(QString("Strike: %1").arg(m_K)));
    result->addWidget(new QLabel(QString("Taux d'interêt: %1").arg(m_r)));
    result->addWidget(new QLabel(QString("Volatilité: %1").arg(m_std)));
    result->addWidget(new QLabel(QString("Maturité: %1 an(s)").arg(m_T)));
    result->addWidget(new QLabel(QString("Prix Black Scholes: %1").arg(m_prix_BS)));
    result->addWidget(new QLabel(QString("Prix Monte Carlo: %1").arg(m_prix_MC)));

    greeks = new QVBoxLayout();
    delta = new QPushButton("Delta");
    gamma = new QPushButton("Gamma");
    vega = new QPushButton("Vega");
    theta = new QPushButton("Theta");
    rho = new QPushButton("Rho");
    greeks->addWidget(delta);
    connect(delta,SIGNAL(clicked()),this,SLOT(displayDelta()));
    greeks->addWidget(gamma);
    connect(gamma,SIGNAL(clicked()),this,SLOT(displayGamma()));
    greeks->addWidget(vega);
    connect(vega,SIGNAL(clicked()),this,SLOT(displayVega()));
    greeks->addWidget(theta);
    connect(theta,SIGNAL(clicked()),this,SLOT(displayTheta()));
    greeks->addWidget(rho);
    connect(rho,SIGNAL(clicked()),this,SLOT(displayRho()));

    layout->addWidget(chart, 0, 0, 2, 1);
    layout->addLayout(result, 0, 1);
    layout->addLayout(greeks, 1, 1);

    setLayout(layout);
}

void FenetrePriceCallPut::displayDelta(){
    QtCharts::QLineSeries *serie_delta = new QtCharts::QLineSeries();
    calculDelta(serie_delta,m_type,m_K,m_T,m_r,m_std,0.1);
    std::vector<QtCharts::QLineSeries*> m_series_delta;
    m_series_delta.push_back(serie_delta);
    MyCharts *chartDelta = new MyCharts(m_series_delta,"toto",0,2*m_K,-1,1);
    QMdiSubWindow *fenetreDelta = new QMdiSubWindow();
    fenetreDelta = parent->addSubWindow(chartDelta);
    fenetreDelta->show();
}

void FenetrePriceCallPut::displayGamma(){
    QtCharts::QLineSeries *serie_gamma = new QtCharts::QLineSeries();
    calculGamma(serie_gamma,m_K,m_T,m_r,m_std,0.1);
    std::vector<QtCharts::QLineSeries*> m_series_gamma;
    m_series_gamma.push_back(serie_gamma);
    MyCharts *chartGamma = new MyCharts(m_series_gamma,"toto",0,2*m_K,0,0);
    QMdiSubWindow *fenetreGamma = new QMdiSubWindow();
    fenetreGamma = parent->addSubWindow(chartGamma);
    fenetreGamma->show();
}

void FenetrePriceCallPut::displayVega(){
    QtCharts::QLineSeries *serie_vega = new QtCharts::QLineSeries();
    calculVega(serie_vega,m_K,m_T,m_r,m_std,0.1);
    std::vector<QtCharts::QLineSeries*> m_series_vega;
    m_series_vega.push_back(serie_vega);
    MyCharts *chartVega = new MyCharts(m_series_vega,"toto",0,2*m_K,0,0);
    QMdiSubWindow *fenetreVega = new QMdiSubWindow();
    fenetreVega = parent->addSubWindow(chartVega);
    fenetreVega->show();
}

void FenetrePriceCallPut::displayTheta(){
    QtCharts::QLineSeries *serie_theta = new QtCharts::QLineSeries();
    calculTheta(serie_theta,m_type,m_K,m_T,m_r,m_std,0.1);
    std::vector<QtCharts::QLineSeries*> m_series_theta;
    m_series_theta.push_back(serie_theta);
    MyCharts *chartTheta = new MyCharts(m_series_theta,"toto",0,2*m_K,0,0);
    QMdiSubWindow *fenetreTheta = new QMdiSubWindow();
    fenetreTheta = parent->addSubWindow(chartTheta);
    fenetreTheta->show();
}

void FenetrePriceCallPut::displayRho(){
    QtCharts::QLineSeries *serie_rho = new QtCharts::QLineSeries();
    calculRho(serie_rho,m_type,m_K,m_T,m_r,m_std,0.1);
    std::vector<QtCharts::QLineSeries*> m_series_rho;
    m_series_rho.push_back(serie_rho);
    MyCharts *chartRho = new MyCharts(m_series_rho,"toto",0,2*m_K,0,0);
    QMdiSubWindow *fenetreRho = new QMdiSubWindow();
    fenetreRho = parent->addSubWindow(chartRho);
    fenetreRho->show();
}
