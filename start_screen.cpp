#include "start_screen.h"

extern int widthScreen;
extern int heightScreen;

extern int numPlayers;

Start_screen::Start_screen(QWidget * parent){
    scene = new QGraphicsScene();
    scene -> setSceneRect(0,0,widthScreen,heightScreen);

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(widthScreen,heightScreen);
    show();
}
 /*
int Start_screen::get_numPlayers(){
    return numPlayers;
}
*/
void Start_screen::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_1:
            qDebug() << "1 player";
            numPlayers = 1;
            break;
        case Qt::Key_2:
            qDebug() << "2 players";
            numPlayers = 2;
            break;
        case Qt::Key_3:
            qDebug() << "3 players";
            numPlayers = 3;
            break;
        case Qt::Key_4:
            qDebug() << "4 players";
            numPlayers = 4;
            break;
        default: break;
    }

    if(numPlayers > 0){
        qDebug() << numPlayers;
        this->update();
    }

}
