#ifndef FENETREPARAM_H
#define FENETREPARAM_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QMdiArea>

class FenetreParam : public QWidget{

    Q_OBJECT

public:
    FenetreParam(QMdiArea *p);

public slots:
    void check1D();
    void check2D();
    void checkUniforme();
    void checkNormale();
    void checkTIT();
    void valider();

signals:
    void createGraph(QString type, QString dim, double xm, double xM, double ym, double yM, double m, double s, int n);

private:
    QMdiArea *parent;
    QGridLayout *gridLayout;
    QGroupBox *boxDim, *boxLoi, *boxX, *boxY, *param;
    QRadioButton *dim1, *dim2, *uniforme, *normale, *TIT;
    QHBoxLayout *boutons, *inputX, *inputY, *paramSimul, *paramNorm;
    QVBoxLayout *boutonsDim, *boutonsLoi, *inputDim, *inputParam;
    QPushButton *bAnnuler, *bValider;
    QLabel *labelXMin, *labelXMax, *labelYMin, *labelYMax, *labelNbSimul, *labelMoy, *labelStd;
    QDoubleSpinBox *xMin, *xMax, *yMin, *yMax, *nbSimul, *moy, *std;
};

#endif // FENETREPARAM_H
