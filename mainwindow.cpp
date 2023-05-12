#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "cardbutton.h"

#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStyle>
#include <QTimer>
#include <QFrame>
#include <QLabel>
#include <QDebug>
#include <random>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_seconds(0)
{
    ui->setupUi(this);

    m_cardImages.append(QPixmap(":/cartes/01.png"));
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::updateTime);
    this->restartGame();
}

void MainWindow::updateTime()
{
    m_seconds++;
    int minutes = m_seconds / 60;
    int seconds = m_seconds % 60;
    QString timeString = QString("%1:%2")
                             .arg(minutes, 2, 10, QChar('0'))
                             .arg(seconds, 2, 10, QChar('0'));
    m_labelTime->setText(timeString);
}

void MainWindow::startGame()
{
    int ROWS = 0;
    int COLS = 0;
    if (m_easyRadioButton->isChecked()) {
        ROWS = 4;
        COLS = 6;
    }
    else if(m_mediumRadioButton->isChecked()){
        ROWS = 4;
        COLS = 8;

    }
    else if(m_hardRadioButton->isChecked()){
        ROWS = 6;
        COLS = 8;
    }
    m_seconds = 0;

    m_labelTime = new QLabel("00:00");
    m_labelTime->setObjectName("labelTime"); // Nommer le label
    m_labelTime->setAlignment(Qt::AlignHCenter | Qt::AlignTop); // Aligner le texte au centre
    m_labelTime->setStyleSheet("font-size: 20pt; color: white"); // Définir le style

    m_labelTime->setText("00:00");
    m_timer->start(1000);
    // Création d'un conteneur pour les widgets
    QWidget* widgetContainer = new QWidget(this);
    widgetContainer->setObjectName("WidgetContainer");
    widgetContainer->setStyleSheet("QWidget#WidgetContainer { background-color: darkgreen; }");
    // Création des widgets à l'intérieur du conteneur
    QWidget* widget1 = new QWidget(widgetContainer);
    widget1->setObjectName("Widget1");
    widget1->setFixedSize(800, 740);
    QWidget* widget2 = new QWidget(widgetContainer);
    widget2->setObjectName("Widget2");
    widget2->setFixedSize(370, 740);
    // Création d'un layout vertical pour le conteneur
    QHBoxLayout* layout = new QHBoxLayout(widgetContainer);
    layout->addWidget(widget1);
    layout->addWidget(widget2);
    // Ajout du conteneur dans la fenêtre principale
    setCentralWidget(widgetContainer);
    // Ajouter le label au layout du widget_2
    QVBoxLayout* widget2Layout = new QVBoxLayout(widget2);
    QGridLayout* gridLayout = new QGridLayout(widget1);
    QStringList cardImages;
    for (int i = 1; i <= 52; i++) {
        cardImages.append(QString(":/cartes/%1.png").arg(QString::number(i, 10).rightJustified(2, '0')));
    }
    std::random_shuffle(cardImages.begin(), cardImages.end());

    cardImages.resize(ROWS * COLS / 2);

    QStringList clonedCardImages = cardImages + cardImages;

    std::random_shuffle(clonedCardImages.begin(), clonedCardImages.end());
    int cardIndex = 0;
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            QPixmap frontImage(clonedCardImages[cardIndex]);
            QPixmap backImage(":/cartes/back.png");
            CardButton* card = new CardButton(frontImage, backImage, this);
            gridLayout->addWidget(card, i, j);
            connect(card, &CardButton::clicked, card, &CardButton::flip);
            cardIndex++;
        }
    }
    widget1->setStyleSheet("border: 2px solid black");
    widget2->setStyleSheet("border: 2px solid black");
    widget1->setLayout(gridLayout);
    // Créer le bouton
    m_restartButton = new QPushButton("Restart Game", widget2);
    m_restartButton->setObjectName("restartButton");
    m_restartButton->setFixedSize(350, 40);
    // Ajout d'un espace vide en haut pour centrer le bouton
    widget2Layout->addStretch(1);

    // Création du bouton et ajout au widget2Layout
    widget2Layout->addWidget(m_restartButton, 0, Qt::AlignHCenter | Qt::AlignBottom);

    // Ajout d'un espace vide en bas pour pousser le bouton vers le bas
    widget2Layout->addStretch(1);
    // Configurer le bouton
    widget2Layout->addWidget(m_labelTime);

    widget2Layout->addWidget(m_restartButton); // Ajouter le bouton au layout
    connect(m_restartButton, &QPushButton::clicked, this, &MainWindow::restartGame);
}

void MainWindow::restartGame(){

    m_timer->stop();

    // Créer le bouton
    QPushButton* startButton = new QPushButton("Start Game", this);
    startButton->setGeometry(QRect(QPoint(350, 100), QSize(200, 150))); // Position et taille
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startGame);

    // Créer la boîte de groupe pour la difficulté
    QGroupBox* difficultyGroupBox = new QGroupBox("Difficulty", this);
    difficultyGroupBox->setGeometry(QRect(QPoint(350, 300), QSize(200, 100))); // Position et taille
    m_easyRadioButton = new QRadioButton("Easy", difficultyGroupBox);
    m_easyRadioButton->setObjectName("easyRadioButton");
    m_mediumRadioButton = new QRadioButton("Medium", difficultyGroupBox);
    m_mediumRadioButton->setObjectName("mediumRadioButton");
    m_hardRadioButton = new QRadioButton("Hard", difficultyGroupBox);
    m_hardRadioButton->setObjectName("hardRadioButton");
    m_easyRadioButton->setChecked(true);

    // Ajouter les boutons radio au groupe
    QVBoxLayout* difficultyLayout = new QVBoxLayout(difficultyGroupBox);
    difficultyLayout->addWidget(m_easyRadioButton);
    difficultyLayout->addWidget(m_mediumRadioButton);
    difficultyLayout->addWidget(m_hardRadioButton);

    // Créer un widget central
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(startButton);
    mainLayout->addWidget(difficultyGroupBox);

    // Définir le widget central
    setCentralWidget(centralWidget);
}



MainWindow::~MainWindow()
{
    delete ui;
}

