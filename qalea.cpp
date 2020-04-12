#include "qalea.h"

double frac(double x){
    return x-floor(x);
}

void TIT2d(QtCharts::QScatterSeries *serie, int nbSimul){
    for(int i(1);i<=nbSimul;i++){
        serie->append(frac(sqrtf(2)*i), frac(sqrtf(3)*i));
    }
}
