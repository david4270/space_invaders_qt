#ifndef START_SCREEN_H
#define START_SCREEN_H

#include <QGraphicsView>
#include <QDebug>
#include <QKeyEvent>

class Start_screen: public QGraphicsView{
//private:
    //int numPlayers = 0;
public:
    Start_screen(QWidget * parent = 0);
    //int get_numPlayers();
    void keyPressEvent(QKeyEvent * event);

    QGraphicsScene * scene;
};

#endif // START_SCREEN_H
