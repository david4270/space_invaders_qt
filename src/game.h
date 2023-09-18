#ifndef GAME_H
#define GAME_H


#include <QGraphicsView>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>

#include <QState>
#include <QAbstractState>
#include <QStateMachine>
#include <QSignalTransition>
#include <QKeyEventTransition>

#include <QGraphicsTextItem>
#include <QFont>

#include "player.h"
#include "score.h"
#include "health.h"
#include "bullet.h"


class Game: public QGraphicsView{
    Q_OBJECT
private:
    int numPlayers = 0;
    int winnerIdx = -1;
    int activePlayer[4];

    QStateMachine machine;
    QState * startScreen;
    QState * startTransition;
    QState * gameRunning;
    QState * gameOver;

public:
    QGraphicsTextItem * startText;
    QGraphicsTextItem * helperText;

    QGraphicsScene * scene;
    Player ** players;
    Score ** scores;
    Health ** healths;

    Game(QWidget * parent = 0);
    int getNumPlayers();
    void keyReleaseEvent(QKeyEvent * event);


public slots:
    void startScreenHelper();
    void startTransitionHelper();
    void gameHelper();
    void playerControl();
    void gameOverHelper();

    void keyPressEvent(QKeyEvent * event);


signals:
    Q_SIGNAL void toPending();
    Q_SIGNAL void startGame();
    Q_SIGNAL void backToStart();
    Q_SIGNAL void finishGame();
    Q_SIGNAL void returnToStart();
};

#endif // GAME_H
