#include "enemy.h"

extern Game * game;

Enemy::Enemy(int playerNo, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    int numPlayers = game -> getNumPlayers();


    int random_number = rand() % (800/numPlayers);
    setPos(random_number + playerNo * (800/numPlayers) + 50, 0);

    setPixmap(QPixmap(":/images/Enemy.png").scaledToHeight(100));
    setRotation(180);

    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    qDebug() << this->pos().x();

    timer->start(35 + rand() % 25);
}

void Enemy::move(){
    QList<QGraphicsItem *> colliding_items = collidingItems();
    int numPlayers = game->getNumPlayers();

    foreach(QGraphicsItem * i, colliding_items){
        Player * player = dynamic_cast<Player *>(i);
        if(player){
            int idx = int((player->x()) / (800 / numPlayers) );
            game -> healths[idx] -> healthDamage();

            if(game -> healths[idx] -> getHealth() == 0){
                scene()->removeItem(player);
                delete player;

                qDebug() << "Player" << idx << "slained";
            }

            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    int randSpeed = 4 + rand() % 4;
    setPos(x(), y()+randSpeed);

    if(pos().y() - pixmap().height() > 600){
        int idx = std::min(int((pos().x()) / (800 / numPlayers) ), numPlayers-1);
        qDebug() << idx << pos().x();
        game->scores[idx]->enemyHitGround();
        scene()->removeItem(this);
        delete this;
    }
}
