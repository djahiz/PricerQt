#include <QApplication>
#include "fenetremain.h"

int main(int argc, char *argv[]){

    QApplication app(argc, argv);

    FenetreMain fenetre;
    fenetre.show();

    return app.exec();
}
