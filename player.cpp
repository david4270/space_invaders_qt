#include "player.h"
#include "bullet.h"
#include "enemy.h"


Player::Player(int no, int tp, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    playerNo = no;
    totalPlayers = tp;
    setPixmap(QPixmap(":/images/Player.png").scaledToHeight(100));
}
/*
void Player::keyPressEvent(QKeyEvent *event){
    //qDebug() << "Player knows that you pressed the key";
    //qDebug() << playerNo;

    switch(playerNo){
        case 0:
            switch(event->key()){
                case Qt::Key_Left:
                    if(pos().x() > 800 * (playerNo/totalPlayers)){
                        setPos(x()-5 ,y());
                    }
                    break;
                case Qt::Key_Right:
                    if(pos().x() < 800 * ((playerNo+1)/totalPlayers)){
                        setPos(x()+5 ,y());
                    }
                    break;
                case Qt::Key_Up:
                    Bullet * bullet = new Bullet();
                    bullet->setPos(x(),y());
                    scene()->addItem(bullet);
                    break;
            }
            break;
        case 1:
            switch(event->key()){
                case Qt::Key_A:
                    if(pos().x() > 800 * (playerNo/totalPlayers)){
                        setPos(x()-5 ,y());
                    }
                    break;
                case Qt::Key_D:
                    if(pos().x() < 800 * ((playerNo+1)/totalPlayers)){
                        setPos(x()+5 ,y());
                    }
                    break;
                case Qt::Key_W:
                    Bullet * bullet = new Bullet();
                    bullet->setPos(x(),y());
                    scene()->addItem(bullet);
                    break;
            }
            break;
        case 2:
            switch(event->key()){
                case Qt::Key_J:
                    if(pos().x() > 800 * (playerNo/totalPlayers)){
                        setPos(x()-5 ,y());
                    }
                    break;
                case Qt::Key_L:
                    if(pos().x() < 800 * ((playerNo+1)/totalPlayers)){
                        setPos(x()+5 ,y());
                    }
                    break;
                case Qt::Key_I:
                    Bullet * bullet = new Bullet();
                    bullet->setPos(x(),y());
                    scene()->addItem(bullet);
                    break;
            }
            break;
        case 3:
            switch(event->key()){
                case Qt::Key_Delete:
                    if(pos().x() > 800 * (playerNo/totalPlayers)){
                        setPos(x()-5 ,y());
                    }
                    break;
                case Qt::Key_PageDown:
                    if(pos().x() < 800 * ((playerNo+1)/totalPlayers)){
                        setPos(x()+5 ,y());
                    }
                    break;
                case Qt::Key_Home:
                    Bullet * bullet = new Bullet();
                    bullet->setPos(x(),y());
                    scene()->addItem(bullet);
                    break;
            }
            break;
    }



}
*/
int Player::getPlayerNo(){
    return playerNo;
}

void Player::setPlayerNo(int no){
    playerNo = no;
}

void Player::spawn(){
    Enemy * enemy = new Enemy(playerNo);
    scene()->addItem(enemy);
}
