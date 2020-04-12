#include "montecarlo.h"

MonteCarlo::MonteCarlo(QString type, double S0, double K, double r, double std, double T, int nbSimul, int nbPoint) :
    m_type(type), m_S0(S0), m_K(K), m_r(r), m_std(std), m_T(T), m_nbSimul(nbSimul), m_nbPoint(nbPoint){

    vectNorm(vectAleatoire,m_nbSimul);
}

void MonteCarlo::callPutVanilla(){
    double sum_temp = m_S0*expf((-(double)(m_std*m_std/2))*m_T);
    double e = expf(-m_r*m_T);
    double sum = 0.0, sum2 = 0.0, m, v, p;
    for(int i(1);i<=m_nbSimul;i++){
        if(m_type == "Call")
            p = std::max(0.0,sum_temp*expf(sqrtf(m_T)*m_std*vectAleatoire[i-1])-m_K*e);
        else
            p= std::max(0.0,m_K*e-sum_temp*expf(sqrtf(m_T)*m_std*vectAleatoire[i-1]));
        sum += p;
        sum2 += p*p;
        if(i%(m_nbSimul/m_nbPoint)==0){
            m = (double)sum/i;
            v = (double)(sum2-i*m*m)/(i-1);
            m_IC_min.push_back(m-1.96*sqrtf((double)v/i));
            m_price.push_back(m);
            m_IC_max.push_back(m+1.96*sqrtf((double)v/i));
        }
    }
}

std::vector<double>& MonteCarlo::getTabPrice(){
    return m_price;
}

std::vector<double>& MonteCarlo::getTabICMin(){
    return m_IC_min;
}

std::vector<double>& MonteCarlo::getTabICMax(){
    return m_IC_max;
}
