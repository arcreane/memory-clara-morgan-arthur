#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPushButton>

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

