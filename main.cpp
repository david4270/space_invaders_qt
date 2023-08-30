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

    heightScreen = 720;
    widthScreen = 1280;

    //game = new Game(numPlayers);
    game = new Game();
    game->setFocus();

    game -> show();

    return a.exec();
}
