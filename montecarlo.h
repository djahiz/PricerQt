#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <QString>
#include <vector>
#include "alea.h"

class MonteCarlo {
public:
    MonteCarlo(QString type, double S0, double K, double r, double std, double T, int nbSimul, int nbPoint);
    void callPutVanilla();
    std::vector<double>& getTabPrice();
    std::vector<double>& getTabICMin();
    std::vector<double>& getTabICMax();

private:
    QString m_type;
    int m_nbSimul, m_nbPoint;
    double m_S0, m_K, m_r, m_std, m_T;
    std::vector<double> vectAleatoire, m_price, m_IC_min, m_IC_max;

};

#endif // MONTECARLO_H
