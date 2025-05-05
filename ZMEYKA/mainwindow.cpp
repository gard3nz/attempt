#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{

    ui->setupUi(this);
    myscene = new MyScene;
    ui -> graphicsView -> setScene(myscene);
    connect(myscene, SIGNAL(score(int)),
            this, SLOT(addScore(int)));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addScore(int score)
{
    ui->label->setNum(score);
}
