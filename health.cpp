#include "health.h"

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent){
    health = 100;
    setPlainText(QString("Health: ")+QString::number(health));
    setDefaultTextColor(Qt::green);
    setFont(QFont("Times",16));

}

void Health::healthDamage(){
    health -= 20;
    setPlainText(QString("Health: ")+QString::number(health));
    if(health < 40){
        setDefaultTextColor(Qt::red);
    }
}

int Health::getHealth(){
    return health;
}
