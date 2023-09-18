#include "game.h"

extern int widthScreen;
extern int heightScreen;

Game::Game(QWidget *parent){
    startScreen = new QState(&machine);
    startTransition = new QState(&machine);
    gameRunning = new QState(&machine);
    gameOver = new QState(&machine);

    QObject::connect(startScreen,SIGNAL(entered()),this,SLOT(startScreenHelper()));
    QObject::connect(startTransition,SIGNAL(entered()),this,SLOT(startTransitionHelper()));
    QObject::connect(gameRunning,SIGNAL(entered()),this,SLOT(gameHelper()));
    QObject::connect(gameOver,SIGNAL(entered()),this,SLOT(gameOverHelper()));

    startScreen->addTransition(this, SIGNAL(toPending()), startTransition);
    startTransition->addTransition(this, SIGNAL(startGame()), gameRunning);
    startTransition->addTransition(this, SIGNAL(backToStart()), startScreen);
    gameRunning->addTransition(this,SIGNAL(finishGame()),gameOver);
    gameOver->addTransition(this,SIGNAL(returnToStart()), startScreen);

    //machine.addState(startScreen);
    //machine.addState(gameRunning);
    //machine.addState(gameOver);
    machine.setInitialState(startScreen);
    machine.start();

    //numPlayers = np;
    //startScreenHelper();
}

int Game::getNumPlayers(){
    return numPlayers;
}

void Game::startScreenHelper(){
    qDebug() << "Running startScreenHelper";
    scene = new QGraphicsScene();
    scene -> setSceneRect(0,0,widthScreen,heightScreen);
    setBackgroundBrush(QBrush(QImage(":/images/Startscreen.png")));

    startText = new QGraphicsTextItem;
    startText->setPlainText("Space Race");
    startText->setFont(QFont("Comic Sans", 48, QFont::Bold));
    startText->setDefaultTextColor(Qt::white);
    startText->setPos(widthScreen/2 - startText->boundingRect().width()/2,heightScreen/5);
    scene->addItem(startText);

    helperText = new QGraphicsTextItem;
    helperText->setPlainText("Press 1-4 to select # of players");
    helperText->setFont(QFont("Aptos", 16));
    helperText->setDefaultTextColor(Qt::white);
    helperText->setPos(widthScreen/2 - helperText->boundingRect().width()/2,4*heightScreen/5);
    scene->addItem(helperText);

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(widthScreen,heightScreen);
}

void Game::startTransitionHelper(){
    qDebug() << "Running startTransitionHelper";

    delete helperText;
    helperText = NULL;

    helperText = new QGraphicsTextItem;
    helperText->setPlainText(QString::number(numPlayers) + " players selected. Press [Enter] or [Space] to proceed");
    helperText->setFont(QFont("Helvetica", 16));
    helperText->setDefaultTextColor(Qt::white);
    helperText->setPos(widthScreen/2 - helperText->boundingRect().width()/2,4*heightScreen/5);
    scene->addItem(helperText);
}

void Game::gameHelper(){
    qDebug() << "Running gameHelper";
    delete startText;
    startText = NULL;

    delete helperText;
    helperText = NULL;

    setBackgroundBrush(QBrush(QImage(":/images/Background2.png")));
    QTimer * timer = new QTimer();
    QTimer * timer2 = new QTimer();

    players = new Player * [numPlayers];
    scores = new Score * [numPlayers];
    healths = new Health * [numPlayers];


    for(int i = 0; i < numPlayers; i++){
        players[i] = new Player(i, numPlayers);
        //players[i]->setFlag(QGraphicsItem::ItemIsFocusable);
        //players[i]->setFocus();
        players[i]->setPos(scene->width() * (2*i + 1)/ (2 * numPlayers), scene->height() - players[i]->pixmap().height());
        players[i]->playerKeys[0] = 0;
        players[i]->playerKeys[1] = 0;
        players[i]->playerKeys[2] = 0;
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

    QObject::connect(timer2, SIGNAL(timeout()), this, SLOT(playerControl()));
    timer2->start(50);

    show();

    for(int i=0; i<numPlayers; i++){
        if(i>0){
            scene->addLine((widthScreen/numPlayers)*i,0,(widthScreen/numPlayers)*i,heightScreen);
        }

        //playerControl(i);
        this->update();
    }

}

void Game::playerControl(){
    int playerActive = 0;
    for(int playerNo = 0; playerNo < numPlayers; playerNo++){
        if(players[playerNo]!=NULL){
            //left or right
            if(players[playerNo]->playerKeys[0]){
                if(players[playerNo]->x() > widthScreen * playerNo/numPlayers + 5){
                    //qDebug() << "player " << playerNo << "Moving left";
                    players[playerNo]->setPos(players[playerNo]->x()-5 ,players[playerNo]->y());
                }
            }
            else if(players[playerNo]->playerKeys[2]){
                if(players[playerNo]->x() < (widthScreen * (playerNo+1)/numPlayers) - players[0]->pixmap().width() -5){
                    //qDebug() << "player " << playerNo << "Moving right";
                    players[playerNo]->setPos(players[playerNo]->x()+5 ,players[playerNo]->y());
                }
            }
            //bullet
            if(players[playerNo]->playerKeys[1]){
                //qDebug() << "player " << playerNo << " shoots bullet";
                Bullet * bullet = new Bullet();
                bullet->setPos(players[playerNo]->x() + (players[playerNo]->pixmap().width()/2),players[playerNo]->y() -  bullet->pixmap().height());
                scene->addItem(bullet);
            }
            playerActive++;
        }
    }

    if(playerActive == 0){
        emit finishGame();
    }
}

void Game::gameOverHelper(){
    qDebug() << "Running gameOverHelper";
    scene->clear();

    // destroy everything, declare winner
}

void Game::keyPressEvent(QKeyEvent *event){

    if(machine.configuration().contains(startScreen)){
        if(event->key() == Qt::Key_1){
            qDebug() << "1 player";
            numPlayers = 1;
            emit toPending();
        }
        else if(event->key() == Qt::Key_2){
            qDebug() << "2 player";
            numPlayers = 2;
            emit toPending();
        }
        else if(event->key() == Qt::Key_3){
            qDebug() << "3 player";
            numPlayers = 3;
            emit toPending();
        }
        else if(event->key() == Qt::Key_4){
            qDebug() << "4 player";
            numPlayers = 4;
            emit toPending();
        }
        //gameHelper();
    }
    if(machine.configuration().contains(startTransition)){
        // "Key_Return" converts to Enter - https://stackoverflow.com/questions/25637171/qt-key-pressevent-enter
        if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Space){
            //qDebug() << "Game started!";
            emit startGame();
        }
        else if(event->key() == Qt::Key_Escape){
            //qDebug() << "Return back to start menu";
            numPlayers = 0;
            emit backToStart();
        }
    }

    if(machine.configuration().contains(gameRunning)){
        switch(event->key()){
            case Qt::Key_Left:
                if(players[0] != NULL){
                    players[0]->playerKeys[0] = 1;
                }
                break;
            case Qt::Key_Up:
                if(players[0] != NULL){
                    players[0]->playerKeys[1] = 1;
                }
                break;
            case Qt::Key_Right:
                if(players[0] != NULL){
                    players[0]->playerKeys[2] = 1;
                }
                break;
            case Qt::Key_A:
                if(numPlayers > 1){
                    if(players[1] != NULL){
                        players[1]->playerKeys[0] = 1;
                    }
                }
                break;
            case Qt::Key_W:
                if(numPlayers > 1){
                    if(players[1] != NULL){
                        players[1]->playerKeys[1] = 1;
                    }
                }
                break;
            case Qt::Key_D:
                if(numPlayers > 1){
                    if(players[1] != NULL){
                        players[1]->playerKeys[2] = 1;
                    }
                }
                break;

            case Qt::Key_J:
                if(numPlayers > 2){
                    if(players[2] != NULL){
                        players[2]->playerKeys[0] = 1;
                    }
                }
                break;
            case Qt::Key_I:
                if(numPlayers > 2){
                    if(players[2] != NULL){
                        players[2]->playerKeys[1] = 1;
                    }
                }
                break;
            case Qt::Key_L:
                if(numPlayers > 2){
                    if(players[2] != NULL){
                        players[2]->playerKeys[2] = 1;
                    }
                }
                break;
            case Qt::Key_Delete:
                if(numPlayers > 3){
                    if(players[3] != NULL){
                        players[3]->playerKeys[0] = 1;
                    }
                }
                break;
            case Qt::Key_Home:
                if(numPlayers > 3){
                    if(players[3] != NULL){
                        players[3]->playerKeys[1] = 1;
                    }
                }
                break;
            case Qt::Key_PageDown:
                if(numPlayers > 3){
                    if(players[3] != NULL){
                        players[3]->playerKeys[2] = 1;
                    }
                }
                break;
            default:
                break;
        }

    }

    if(machine.configuration().contains(gameOver)){
        if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Space || event->key() == Qt::Key_Escape){
            qDebug() << "Return back to start menu";
            numPlayers = 0;
            emit returnToStart();
        }
    }


}

void Game::keyReleaseEvent(QKeyEvent *event){
    if(machine.configuration().contains(gameRunning) && !event->isAutoRepeat()){
        switch(event->key()){
            case Qt::Key_Left:
                if(players[0] != NULL){
                    players[0]->playerKeys[0] = 0;
                }
                break;
            case Qt::Key_Up:
                if(players[0] != NULL){
                    players[0]->playerKeys[1] = 0;
                }
                break;
            case Qt::Key_Right:
                if(players[0] != NULL){
                    players[0]->playerKeys[2] = 0;
                }
                break;
            case Qt::Key_A:
                if(numPlayers > 1){
                    if(players[1] != NULL){
                        players[1]->playerKeys[0] = 0;
                    }
                }
                break;
            case Qt::Key_W:
                if(numPlayers > 1){
                    if(players[1] != NULL){
                        players[1]->playerKeys[1] = 0;
                    }
                }
                break;
            case Qt::Key_D:
                if(numPlayers > 1){
                    if(players[1] != NULL){
                        players[1]->playerKeys[2] = 0;
                    }
                }
                break;

            case Qt::Key_J:
                if(numPlayers > 2){
                    if(players[2] != NULL){
                        players[2]->playerKeys[0] = 0;
                    }
                }
                break;
            case Qt::Key_I:
                if(numPlayers > 2){
                    if(players[2] != NULL){
                        players[2]->playerKeys[1] = 0;
                    }
                }
                break;
            case Qt::Key_L:
                if(numPlayers > 2){
                    if(players[2] != NULL){
                        players[2]->playerKeys[2] = 0;
                    }
                }
                break;
            case Qt::Key_Delete:
                if(numPlayers > 3){
                    if(players[3] != NULL){
                        players[3]->playerKeys[0] = 0;
                    }
                }
                break;
            case Qt::Key_Home:
                if(numPlayers > 3){
                    if(players[3] != NULL){
                        players[3]->playerKeys[1] = 0;
                    }
                }
                break;
            case Qt::Key_PageDown:
                if(numPlayers > 3){
                    if(players[3] != NULL){
                        players[3]->playerKeys[2] = 0;
                    }
                }
                break;
            default:
                break;
        }
     }

}


