#include "enemy.h"

extern Game * game;
extern int widthScreen;
extern int heightScreen;

Enemy::Enemy(int playerNo, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    int numPlayers = game -> getNumPlayers();

    setPixmap(QPixmap(":/images/Enemy.png").scaledToHeight(100));
    setRotation(180);

    int random_number = rand() % ((widthScreen/numPlayers) - (this->pixmap().width())) ;
    setPos(random_number + playerNo * (widthScreen/numPlayers) + (this->pixmap().width()/2), 0);



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
            int idx = int((player->x()) / (widthScreen / numPlayers) );
            if(game->healths[idx]){
                game -> healths[idx] -> healthDamage();
            }


            if(game -> healths[idx] -> getHealth() == 0){
                /*
                scene()->removeItem(player);
                delete player;
                player = NULL;
                */
                scene()->removeItem(game->players[idx]);
                delete game->players[idx];
                game->players[idx] = NULL;


                scene()->removeItem(game->healths[idx]);
                delete game->healths[idx];
                game->healths[idx] = NULL;

                scene()->removeItem(game->scores[idx]);
                delete game->scores[idx];
                game->scores[idx] = NULL;
                qDebug() << "Player" << idx << "slained";
            }

            scene()->removeItem(this);
            delete this;

            return;
        }
    }

    int randSpeed = 4 + rand() % 4;
    setPos(x(), y()+randSpeed);

    if(pos().y() - pixmap().height() > heightScreen){
        int idx = std::min(int((pos().x()) / (widthScreen / numPlayers) ), numPlayers-1);
        qDebug() << idx << pos().x();
        if(game->scores[idx]){
            game->scores[idx]->enemyHitGround();
        }
        scene()->removeItem(this);
        delete this;
    }
}
