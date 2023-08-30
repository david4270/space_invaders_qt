#include "game.h"

extern int widthScreen;
extern int heightScreen;

Game::Game(QWidget *parent){

    //numPlayers = np;
    numPlayers = 0;

    scene = new QGraphicsScene();
    scene -> setSceneRect(0,0,widthScreen,heightScreen);
    setBackgroundBrush(QBrush(QImage(":/images/Background.png")));

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(widthScreen,heightScreen);


}

int Game::getNumPlayers(){
    return numPlayers;
}

void Game::gameHelper(){
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

    for(int i=1; i<numPlayers; i++){
        scene->addLine((widthScreen/numPlayers)*i,0,(widthScreen/numPlayers)*i,heightScreen);
        this->update();
    }

}

void Game::keyPressEvent(QKeyEvent *event){
    //qDebug() << "Key is pressed" << event->key();
    //qDebug() << numPlayers;

    if(numPlayers == 0){
        if(event->key() == Qt::Key_1){
            qDebug() << "1 player";
            numPlayers = 1;
            gameHelper();
        }
        else if(event->key() == Qt::Key_2){
            qDebug() << "2 player";
            numPlayers = 2;
            gameHelper();
        }
        else if(event->key() == Qt::Key_3){
            qDebug() << "3 player";
            numPlayers = 3;
            gameHelper();
        }
        else if(event->key() == Qt::Key_4){
            qDebug() << "4 player";
            numPlayers = 4;
            gameHelper();
        }
    }
    else{
        if(event->key() == Qt::Key_Left){
            //qDebug() << "Left" << widthScreen *0/numPlayers+5;;
            if(players[0] != NULL){
                if(players[0]->x() > widthScreen * 0/numPlayers + 5){
                    //qDebug() << "Moving left";
                    players[0]->setPos(players[0]->x()-5 ,players[0]->y());
                }
            }

        }
        if(event->key() == Qt::Key_Right){
            //qDebug() << "Right" << widthScreen *1/numPlayers-5;
            if(players[0] != NULL){
                if(players[0]->x() < (widthScreen * 1/numPlayers) - players[0]->pixmap().width() -5){
                    //qDebug() << "Moving right";
                    players[0]->setPos(players[0]->x()+5 ,players[0]->y());
                }
            }

        }
        if(event->key() == Qt::Key_Up){
            if(players[0] != NULL){
                qDebug() << "player 0 shoots bullet";
                Bullet * bullet = new Bullet();
                bullet->setPos(players[0]->x() + (players[0]->pixmap().width()/2),players[0]->y() -  bullet->pixmap().height());
                scene->addItem(bullet);
            }

        }
        if(event->key() == Qt::Key_A && numPlayers > 1){
            if(players[1] != NULL){
                if(players[1]->x() > widthScreen * 1/numPlayers + 5){
                    players[1]->setPos(players[1]->x()-5 ,players[1]->y());
                }
            }
        }
        if(event->key() == Qt::Key_D && numPlayers > 1){
            if(players[1] != NULL){
                if(players[1]->x() < (widthScreen * 2/numPlayers)- players[1]->pixmap().width() - 5){
                    players[1]->setPos(players[1]->x()+5 ,players[1]->y());
                }
            }
        }
        if(event->key() == Qt::Key_W && numPlayers > 1){
            if(players[1] != NULL){
                qDebug() << "player 1 shoots bullet";
                Bullet * bullet = new Bullet();
                bullet->setPos(players[1]->x() + (players[1]->pixmap().width()/2),players[1]->y() - bullet->pixmap().height());
                scene->addItem(bullet);
            }
        }
        if(event->key() == Qt::Key_J && numPlayers > 2){
            if(players[2] != NULL){
                if(players[2]->x() > widthScreen * 2/numPlayers + 5){
                    players[2]->setPos(players[2]->x()-5 ,players[2]->y());
                }
            }
        }
        if(event->key() == Qt::Key_L && numPlayers > 2){
            if(players[2] != NULL){
                if(players[2]->x() < (widthScreen * 3/numPlayers)- players[2]->pixmap().width() -5){
                    players[2]->setPos(players[2]->x()+5 ,players[2]->y());
                }
            }
        }
        if(event->key() == Qt::Key_I && numPlayers > 2){
            if(players[2] != NULL){
                Bullet * bullet = new Bullet();
                bullet->setPos(players[2]->x()+ (players[2]->pixmap().width()/2),players[2]->y() - bullet->pixmap().height());
                scene->addItem(bullet);
            }
        }
        if(event->key() == Qt::Key_Delete && numPlayers > 3){
            if(players[3] != NULL){
                if(players[3]->x() > widthScreen * 3/numPlayers + 5){
                    players[3]->setPos(players[3]->x()-5 ,players[3]->y());
                }
            }
        }
        if(event->key() == Qt::Key_PageDown && numPlayers > 3){
            if(players[3] != NULL){
                if(players[3]->x() < (widthScreen * 4/numPlayers) - players[3]->pixmap().width() -5){
                    players[3]->setPos(players[3]->x()+5 ,players[3]->y());
                }
            }
        }
        if(event->key() == Qt::Key_Home && numPlayers > 3){
            if(players[3] != NULL){
                Bullet * bullet = new Bullet();
                bullet->setPos(players[3]->x()+ (players[3]->pixmap().width()/2),players[3]->y() - bullet->pixmap().height());
                scene->addItem(bullet);
            }
        }
    }


}
