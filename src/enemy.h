#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

#include "game.h"

class Enemy: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Enemy(int playerNo, QGraphicsItem * parent = 0);
public slots:
    void move();
};

#endif // ENEMY_H
