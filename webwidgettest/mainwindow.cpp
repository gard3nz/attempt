#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    webView = new QWebEngineView(this);
    webView->load(QUrl("https://example.com"));
    webView->hide();
    ui->widget->layout()->addWidget(webView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    webView->hide();
}


void MainWindow::on_pushButton_2_clicked()
{
    webView->load(QUrl("https://example.com"));
    webView->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    webView->load(QUrl("https://quickdraw.withgoogle.com/?locale=ru"));
    webView->show();
}

