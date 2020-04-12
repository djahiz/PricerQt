#ifndef BLACKSCHOLES_H
#define BLACKSCHOLES_H

#include <cmath>
#include <QString>
#include <QtCharts/QLineSeries>

double prixBS(QString type, double S0, double K, double T, double r, double std);
double prixCall(double S0, double K, double T, double r, double std);
double prixPut(double S0, double K, double T, double r, double std);
double calculD1(double S0, double K, double r, double std, double T);
double calculD2(double S0, double K, double r, double std, double T);
double normFDR(double x);
double normDis(double x);
void calculDelta(QtCharts::QLineSeries *serie, QString type, double K, double T, double r, double std, double pas);
void deltaCall(QtCharts::QLineSeries *serie, double K, double T, double r, double std, double pas);
void deltaPut(QtCharts::QLineSeries *serie, double K, double T, double r, double std, double pas);
void calculGamma(QtCharts::QLineSeries *serie, double K, double T, double r, double std, double pas);
void calculVega(QtCharts::QLineSeries *serie, double K, double T, double r, double std, double pas);
void calculTheta(QtCharts::QLineSeries *serie, QString type, double K, double T, double r, double std, double pas);
void thetaCall(QtCharts::QLineSeries *serie, double K, double T, double r, double std, double pas);
void thetaPut(QtCharts::QLineSeries *serie, double K, double T, double r, double std, double pas);
void calculRho(QtCharts::QLineSeries *serie, QString type, double K, double T, double r, double std, double pas);
void rhoCall(QtCharts::QLineSeries *serie, double K, double T, double r, double std, double pas);
void rhoPut(QtCharts::QLineSeries *serie, double K, double T, double r, double std, double pas);

#endif // BLACKSCHOLES_H
