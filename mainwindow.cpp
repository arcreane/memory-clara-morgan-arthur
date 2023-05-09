#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_cardImages.append(QPixmap(":/cartes/10_of_clubs.png"));

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
        QGridLayout* gridLayout = new QGridLayout(ui->centralwidget);
        for(int i=0; i<ROWS; i++){
            for(int j=0; j<COLS; j++){
                // Créer un bouton personnalisé avec une image de carte
                QPushButton* button = new QPushButton(ui->centralwidget);
                button->setFixedSize(74,107);
                QPixmap pixmap(":/cartes/10_of_clubs.png"); // Charger l'image à partir du fichier de ressources
                QIcon buttonIcon(pixmap);
                button->setIcon(buttonIcon);
                button->setIconSize(QSize(74,107));
                gridLayout->addWidget(button,i,j);
            }
        }
        // Afficher la grille
        ui->centralwidget->setLayout(gridLayout);
    }
    else if(m_mediumRadioButton->isChecked()){
        int ROWS = 4;
        int COLS = 9;
        QGridLayout* gridLayout = new QGridLayout(ui->centralwidget);
        for(int i=0; i<ROWS; i++){
            for(int j=0; j<COLS; j++){
                // Créer un bouton personnalisé avec une image de carte
                QPushButton* button = new QPushButton(ui->centralwidget);
                button->setFixedSize(74,107);
                QPixmap pixmap(":/cartes/10_of_clubs.png"); // Charger l'image à partir du fichier de ressources
                QIcon buttonIcon(pixmap);
                button->setIcon(buttonIcon);
                button->setIconSize(QSize(74,107));
                gridLayout->addWidget(button,i,j);
            }
        }
        // Afficher la grille
        ui->centralwidget->setLayout(gridLayout);
    }
    else if(m_hardRadioButton->isChecked()){
        int ROWS = 6;
        int COLS = 8;
        QGridLayout* gridLayout = new QGridLayout(ui->centralwidget);
        for(int i=0; i<ROWS; i++){
            for(int j=0; j<COLS; j++){
                // Créer un bouton personnalisé avec une image de carte
                QPushButton* button = new QPushButton(ui->centralwidget);
                button->setFixedSize(74,107);
                QPixmap pixmap(":/cartes/10_of_clubs.png"); // Charger l'image à partir du fichier de ressources
                QIcon buttonIcon(pixmap);
                button->setIcon(buttonIcon);
                button->setIconSize(QSize(74,107));
                gridLayout->addWidget(button,i,j);
            }
        }
        // Afficher la grille
        ui->centralwidget->setLayout(gridLayout);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

