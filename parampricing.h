#ifndef PARAMPRICING_H
#define PARAMPRICING_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QMdiArea>

class ParamPricing : public QWidget{

    Q_OBJECT

public:
    ParamPricing(QMdiArea *p);

public slots:
    void checkCall();
    void checkPut();
    void valider();

signals:
    void compute(QString type, double S0, double K, double r, double std, double T, int nbSimul);

private:
    QMdiArea *parent;
    QGridLayout *gridLayout;
    QGroupBox *boxType, *param;
    QRadioButton *call, *put;
    QHBoxLayout *boutons, *paramSimul, *paramPrix, *paramTime, *paramCst;
    QVBoxLayout *boutonsType, *inputParam;
    QPushButton *bAnnuler, *bValider;
    QLabel *labelS0, *labelK, *labelT, *labelr, *labelStd, *labelNbSimul;
    QDoubleSpinBox *S0, *K, *T, *r, *std, *nbSimul;
};

#endif // PARAMPRICING_H
