#include "score.h"



Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    score = 0;

    setPlainText(QString("Score: ")+QString::number(score));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times",16));
}

void Score::hitEnemy(){
    score += 10;
    setPlainText(QString("Score: ")+QString::number(score));
}

void Score::enemyHitGround(){
    score -= 10;
    setPlainText(QString("Score: ")+QString::number(score));
}

int Score::getScore(){
    return score;
}
