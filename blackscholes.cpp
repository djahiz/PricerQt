#include "blackscholes.h"

double prixBS(QString type, double S0, double K, double T, double r, double std){
    if(type == "Call")
        return prixCall(S0,K,T,r,std);
    return prixPut(S0,K,T,r,std);
}

double prixCall(double S0, double K, double T, double r, double std){
    return S0*normFDR(calculD1(S0,K,r,std,T))-K*expf(-r*T)*normFDR(calculD2(S0,K,r,std,T));
}

double prixPut(double S0, double K, double T, double r, double std){
    return K*expf(-r*T)*normFDR(-calculD2(S0,K,r,std,T))-S0*normFDR(-calculD1(S0,K,r,std,T));
}

double calculD1(double S0, double K, double r, double std, double T){
    return (double)(log(S0/K)+(r+std*std/2)*T)/(std*sqrtf(T));
}

double calculD2(double S0, double K, double r, double std, double T){
    return calculD1(S0,K,r,std,T)-std*sqrtf(T);
}

double normFDR(double x){
    return (double)(1+erf((double)x/sqrtf(2)))/2;
}

double normDis(double x){
    return (double)(expf(-x*x/2)/(sqrtf(2*M_PI)));
}

void calculDelta(QtCharts::QLineSeries *serie, QString type, double K, double T, double r, double std, double pas){
    if(type == "Call")
        deltaCall(serie,K,T,r,std,pas);
    else
        deltaPut(serie,K,T,r,std,pas);
}

void deltaCall(QtCharts::QLineSeries *serie, double K, double T, double r, double std, double pas){
    for(int i(0);i<=2*K/pas;i++){
        serie->append(i*pas,normFDR(calculD1(i*pas,K,r,std,T)));
    }
}
void deltaPut(QtCharts::QLineSeries *serie, double K, double T, double r, double std, double pas){
    for(int i(0);i<=2*K/pas;i++){
        serie->append(i*pas,normFDR(calculD1(i*pas,K,r,std,T))-1);
    }
}

void calculGamma(QtCharts::QLineSeries *serie, double K, double T, double r, double std, double pas){
    for(int i(0);i<=2*K/pas;i++){
        serie->append(i*pas,normDis(calculD1(i*pas,K,r,std,T))/(i*pas*std*sqrtf(T)));
    }
}

void calculVega(QtCharts::QLineSeries *serie, double K, double T, double r, double std, double pas){
    for(int i(0);i<=2*K/pas;i++){
        serie->append(i*pas,normDis(calculD1(i*pas,K,r,std,T))*i*pas*sqrtf(T));
    }
}

void calculTheta(QtCharts::QLineSeries *serie, QString type, double K, double T, double r, double std, double pas){
    if(type == "Call")
        thetaCall(serie,K,T,r,std,pas);
    else
        thetaPut(serie,K,T,r,std,pas);
}

void thetaCall(QtCharts::QLineSeries *serie, double K, double T, double r, double std, double pas){
    for(int i(0);i<=2*K/pas;i++){
        serie->append(i*pas,(-i)*pas*normDis(calculD1(i*pas,K,r,std,T))*std/(double)(2*sqrtf(T))-r*K*expf(-r*T)*normFDR(calculD2(i*pas,K,r,std,T)));
    }
}
void thetaPut(QtCharts::QLineSeries *serie, double K, double T, double r, double std, double pas){
    for(int i(0);i<=2*K/pas;i++){
        serie->append(i*pas,(-i)*pas*normDis(calculD1(i*pas,K,r,std,T))*std/(double)(2*sqrtf(T))+r*K*expf(-r*T)*normFDR(calculD2(i*pas,K,r,std,T)));
    }
}

void calculRho(QtCharts::QLineSeries *serie, QString type, double K, double T, double r, double std, double pas){
    if(type == "Call")
        rhoCall(serie,K,T,r,std,pas);
    else
        rhoPut(serie,K,T,r,std,pas);
}

void rhoCall(QtCharts::QLineSeries *serie, double K, double T, double r, double std, double pas){
    for(int i(0);i<=2*K/pas;i++){
        serie->append(i*pas,K*T*expf(-r*T)*normFDR(calculD2(i*pas,K,r,std,T)));
    }
}
void rhoPut(QtCharts::QLineSeries *serie, double K, double T, double r, double std, double pas){
    for(int i(0);i<=2*K/pas;i++){
        serie->append(i*pas,-K*T*expf(-r*T)*normFDR(-calculD2(i*pas,K,r,std,T)));
    }
}
