#include "bullet.h"
#include "enemy.h"

extern Game * game;

Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/images/Bullet.png").scaledToHeight(50));

    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);
}

void Bullet::move(){
    QList<QGraphicsItem *> colliding_items = collidingItems();

    foreach(QGraphicsItem * i, colliding_items){
        Enemy * enemy = dynamic_cast<Enemy *>(i);
        if(enemy){

            int idx = int((enemy->x()) / (800 / (game->getNumPlayers())) );

            game->scores[idx]->hitEnemy();

            scene()->removeItem(enemy);
            scene()->removeItem(this);
            delete enemy;
            delete this;
            return;
        }
    }

    setPos(x(), y()-10);

    if(pos().y() < 0){

        scene()->removeItem(this);
        delete this;
    }
}
