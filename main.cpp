#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QStackedWidget>

#include "game.h"

Game * game;
int heightScreen;
int widthScreen;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    QGraphicsScene * startScreen = new QGraphicsScene();
    startScreen -> setSceneRect(0,0,800,600);
    /*
    QGraphicsView * startView = new QGraphicsView(startScreen);

    startView -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    startView -> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    startView -> setFixedSize(800,600);

    startView -> show();
    */
    setScene(startScreen);

    int numPlayers = 2; //by default

    heightScreen = 600;
    widthScreen = 800;

    game = new Game(numPlayers);

    game->setFocus();

    game -> show();

    return a.exec();
}
