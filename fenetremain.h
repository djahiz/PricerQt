#ifndef FENETREMAIN_H
#define FENETREMAIN_H

#include <QtWidgets>
#include "fenetreparam.h"
#include "fenetretirage.h"
#include "parampricing.h"
#include "fenetrepricecallput.h"
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLegendMarker>

class FenetreMain : public QMainWindow
{
    Q_OBJECT

public:
    FenetreMain();
    void setMenu();
    void setActions();

private:
    int height, width;
    QMenu *menuFile, *menuEdit, *menuSimul, *menu1D, *menu2D, *menuPricing, *ssMenuOption;
    QAction *actionQuit, *uniforme1D, *uniforme2D, *normale1D, *normale2D, *TIT2D, *pricingCall, *pricingPut;
    QMdiArea *zoneCentrale;

public slots:
    void choixParametre();
    void newGraph(QString type, QString dim, double xm, double xM, double ym, double yM, double m, double s, int n);
    void choixParamPricing();
    void priceOption(QString type, double S0, double K, double r, double std, double T, int nbSimul);

};

#endif // FENETREMAIN_H
