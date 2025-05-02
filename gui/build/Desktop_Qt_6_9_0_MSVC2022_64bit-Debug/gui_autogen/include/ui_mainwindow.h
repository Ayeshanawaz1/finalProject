/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, -10, 891, 671));
        label->setStyleSheet(QString::fromUtf8("this->setStyleSheet(\n"
"    \"QMainWindow {\"\n"
"    \"   background-image: url(:/images/weather.png);\"\n"
"    \"   background-repeat: no-repeat;\"\n"
"    \"   background-position: center;\"\n"
"    \"   background-attachment: fixed;\"\n"
"    \"   background-size: cover;\"\n"
"    \"}\"\n"
");\n"
""));
        label->setPixmap(QPixmap(QString::fromUtf8("weather.png")));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(270, 0, 241, 241));
        label_2->setStyleSheet(QString::fromUtf8("border-image: url(:/images/cloud.png);"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(270, 240, 291, 51));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(250, 290, 281, 61));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(270, 420, 221, 71));
        pushButton->setStyleSheet(QString::fromUtf8("ui->pushButton->setText(\"Welcome\");\n"
"ui->pushButton->setStyleSheet(\n"
"    \"QPushButton {\"\n"
"    \"    background-color: #ffccff;\"      // Light pink background\n"
"    \"    color: #660066;\"                 // Dark purple text\n"
"    \"    font-size: 24pt;\"\n"
"    \"    font-weight: bold;\"\n"
"    \"    border: 3px solid #ff99cc;\"      // Pink border\n"
"    \"    border-radius: 30px;\"            // Oval shape\n"
"    \"    padding: 10px 20px;\"\n"
"    \"}\"\n"
"    \"QPushButton:hover {\"\n"
"    \"    background-color: #ffe6f0;\"      // Lighter on hover\n"
"    \"    border-color: #ff66b2;\"\n"
"    \"}\"\n"
");\n"
""));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 18));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QString());
        label_2->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:36pt; font-weight:700; color:#ffffff;\">WEATHER </span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:36pt; font-weight:700; color:#ffff00;\">FORECASTS</span></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Welcome", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
