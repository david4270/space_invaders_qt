#include "health.h"

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent){
    health = 100;
    setPlainText(QString("Health: ")+QString::number(health));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));

}

void Health::healthDamage(){
    health -= 20;
    setPlainText(QString("Health: ")+QString::number(health));
}

int Health::getHealth(){
    return health;
}
