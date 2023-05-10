#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "cardbutton.h"

#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_cardImages.append(QPixmap(":/cartes/01.png"));

    // Créer le bouton
    QPushButton *startButton = new QPushButton("Start Game", this);

    // Configurer le bouton
    startButton->setGeometry(QRect(QPoint(350, 100), QSize(200, 150))); // Position et taille
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startGame);

    // Créer la boîte de groupe pour la difficulté
    QGroupBox* difficultyGroupBox = new QGroupBox("Difficulty", this);
    difficultyGroupBox->setGeometry(QRect(QPoint(350, 300), QSize(200, 100))); // Position et taille
    m_easyRadioButton = new QRadioButton("Easy", difficultyGroupBox); // Stocker un pointeur vers le bouton radio "Easy"
    m_easyRadioButton->setObjectName("easyRadioButton"); // Nommer le bouton radio
    m_mediumRadioButton = new QRadioButton("Medium", difficultyGroupBox); // Stocker un pointeur vers le bouton radio "medium"
    m_mediumRadioButton->setObjectName("mediumRadioButton"); // Nommer le bouton radio
    m_hardRadioButton = new QRadioButton("Hard", difficultyGroupBox); // Stocker un pointeur vers le bouton radio "hard"
    m_hardRadioButton->setObjectName("hardRadioButton"); // Nommer le bouton radio
    m_easyRadioButton->setChecked(true); // Sélectionner le bouton radio "Easy" par défaut

    // Ajouter les boutons radio au groupe
    QVBoxLayout *difficultyLayout = new QVBoxLayout;
    difficultyLayout->addWidget(m_easyRadioButton); // Utiliser la variable membre pour ajouter le bouton radio "Easy"
    difficultyLayout->addWidget(m_mediumRadioButton);
    difficultyLayout->addWidget(m_hardRadioButton);
    difficultyGroupBox->setLayout(difficultyLayout);

    // Ajouter les widgets à la fenêtre
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(startButton);
    mainLayout->addWidget(difficultyGroupBox); // Ajouter la boîte de groupe au layout principal
    ui->centralwidget->setLayout(mainLayout);
}


void MainWindow::startGame()
{
    QLayout* layout = ui->centralwidget->layout();
    if (layout != nullptr) {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete layout;
    }
    if(m_easyRadioButton->isChecked()){
        int ROWS = 4;
        int COLS = 6;
        QWidget* widget1 = ui->centralwidget->findChild<QWidget*>("widget_1");
        QWidget* widget2 = ui->centralwidget->findChild<QWidget*>("widget_2");

        QGridLayout* gridLayout = new QGridLayout(widget1);
        for(int i=0; i<ROWS; i++){
            for(int j=0; j<COLS; j++){
                QPixmap frontImage(":/cartes/01.png");
                QPixmap backImage(":/cartes/back.png");
                CardButton* card = new CardButton(frontImage, backImage, this);

                // Add the card to the grid layout
                gridLayout->addWidget(card, i, j);

                // Connect the clicked signal of the card to the flip slot
                connect(card, &CardButton::clicked, card, &CardButton::flip);
            }
        }
        // Afficher la grille
        widget1->setStyleSheet("border: 2px solid black");
        widget2->setStyleSheet("border: 2px solid black");
        ui->centralwidget->setStyleSheet("background-color: darkgreen");
        widget1->setLayout(gridLayout);
    }
    else if(m_mediumRadioButton->isChecked()){
        int ROWS = 4;
        int COLS = 9;
        QGridLayout* gridLayout = new QGridLayout(ui->centralwidget);
        for(int i=0; i<ROWS; i++){
            for(int j=0; j<COLS; j++){
                QPixmap frontImage(":/cartes/01.png");
                QPixmap backImage(":/cartes/back.png");
                CardButton* card = new CardButton(frontImage, backImage, this);

                // Add the card to the grid layout
                gridLayout->addWidget(card, i, j);

                // Connect the clicked signal of the card to the flip slot
                connect(card, &CardButton::clicked, card, &CardButton::flip);
            }
        }
        // Afficher la grille
        ui->centralwidget->setStyleSheet("background-color: darkgreen");
        ui->centralwidget->setLayout(gridLayout);
    }
    else if(m_hardRadioButton->isChecked()){
        int ROWS = 6;
        int COLS = 8;
        QGridLayout* gridLayout = new QGridLayout(ui->centralwidget);
        for(int i=0; i<ROWS; i++){
            for(int j=0; j<COLS; j++){
                QPixmap frontImage(":/cartes/01.png");
                QPixmap backImage(":/cartes/back.png");
                CardButton* card = new CardButton(frontImage, backImage, this);

                // Add the card to the grid layout
                gridLayout->addWidget(card, i, j);

                // Connect the clicked signal of the card to the flip slot
                connect(card, &CardButton::clicked, card, &CardButton::flip);
            }
        }
        // Afficher la grille
        ui->centralwidget->setStyleSheet("background-color: darkgreen");
        ui->centralwidget->setLayout(gridLayout);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
    }

