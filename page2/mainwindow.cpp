#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QLineEdit>
#include <QTabBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , backgroundImage(":/images/weather.png")
{
    ui->setupUi(this);

    // Make central widget transparent
    ui->centralwidget->setAttribute(Qt::WA_TranslucentBackground);
    ui->centralwidget->setStyleSheet("background: transparent;");

    // Create main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(ui->centralwidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Add stretch to push everything down
    mainLayout->addStretch();

    // Container for bottom elements
    QWidget *bottomWidget = new QWidget(this);
    bottomWidget->setStyleSheet("background: transparent;");
    QVBoxLayout *bottomLayout = new QVBoxLayout(bottomWidget);
    bottomLayout->setContentsMargins(50, 0, 50, 50);
    bottomLayout->setSpacing(15);

    // Search for country field with icon on right
    QWidget *countryContainer = new QWidget(bottomWidget);
    countryContainer->setStyleSheet("background: transparent;");
    QHBoxLayout *countryLayout = new QHBoxLayout(countryContainer);
    countryLayout->setContentsMargins(0, 0, 0, 0);
    countryLayout->setSpacing(0);

    QLineEdit *countrySearch = new QLineEdit(countryContainer);
    countrySearch->setPlaceholderText("Search for a country");
    countrySearch->setStyleSheet(
        "QLineEdit {"
        "   background: rgba(255, 255, 255, 180);"
        "   border: 2px solid #FF69B4;"
        "   border-radius: 15px;"
        "   padding: 10px 35px 10px 15px;"
        "   color: #333333;"
        "   font-size: 14px;"
        "   min-width: 250px;"
        "}"
        "QLineEdit:hover { border-color: #FF1493; }"
        );

    // Magnifying glass button (aligned right)
    QPushButton *countrySearchBtn = new QPushButton(countryContainer);
    countrySearchBtn->setIcon(QIcon(":/images/glass.png"));  // updated icon
    countrySearchBtn->setIconSize(QSize(20, 20));
    countrySearchBtn->setStyleSheet(
        "QPushButton {"
        "   background: transparent;"
        "   border: none;"
        "   padding: 0px 8px 0px 0px;"
        "}"
        "QPushButton:hover { background: rgba(255,255,255,50); }"
        );

    countryLayout->addWidget(countrySearch);
    countryLayout->addWidget(countrySearchBtn);
    bottomLayout->addWidget(countryContainer);

    // Search for city field with icon on right
    QWidget *cityContainer = new QWidget(bottomWidget);
    cityContainer->setStyleSheet("background: transparent;");
    QHBoxLayout *cityLayout = new QHBoxLayout(cityContainer);
    cityLayout->setContentsMargins(0, 0, 0, 0);
    cityLayout->setSpacing(0);

    QLineEdit *citySearch = new QLineEdit(cityContainer);
    citySearch->setPlaceholderText("Search for a city");
    citySearch->setStyleSheet(countrySearch->styleSheet());

    QPushButton *citySearchBtn = new QPushButton(cityContainer);
    citySearchBtn->setIcon(QIcon(":/images/glass.png"));  // updated icon
    citySearchBtn->setIconSize(QSize(20, 20));
    citySearchBtn->setStyleSheet(countrySearchBtn->styleSheet());

    cityLayout->addWidget(citySearch);
    cityLayout->addWidget(citySearchBtn);
    bottomLayout->addWidget(cityContainer);

    // Tab bar for views
    QTabBar *tabBar = new QTabBar(bottomWidget);
    tabBar->addTab("Daily");
    tabBar->addTab("Hourly");
    tabBar->addTab("One Week");
    tabBar->setStyleSheet(
        "QTabBar {"
        "   background: transparent;"
        "   border: none;"
        "}"
        "QTabBar::tab {"
        "   background: rgba(255, 255, 255, 180);"
        "   border: 2px solid #FF69B4;"
        "   border-radius: 15px;"
        "   padding: 8px 20px;"
        "   margin: 0 5px;"
        "   color: #333333;"
        "   font-size: 14px;"
        "}"
        "QTabBar::tab:selected {"
        "   background: rgba(255, 105, 180, 150);"
        "   border-color: #FF1493;"
        "}"
        "QTabBar::tab:hover {"
        "   background: rgba(255, 105, 180, 100);"
        "}"
        );

    bottomLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed));
    bottomLayout->addWidget(tabBar, 0, Qt::AlignHCenter);
    bottomLayout->addStretch(1);

    // Add bottom widget to main layout
    mainLayout->addWidget(bottomWidget, 0, Qt::AlignBottom);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap scaled = backgroundImage.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
    painter.drawPixmap(0, 0, scaled.width(), scaled.height(), scaled);
    QMainWindow::paintEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    update();
}
