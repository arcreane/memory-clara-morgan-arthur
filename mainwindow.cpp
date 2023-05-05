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
    startButton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50))); // Position et taille
    connect(startButton, SIGNAL(clicked()), this, SLOT(startGame())); // Connecter le signal clicked() à la slot startGame()

    // Créer le groupe de boutons radio pour la sélection de niveau de difficulté
    QGroupBox *difficultyGroupBox = new QGroupBox("Difficulty", this);

    // Configurer le groupe de boutons radio
    difficultyGroupBox->setGeometry(QRect(QPoint(350, 100), QSize(200, 150))); // Position et taille
    QRadioButton *easyRadioButton = new QRadioButton("Easy", difficultyGroupBox);
    QRadioButton *mediumRadioButton = new QRadioButton("Medium", difficultyGroupBox);
    QRadioButton *hardRadioButton = new QRadioButton("Hard", difficultyGroupBox);
    easyRadioButton->setChecked(true); // Sélectionner le bouton radio "Easy" par défaut

    // Ajouter les boutons radio au groupe
    QVBoxLayout *difficultyLayout = new QVBoxLayout;
    difficultyLayout->addWidget(easyRadioButton);
    difficultyLayout->addWidget(mediumRadioButton);
    difficultyLayout->addWidget(hardRadioButton);
    difficultyGroupBox->setLayout(difficultyLayout);
}
void MainWindow::startGame()
{
    // Code pour démarrer le jeu
    // ...
}
MainWindow::~MainWindow()
{
    delete ui;
}

