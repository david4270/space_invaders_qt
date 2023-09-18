#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "player.h"


Player::Player(int no, int tp, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    playerNo = no;
    totalPlayers = tp;
    setPixmap(QPixmap(":/images/Player.png").scaledToHeight(100));
}


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

