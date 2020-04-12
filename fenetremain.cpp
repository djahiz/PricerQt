#include "fenetremain.h"

FenetreMain::FenetreMain()
{
    width = 800;
    height = 600;
    setMinimumSize(width,height);
    setMenu();
    setActions();
    zoneCentrale = new QMdiArea();
    setCentralWidget(zoneCentrale);
}

void FenetreMain::setMenu(){
    menuFile = menuBar()->addMenu("Fichier");
    menuEdit = menuBar()->addMenu("Edition");
    menuSimul = menuBar()->addMenu("Simulation");
    menu1D = menuSimul->addMenu("1 dimension");
    menu2D = menuSimul->addMenu("2 dimensions");
    menuPricing = menuBar()->addMenu("Pricing");
    ssMenuOption = menuPricing->addMenu("Options");
}

void FenetreMain::setActions(){
    actionQuit = new QAction("Quitter", this);
    menuFile->addAction(actionQuit);
    connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

    uniforme1D = new QAction("Uniforme", this);
    menu1D->addAction(uniforme1D);
    connect(uniforme1D, SIGNAL(triggered()), this, SLOT(choixParametre()));

    uniforme2D = new QAction("Uniforme", this);
    menu2D->addAction(uniforme2D);
    connect(uniforme2D, SIGNAL(triggered()), this, SLOT(choixParametre()));

    normale1D = new QAction("Normale", this);
    menu1D->addAction(normale1D);
    connect(normale1D, SIGNAL(triggered()), this, SLOT(choixParametre()));

    normale2D = new QAction("Normale", this);
    menu2D->addAction(normale2D);
    connect(normale2D, SIGNAL(triggered()), this, SLOT(choixParametre()));

    TIT2D = new QAction("T.I.T.", this);
    menu2D->addAction(TIT2D);
    connect(TIT2D, SIGNAL(triggered()), this, SLOT(choixParametre()));

    pricingCall = new QAction("Call", this);
    ssMenuOption->addAction(pricingCall);
    connect(pricingCall, SIGNAL(triggered()), this, SLOT(choixParamPricing()));

    pricingPut = new QAction("Put", this);
    ssMenuOption->addAction(pricingPut);
    connect(pricingPut, SIGNAL(triggered()), this, SLOT(choixParamPricing()));
}

void FenetreMain::choixParametre(){
    FenetreParam *fenetreParam = new FenetreParam(zoneCentrale);
    connect(fenetreParam, SIGNAL(createGraph(QString,QString,double,double,double,double,double,double,int)), this, SLOT(newGraph(QString,QString,double,double,double,double,double,double,int)));

    if(sender() == uniforme1D){
        fenetreParam->check1D();
        fenetreParam->checkUniforme();
    }
    else if(sender() == uniforme2D){
        fenetreParam->check2D();
        fenetreParam->checkUniforme();
    }
    else if(sender() == normale1D){
        fenetreParam->check1D();
        fenetreParam->checkNormale();
    }
    else if(sender() == normale2D){
        fenetreParam->check2D();
        fenetreParam->checkNormale();
    }
    else if(sender() == TIT2D){
        fenetreParam->check2D();
        fenetreParam->checkTIT();
    }
    else{
        fenetreParam->check1D();
        fenetreParam->checkUniforme();
    }

    QMdiSubWindow *sousFenetre = zoneCentrale->addSubWindow((QWidget*)fenetreParam);

    sousFenetre->show();
}

void FenetreMain::newGraph(QString type, QString dim, double xm, double xM, double ym, double yM, double m, double s, int n){
    FenetreTirage *fenetreTirage = new FenetreTirage(type,dim,xm,xM,ym,yM,m,s,n);
    QMdiSubWindow *sousFenetre = zoneCentrale->addSubWindow(fenetreTirage);
    sousFenetre->showMaximized();
}

void FenetreMain::choixParamPricing(){
    ParamPricing *fenetreParam = new ParamPricing(zoneCentrale);
    connect(fenetreParam, SIGNAL(compute(QString,double,double,double,double,double,int)), this, SLOT(priceOption(QString,double,double,double,double,double,int)));

    if(sender() == pricingCall)
        fenetreParam->checkCall();
    else
        fenetreParam->checkPut();

    QMdiSubWindow *sousFenetre = zoneCentrale->addSubWindow((QWidget*)fenetreParam);

    sousFenetre->show();
}

void FenetreMain::priceOption(QString type, double S0, double K, double r, double std, double T, int nbSimul){
    FenetrePriceCallPut *fenetrePrice = new FenetrePriceCallPut(zoneCentrale,type,S0,K,r,std,T,nbSimul);
    QMdiSubWindow *sousFenetre = zoneCentrale->addSubWindow(fenetrePrice);
    sousFenetre->showMaximized();
}
