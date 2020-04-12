#include "alea.h"

void uniforme1d(QtCharts::QScatterSeries *serie, double xMin, double xMax, int nbSimul){
    std::mt19937 gen;
    gen.seed(time(0));
    std::uniform_real_distribution<double> distribution(0,1);
    for(int i(0);i<nbSimul;i++)
        serie->append(distribution(gen)*abs(xMax-xMin)+xMin,0);
}

void uniforme2d(QtCharts::QScatterSeries *serie, double xMin, double xMax, double yMin, double yMax, int nbSimul){
    std::mt19937 gen;
    gen.seed(time(0));
    std::uniform_real_distribution<double> distribution(0,1);
    for(int i(0);i<nbSimul;i++)
        serie->append(distribution(gen)*abs(xMax-xMin)+xMin,distribution(gen)*abs(yMax-yMin)+yMin);
}

void normale1d(QtCharts::QScatterSeries *serie, double moy, double std, int nbSimul){
    std::mt19937 gen;
    gen.seed(time(0));
    std::uniform_real_distribution<double> distribution(0,1);
    double x1,x2;
    for(int i(0);i<nbSimul;i++){
        x1 = distribution(gen);
        x2 = distribution(gen);
        serie->append(sqrtf(-2*log(x1))*cos(2*M_PI*x2)*std+moy, 0);
    }
}

void normale2d(QtCharts::QScatterSeries *serie, double moy, double std, int nbSimul){
    std::mt19937 gen;
    gen.seed(time(0));
    std::uniform_real_distribution<double> distribution(0,1);
    double x1,x2;
    for(int i(0);i<nbSimul;i++){
        x1 = distribution(gen);
        x2 = distribution(gen);
        serie->append(sqrtf(-2*log(x1))*cos(2*M_PI*x2)*std+moy, sqrtf(-2*log(x1))*sin(2*M_PI*x2)*std+moy);
    }
}

void vectNorm(std::vector<double> &vec, int nbSimul){
    std::mt19937 gen;
    gen.seed(time(0));
    std::uniform_real_distribution<double> distribution(0,1);
    double x1,x2;
    for(int i(0);i<nbSimul;i++){
        x1 = distribution(gen);
        x2 = distribution(gen);
        vec.push_back(sqrtf(-2*log(x1))*cos(2*M_PI*x2));
    }
}
