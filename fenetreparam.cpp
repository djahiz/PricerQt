#include "fenetreparam.h"

FenetreParam::FenetreParam(QMdiArea *p) : QWidget(){

    parent = p;

    gridLayout = new QGridLayout();

    //box boutons radio dimension
    boxDim = new QGroupBox("Dimension", this);
    boutonsDim = new QVBoxLayout();
    dim1 = new QRadioButton("1 dimension");
    dim2 = new QRadioButton("2 dimensions");
    boutonsDim->addWidget(dim1);
    boutonsDim->addWidget(dim2);
    boxDim->setLayout(boutonsDim);
    gridLayout->addWidget(boxDim, 0, 0);
    dim1->setChecked(true);
    connect(dim1, SIGNAL(clicked()), this, SLOT(check1D()));
    connect(dim2, SIGNAL(clicked()), this, SLOT(check2D()));

    //box boutons radio distribution
    boxLoi = new QGroupBox("Distribution", this);
    boutonsLoi = new QVBoxLayout();
    uniforme = new QRadioButton("Uniforme");
    normale = new QRadioButton("Normale");
    TIT = new QRadioButton("T.I.T.");
    boutonsLoi->addWidget(uniforme);
    boutonsLoi->addWidget(normale);
    boutonsLoi->addWidget(TIT);
    boxLoi->setLayout(boutonsLoi);
    gridLayout->addWidget(boxLoi, 1, 0);
    uniforme->setChecked(true);
    connect(uniforme, SIGNAL(clicked()), this, SLOT(checkUniforme()));
    connect(normale, SIGNAL(clicked()), this, SLOT(checkNormale()));
    connect(TIT, SIGNAL(clicked()), this, SLOT(checkTIT()));

    //bloc axes
    inputDim = new QVBoxLayout();
    // axe X
    boxX = new QGroupBox("Axe X");
    inputX = new QHBoxLayout();
    labelXMin = new QLabel("Xmin");
    xMin = new QDoubleSpinBox();
    xMin->setMinimum(-1000);
    xMin->setMaximum(1000);
    labelXMax = new QLabel("Xmax");
    xMax = new QDoubleSpinBox();
    xMax->setMinimum(-1000);
    xMax->setMaximum(1000);
    xMax->setValue(1);
    inputX->addWidget(labelXMin);
    inputX->addWidget(xMin);
    inputX->addWidget(labelXMax);
    inputX->addWidget(xMax);
    boxX->setLayout(inputX);
    inputDim->addWidget(boxX);
    //axe Y
    boxY = new QGroupBox("Axe Y");
    inputY = new QHBoxLayout();
    labelYMin = new QLabel("Ymin");
    yMin = new QDoubleSpinBox();
    yMin->setMinimum(-1000);
    yMin->setMaximum(1000);
    labelYMax = new QLabel("Ymax");
    yMax = new QDoubleSpinBox();
    yMax->setMinimum(-1000);
    yMax->setMaximum(1000);
    yMax->setValue(1);
    inputY->addWidget(labelYMin);
    inputY->addWidget(yMin);
    inputY->addWidget(labelYMax);
    inputY->addWidget(yMax);
    boxY->setLayout(inputY);
    inputDim->addWidget(boxY);
    gridLayout->addLayout(inputDim, 0, 1);

    //box parametres
    param = new QGroupBox("Paramètres", this);
    inputParam = new QVBoxLayout();
    paramSimul = new QHBoxLayout();
    labelNbSimul = new QLabel("Simulation");
    nbSimul = new QDoubleSpinBox();
    nbSimul->setMaximum(99999999);
    paramSimul->addWidget(labelNbSimul);
    paramSimul->addWidget(nbSimul);
    paramNorm = new QHBoxLayout();
    labelMoy = new QLabel("Moyenne");
    moy = new QDoubleSpinBox();
    moy->setMinimum(-1000);
    moy->setMaximum(1000);
    labelStd = new QLabel("Ecart-Type");
    std = new QDoubleSpinBox();
    std->setMinimum(0);
    std->setMaximum(1000);
    std->setValue(1);
    paramNorm->addWidget(labelMoy);
    paramNorm->addWidget(moy);
    paramNorm->addWidget(labelStd);
    paramNorm->addWidget(std);
    inputParam->addLayout(paramSimul);
    inputParam->addLayout(paramNorm);
    param->setLayout(inputParam);
    gridLayout->addWidget(param, 1, 1);

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

void FenetreParam::check1D(){
    if(TIT->isChecked())
        uniforme->setChecked(true);
    dim1->setChecked(true);
    TIT->setDisabled(true);
    boxY->setDisabled(true);
}

void FenetreParam::check2D(){
    dim2->setChecked(true);
    TIT->setDisabled(false);
    boxY->setDisabled(false);
}

void FenetreParam::checkUniforme(){
    boxX->setDisabled(false);
    boxY->setDisabled(false);
    param->setDisabled(false);
    moy->setDisabled(true);
    labelMoy->setDisabled(true);
    std->setDisabled(true);
    labelStd->setDisabled(true);
    uniforme->setChecked(true);
}

void FenetreParam::checkNormale(){
    boxX->setDisabled(false);
    boxY->setDisabled(false);
    param->setDisabled(false);
    moy->setDisabled(false);
    labelMoy->setDisabled(false);
    std->setDisabled(false);
    labelStd->setDisabled(false);
    normale->setChecked(true);
}

void FenetreParam::checkTIT(){
    check2D();
    xMin->setValue(0);
    yMin->setValue(0);
    xMax->setValue(1);
    yMax->setValue(1);
    boxX->setDisabled(true);
    boxY->setDisabled(true);
    param->setDisabled(false);
    moy->setDisabled(true);
    labelMoy->setDisabled(true);
    std->setDisabled(true);
    labelStd->setDisabled(true);
    TIT->setChecked(true);
}

void FenetreParam::valider(){
    parent->closeActiveSubWindow();
    if(dim1->isChecked()){
        if(uniforme->isChecked())
            emit createGraph("uniforme", "1d", xMin->value(), xMax->value(), 0, 0, 0, 0, nbSimul->value());
        if(normale->isChecked())
            emit createGraph("normale", "1d", xMin->value(), xMax->value(), 0, 0, moy->value(), std->value(), nbSimul->value());
    }
    if(dim2->isChecked()){
        if(uniforme->isChecked())
            emit createGraph("uniforme", "2d", xMin->value(), xMax->value(), yMin->value(), yMax->value(), 0, 0, nbSimul->value());
        if(normale->isChecked())
            emit createGraph("normale", "2d", xMin->value(), xMax->value(), yMin->value(), yMax->value(), moy->value(), std->value(), nbSimul->value());
        if(TIT->isChecked())
            emit createGraph("TIT", "2d", xMin->value(), xMax->value(), yMin->value(), yMax->value(), 0, 0, nbSimul->value());
    }
}
