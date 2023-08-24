#include "game.h"

Game::Game(int np, QWidget *parent){

    numPlayers = np;

    scene = new QGraphicsScene();
    scene -> setSceneRect(0,0,800,600);
    setBackgroundBrush(QBrush(QImage(":/images/Background.png")));

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    QTimer * timer = new QTimer();

    players = new Player * [numPlayers];
    scores = new Score * [numPlayers];
    healths = new Health * [numPlayers];


    for(int i = 0; i < numPlayers; i++){
        players[i] = new Player(i, numPlayers);
        //players[i]->setFlag(QGraphicsItem::ItemIsFocusable);
        //players[i]->setFocus();
        players[i]->setPos(scene->width() * (2*i + 1)/ (2 * numPlayers), scene->height() - players[i]->pixmap().height());
        // add item to the scene
        scene->addItem(players[i]);

        scores[i] = new Score();
        scores[i]->setPos( ((scene->width() * (2*i))/ (2 * numPlayers))+5, 5);
        scene->addItem(scores[i]);

        healths[i] = new Health();
        healths[i]->setPos( ((scene->width() * (2*i))/ (2 * numPlayers))+5, 30);
        scene->addItem(healths[i]);

        QObject::connect(timer, SIGNAL(timeout()), players[i], SLOT(spawn()));
    }

    timer->start(1800 + rand() % 400);

    show();

}

int Game::getNumPlayers(){
    return numPlayers;
}

void Game::keyPressEvent(QKeyEvent *event){
    //qDebug() << "Key is pressed" << event->key();
    //qDebug() << numPlayers;
    if(event->key() == Qt::Key_Left){
        //qDebug() << "Left" << 800 *0/numPlayers+5;;
        if(players[0]){
            if(players[0]->x() > 800 *0/numPlayers+5){
                //qDebug() << "Moving left";
                players[0]->setPos(players[0]->x()-5 ,players[0]->y());
            }
        }

    }
    if(event->key() == Qt::Key_Right){
        //qDebug() << "Right" << 800 *1/numPlayers-5;
        if(players[0]){
            if(players[0]->x() < 800 * 1/numPlayers-5){
                //qDebug() << "Moving right";
                players[0]->setPos(players[0]->x()+5 ,players[0]->y());
            }
        }

    }
    if(event->key() == Qt::Key_Up){
        if(players[0]){
            Bullet * bullet = new Bullet();
            bullet->setPos(players[0]->x(),players[0]->y());
            scene->addItem(bullet);
        }

    }
    if(event->key() == Qt::Key_A && numPlayers > 1){
        if(players[1]){
            if(players[1]->x() > 800 * 1/numPlayers + 5){
                players[1]->setPos(players[1]->x()-5 ,players[1]->y());
            }
        }
    }
    if(event->key() == Qt::Key_D && numPlayers > 1){
        if(players[1]){
            if(players[1]->x() < 800 * 2/numPlayers - 5){
                players[1]->setPos(players[1]->x()+5 ,players[1]->y());
            }
        }
    }
    if(event->key() == Qt::Key_W && numPlayers > 1){
        if(players[1]){
            Bullet * bullet = new Bullet();
            bullet->setPos(players[1]->x(),players[1]->y());
            scene->addItem(bullet);
        }
    }
    if(event->key() == Qt::Key_J && numPlayers > 2){
        if(players[2]){
            if(players[2]->x() > 800 * 2/numPlayers + 5){
                players[2]->setPos(players[2]->x()-5 ,players[2]->y());
            }
        }
    }
    if(event->key() == Qt::Key_L && numPlayers > 2){
        if(players[2]){
            if(players[2]->x() < 800 * 3/numPlayers -5){
                players[2]->setPos(players[2]->x()+5 ,players[2]->y());
            }
        }
    }
    if(event->key() == Qt::Key_I && numPlayers > 2){
        if(players[2]){
            Bullet * bullet = new Bullet();
            bullet->setPos(players[2]->x(),players[2]->y());
            scene->addItem(bullet);
        }
    }
    if(event->key() == Qt::Key_Delete && numPlayers > 3){
        if(players[3]){
            if(players[3]->x() > 800 * 3/numPlayers + 5){
                players[3]->setPos(players[3]->x()-5 ,players[3]->y());
            }
        }
    }
    if(event->key() == Qt::Key_PageDown && numPlayers > 3){
        if(players[3]){
            if(players[3]->x() < 800 * 4/numPlayers -5){
                players[3]->setPos(players[3]->x()+5 ,players[3]->y());
            }
        }
    }
    if(event->key() == Qt::Key_Home && numPlayers > 3){
        if(players[3]){
            Bullet * bullet = new Bullet();
            bullet->setPos(players[3]->x(),players[3]->y());
            scene->addItem(bullet);
        }
    }

}
