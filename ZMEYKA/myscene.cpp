#include "myscene.h"
#include <ctime>
MyScene::MyScene()

{
    srand(time(0));
    setSceneRect(-300,-300,600,600);
    addRect(-300,-300,600,600, QPen(Qt::blue, 3), QBrush(Qt::white, Qt::SolidPattern));

    QGraphicsPixmapItem* snakeHead = new QGraphicsPixmapItem;
    snakeHead->setPixmap(QPixmap(":/new/prefix1/HEAD.jpg").scaled(30, 30));
    snakeHead-> setPos(X,Y);
    addItem(snakeHead);
    snake.push_back(snakeHead);

    apple = new QGraphicsPixmapItem;
    apple->setPixmap(QPixmap(":/new/prefix1/APPLE.png").scaled(30, 30));
    apple -> setPos((rand()%19-9)*30,(rand()% 19-9)*30);
    addItem(apple);
    my_timer = new QTimer;
    connect(my_timer, SIGNAL(timeout()),
            this, SLOT(gameSlot()));
    my_timer-> setInterval(50);
    megaApple = new QGraphicsPixmapItem;
    megaApple->setPixmap(QPixmap(":/new/prefix1/APPLE.png").scaled(30, 30));
    addItem(megaApple);
    my_timer-> start();

}


void MyScene::keyPressEvent(QKeyEvent *event)

{
    if(event->key() == Qt::Key_Up){
        if(snake.size() == 1 || yMove != 30){
        yMove = -30;
        xMove = 0;
    }


    }else if(event ->key() == Qt::Key_Down){
        if(snake.size() == 1 || yMove != -30){
        yMove = 30;
        xMove = 0;
    }

    }else if(event ->key() == Qt::Key_Left){
        if(snake.size() == 1 || xMove != 30){
        yMove = 0;
        xMove = -30;
    }
    }else if(event ->key() == Qt::Key_Right){
        if(snake.size() == 1 || xMove != -30){
        yMove = 0;
        xMove = 30;
    }
    }
}


void MyScene::gameSlot()

{

    int xTemp = X;
    int yTemp = Y;
    X = X+xMove;
    Y = Y+yMove;
    bool islost = false;
    for(int i = 1;i <snake.size();i++){
        if(X == snake[i]->x()&&
                Y == snake[i]->y()){
            islost = true;
            break;
        }
    }

    if(X == 300 || X== -330 || Y== 300 || Y == -330 || islost){
//        my_timer-> stop();
        X =0;
        Y = 0;
        for(int i = 1;i<snake.size();i++){
            removeItem(snake[i]);

        }

        snake.resize(1);
        snake[0]->setPos(X,Y);
        Score = 0;
        emit score(Score);
    }

    if(X == megaApple->x() and Y == megaApple->y()){
        Score = Score + 3;
        emit score(Score);
        megaApple->setPos(-330,-330);
        for(int i = 0;i<3;i++){
            QGraphicsPixmapItem* snakeBody = new QGraphicsPixmapItem;
            snakeBody->setPixmap(QPixmap(":/new/prefix1/BODY.jpg").scaled(30, 30));
            snakeBody-> setPos(X,Y);
            addItem(snakeBody);

            snake.push_back(snakeBody);
        }
    }


    if(X == apple->x() and Y == apple->y()){
        Score++;
        emit score(Score);
         apple -> setPos((rand()%19-9)*30,(rand()% 19-9)*30);
         QGraphicsPixmapItem* snakeBody = new QGraphicsPixmapItem;
         snakeBody->setPixmap(QPixmap(":/new/prefix1/BODY.jpg").scaled(30, 30));
         snakeBody-> setPos(X,Y);
         addItem(snakeBody);
         snake.push_back(snakeBody);

         if(snake.size()>0 && snake.size()%5==0){
//             megaApple -> setRect((rand()%19-9)*30,(rand()% 19-9)*30,30,30);
//             megaApple ->setPen(QPen(Qt::red));
//             megaApple->setBrush(QBrush(Qt::red));
             addItem(megaApple);
         }

    }

    snake[0]->setPos(X,Y);
    int xTemp2, yTemp2;
    for(int i = 1;i<snake.size();i++){
        xTemp2 = snake[i] -> x();
        yTemp2 = snake[i] -> y();
        snake[i] -> setPos(xTemp,yTemp);
        xTemp = xTemp2;
        yTemp = yTemp2;

    }


}
