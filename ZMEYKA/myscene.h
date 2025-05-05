#ifndef MYSCENE_H

#define MYSCENE_H
#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>

class MyScene : public QGraphicsScene

{
    Q_OBJECT

public:

    MyScene();
    void keyPressEvent(QKeyEvent *event) override;

public slots:
    void gameSlot();

signals:
    void score(int);

private:
    int Score = 0;
    std::vector<QGraphicsPixmapItem*> snake;
    QGraphicsPixmapItem *apple, *megaApple;
    QTimer* my_timer;
    int X = 0, Y=0, xMove = 0, yMove = 0;

};


#endif // MYSCENE_H
