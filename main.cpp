#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QStackedWidget>

#include "game.h"


Game * game;
int heightScreen;
int widthScreen;
int numPlayers = 0;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    heightScreen = 600;
    widthScreen = 800;
    int numPlayers = 2;


    //game = new Game(numPlayers);
    game = new Game();
    game->setFocus();

    game -> show();


    return a.exec();
}
