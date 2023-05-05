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
    QRadioButton *mediumRadioButton = new QRadioButton("Medium", difficultyGroupBox);
    QRadioButton *hardRadioButton = new QRadioButton("Hard", difficultyGroupBox);
    m_easyRadioButton->setChecked(true); // Sélectionner le bouton radio "Easy" par défaut

    // Ajouter les boutons radio au groupe
    QVBoxLayout *difficultyLayout = new QVBoxLayout;
    difficultyLayout->addWidget(m_easyRadioButton); // Utiliser la variable membre pour ajouter le bouton radio "Easy"
    difficultyLayout->addWidget(mediumRadioButton);
    difficultyLayout->addWidget(hardRadioButton);
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
        delete layout;
    }
    // Vérifier si le bouton radio "Easy" est sélectionné
    if(m_easyRadioButton->isChecked()){ // Utiliser la variable membre pour accéder au bouton radio "Easy"
        // Créer la grille de 4 de hauteur et 6 de longueur
        const int ROWS = 4;
        const int COLS = 6;
        QGridLayout* gridLayout = new QGridLayout(ui->centralwidget);
        for(int i=0; i<ROWS; i++){
            for(int j=0; j<COLS; j++){
                QPushButton* button = new QPushButton(ui->centralwidget);
                button->setFixedSize(50,50);
                gridLayout->addWidget(button,i,j);
            }
        }
        // Afficher la grille
        ui->centralwidget->setLayout(gridLayout);
    }
    else{
        // Code pour créer la grille pour les autres niveaux de difficulté
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

