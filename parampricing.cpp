#include "parampricing.h"

ParamPricing::ParamPricing(QMdiArea *p) : QWidget(){

    parent = p;

    gridLayout = new QGridLayout();

    //box boutons radio type option
    boxType = new QGroupBox("Type", this);
    boutonsType = new QVBoxLayout();
    call = new QRadioButton("Call");
    put = new QRadioButton("Put");
    boutonsType->addWidget(call);
    boutonsType->addWidget(put);
    boxType->setLayout(boutonsType);
    gridLayout->addWidget(boxType, 0, 0);
    call->setChecked(true);
    connect(call, SIGNAL(clicked()), this, SLOT(checkCall()));
    connect(put, SIGNAL(clicked()), this, SLOT(checkPut()));

    //box parametres
    param = new QGroupBox("Paramètres", this);
    inputParam = new QVBoxLayout();
    paramPrix = new QHBoxLayout();
    labelS0 = new QLabel("S0");
    S0 = new QDoubleSpinBox();
    S0->setMaximum(9999999);
    S0->setValue(100.0);
    labelK = new QLabel("Strike");
    K = new QDoubleSpinBox();
    K->setMaximum(9999999);
    K->setValue(110.0);
    paramPrix->addWidget(labelS0);
    paramPrix->addWidget(S0);
    paramPrix->addWidget(labelK);
    paramPrix->addWidget(K);
    paramTime = new QHBoxLayout();
    labelT = new QLabel("Maturité");
    T = new QDoubleSpinBox();
    T->setMaximum(50);
    T->setValue(1.0);
    paramTime->addWidget(labelT);
    paramTime->addWidget(T);
    paramCst = new QHBoxLayout();
    labelr = new QLabel("Taux d'interet");
    r = new QDoubleSpinBox();
    r->setMinimum(0);
    r->setMaximum(1);
    r->setValue(0.05);
    labelStd = new QLabel("Volatilité");
    std = new QDoubleSpinBox();
    std->setMinimum(0);
    std->setMaximum(1);
    std->setValue(0.2);
    paramCst->addWidget(labelr);
    paramCst->addWidget(r);
    paramCst->addWidget(labelStd);
    paramCst->addWidget(std);
    paramSimul = new QHBoxLayout();
    labelNbSimul = new QLabel("Simulation");
    nbSimul = new QDoubleSpinBox();
    nbSimul->setMaximum(99999999);
    nbSimul->setValue(100000);
    paramSimul->addWidget(labelNbSimul);
    paramSimul->addWidget(nbSimul);
    inputParam->addLayout(paramPrix);
    inputParam->addLayout(paramTime);
    inputParam->addLayout(paramCst);
    inputParam->addLayout(paramSimul);
    param->setLayout(inputParam);
    gridLayout->addWidget(param, 1, 0, 1, 2);

    //bloc boutons valider annuler
    boutons = new QHBoxLayout();
    bAnnuler = new QPushButton("Annuler", this);
    bValider = new QPushButton("Valider", this);
    boutons->addWidget(bAnnuler);
    boutons->addWidget(bValider);
    gridLayout->addLayout(boutons, 2, 1);
    connect(bAnnuler, SIGNAL(clicked()), parent, SLOT(closeActiveSubWindow()));
    connect(bValider, SIGNAL(clicked()), this, SLOT(valider()));

    setLayout(gridLayout);

}

void ParamPricing::checkCall(){
    call->setChecked(true);
}

void ParamPricing::checkPut(){
    put->setChecked(true);
}

void ParamPricing::valider(){
    parent->closeActiveSubWindow();
    QString type = "Call";
    if(put->isChecked())
        type = "Put";
    emit compute(type,S0->value(),K->value(),r->value(),std->value(),T->value(),nbSimul->value());
}
