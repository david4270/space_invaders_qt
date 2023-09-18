#ifndef PLAYER_H
#define PLAYER_H

#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsScene>

#include <QDebug>

#include "score.h"
#include "health.h"



class Player: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(int no = 0, int tp = 1, QGraphicsItem *parent = 0);

    int getPlayerNo();
    void setPlayerNo(int no);

    int playerKeys[3]; // 0 left, 1 bullet, 2 right

    //Score * score;
    //Health * health;
public slots:
    void spawn();
private:
    int playerNo;
    int totalPlayers;
};

#endif // PLAYER_H
