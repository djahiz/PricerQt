#ifndef ALEA_H
#define ALEA_H

#include <random>
#include <cmath>
#include <time.h>
#include <QtCharts/QScatterSeries>
#include <vector>

void uniforme1d(QtCharts::QScatterSeries *serie, double xMin, double xMax, int nbSimul);
void uniforme2d(QtCharts::QScatterSeries *serie, double xMin, double xMax, double yMin, double yMax, int nbSimul);
void normale1d(QtCharts::QScatterSeries *serie, double moy, double std, int nbSimul);
void normale2d(QtCharts::QScatterSeries *serie, double moy, double std, int nbSimul);
void vectNorm(std::vector<double> &vec, int nbSimul);

#endif // ALEA_H
