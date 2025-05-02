#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText("Welcome");
    ui->pushButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #ffccff;"      // Light pink background
        "    color: #660066;"                 // Dark purple text
        "    font-size: 24pt;"
        "    font-weight: bold;"
        "    border: 3px solid #ff99cc;"      // Pink border
        "    border-radius: 30px;"            // Oval shape
        "    padding: 10px 20px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #ffe6f0;"      // Lighter on hover
        "    border-color: #ff66b2;"
        "}"
        );

    // Set background image using Qt resource system
    this->setStyleSheet(
        "QMainWindow {"
        "background-image: url(:/images/weather.png);"
        "background-repeat: no-repeat;"
        "background-position: center;"
        "background-attachment: fixed;"
        "background-size: cover;"
        "}"
        );
}

MainWindow::~MainWindow()
{
    delete ui;
}
