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
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_seconds(0)
{
    ui->setupUi(this);

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

void MainWindow::checkWin()
{
    int numCards = m_cardButtons.length() / 2;
    int compteur_flipped = 0;
    int firstCard = 0;
    int secondCard = 0;
    int i = 0;

        for (CardButton* card : m_cardButtons) {
            if (card->getIsFlipped() == true)
            {
                compteur_flipped++;
                if (compteur_flipped == 1)
                {
                    firstCard = i;
                    //card->setEnabled(false);
                    disconnect(card, &CardButton::clicked, card, &CardButton::flip);
                    disconnect(card, &CardButton::clicked, this, &MainWindow::checkWin);
                    m_restartButton->setEnabled(false);
                }
                if (compteur_flipped == 2)
                {
                    secondCard = i;
                    for (CardButton* card_disabled : m_cardButtons) {
                        //card_disabled->setEnabled(false);
                        disconnect(card_disabled, &CardButton::clicked, card_disabled, &CardButton::flip);
                        disconnect(card_disabled, &CardButton::clicked, this, &MainWindow::checkWin);
                    }
                }
            }
            i++;
        }
        if (compteur_flipped == 2)
        {
            if (m_cardButtons[firstCard]->getFront().toImage() == m_cardButtons[secondCard]->getFront().toImage())
            {
                QTimer::singleShot(1000, [this, firstCard, secondCard, numCards]() {
                    m_cardButtons[firstCard]->flip();
                    m_cardButtons[secondCard]->flip();
                    //m_cardButtons[firstCard]->hide();
                    m_cardButtons[firstCard]->setEnabled(false);

                    //m_cardButtons[secondCard]->hide();
                    m_cardButtons[secondCard]->setEnabled(false);
                    for (CardButton* card_enabled : m_cardButtons) {
                        //card_enabled->setEnabled(true);
                        connect(card_enabled, &CardButton::clicked, card_enabled, &CardButton::flip);
                        connect(card_enabled, &CardButton::clicked, this, &MainWindow::checkWin);
                        m_restartButton->setEnabled(true);
                    }
                    m_compteur_paires[m_posplayer - 1]++;
                    int i = 0;
                    int compteur = 0;
                    m_scoreText[m_posplayer - 1]->setText("Joueur " + QString::number(m_posplayer) + " : " + QString::number(m_compteur_paires[m_posplayer - 1]) + "/" + QString::number(numCards));
                    while (i < m_player) {
                        compteur = compteur + m_compteur_paires[i];
                        i++;
                    }
                    if (numCards == compteur)
                    {
                        QTimer::singleShot(2000, [this]() {
                            this->showWinningText();
                        });
                    }
                });
            }
            else
            {
                m_posplayer++;
                if (m_posplayer == m_player + 1)
                    m_posplayer = 1;
                QTimer::singleShot(3000, [this, firstCard, secondCard]() {
                    m_cardButtons[firstCard]->flip();
                    m_cardButtons[secondCard]->flip();
                    for (CardButton* card_enabled : m_cardButtons) {
                        //card_enabled->setEnabled(true);
                        connect(card_enabled, &CardButton::clicked, card_enabled, &CardButton::flip);
                        connect(card_enabled, &CardButton::clicked, this, &MainWindow::checkWin);
                        m_restartButton->setEnabled(true);
                    }
                    pos_joueur->setText("Joueur actuel : " + QString::number(m_posplayer));
                });
            }

        }


}

void MainWindow::showWinningText()
{
    QLabel* winningText = new QLabel("Félicitations, vous avez gagné !", this);
    winningText->setAlignment(Qt::AlignCenter);
    winningText->setStyleSheet("font-weight: bold; font-size: 40px;");
    m_timer->stop();
    m_labelTime->setStyleSheet("font-size: 20pt; color: black"); // Définir le style
    // Créer un layout vertical pour le widget central
    QWidget* contain = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(contain);
    mainLayout->addWidget(winningText);
    mainLayout->addWidget(m_labelTime);
    mainLayout->addWidget(m_restartButton);
    setCentralWidget(contain);
}


void MainWindow::startGame()
{
    QString theme = "normal";
    if (m_theme == 1)
        theme = "normal";
    else if (m_theme == 2)
        theme = "uno";
    else
        theme = "pokemon";
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
    m_labelTime->setFixedSize(350, 40);
    m_labelTime->setAlignment(Qt::AlignCenter); // Aligner le texte au centre
    m_labelTime->setStyleSheet("font-size: 20pt; color: white"); // Définir le style

    m_labelTime->setText("00:00");
    m_timer->start(1000);

    int i = 0;
    while (i < m_player) {
        m_scoreText[i] = new QLabel(this);
        m_scoreText[i]->setAlignment(Qt::AlignCenter);
        m_scoreText[i]->setStyleSheet("font-weight: bold; font-size: 28px;");
        m_scoreText[i]->setObjectName("scoreText");
        m_scoreText[i]->setText("Joueur " + QString::number(i + 1) + " : " + QString::number(m_compteur_paires[i]) + "/" + QString::number(ROWS * COLS / 2));
        i++;
    }
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
        cardImages.append(QString(":/" + theme + "/%1.png").arg(QString::number(i, 10).rightJustified(2, '0')));
    }
    std::random_shuffle(cardImages.begin(), cardImages.end());

    cardImages.resize(ROWS * COLS / 2);

    QStringList clonedCardImages = cardImages + cardImages;

    std::random_shuffle(clonedCardImages.begin(), clonedCardImages.end());
    int cardIndex = 0;
    m_cardButtons.clear();
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            QPixmap frontImage(clonedCardImages[cardIndex]);
            QPixmap backImage(":/" + theme + "/back.png");
            CardButton* card = new CardButton(frontImage, backImage, this);
            gridLayout->addWidget(card, i, j);
            connect(card, &CardButton::clicked, card, &CardButton::flip);
            connect(card, &CardButton::clicked, this, &MainWindow::checkWin);
            m_cardButtons.append(card); // Ajout de la carte à la liste
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
    m_restartButton->setStyleSheet("font-weight: bold; font-size: 24px;");


    // Configurer le bouton
    widget2Layout->addWidget(m_labelTime);
    pos_joueur = new QLabel(this);
    pos_joueur->setText("Joueur actuel : " + QString::number(m_posplayer));
    pos_joueur->setFixedSize(350, 40);
    pos_joueur->setAlignment(Qt::AlignCenter); // Aligner le texte au centre
    pos_joueur->setStyleSheet("font-weight: bold; font-size: 24px; color: white;");
    widget2Layout->addWidget(pos_joueur);
    i = 0;
    while (i < m_player) {
        widget2Layout->addWidget(m_scoreText[i]);
        i++;
    }
    widget2Layout->addWidget(m_restartButton);
    connect(m_restartButton, &QPushButton::clicked, this, &MainWindow::restartGame);
}

void MainWindow::restartGame() {
    m_timer->stop();
    int i = 0;
    while (i < 4)
    {
        m_compteur_paires[i] = 0;
        i++;
    }
    m_theme = 1;
    m_player = 1;
    m_posplayer = 1;
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

    // Créer le bouton déroulant pour le choix du thème
    QComboBox* themeComboBox = new QComboBox(this);
    themeComboBox->addItem("Theme 1 (Normal)");
    themeComboBox->addItem("Theme 2 (Uno)");
    themeComboBox->addItem("Theme 3 (Pokemon)");
    connect(themeComboBox, QOverload<int>::of(&QComboBox::activated), [=](int index){
        m_theme = index + 1;// Stocke la valeur du thème dans m_theme (1, 2 ou 3)
    });

    // Créer le bouton déroulant pour le choix du thème
    QComboBox* playerComboBox = new QComboBox(this);
    playerComboBox->addItem("1 joueur");
    playerComboBox->addItem("2 joueurs");
    playerComboBox->addItem("3 joueurs");
    playerComboBox->addItem("4 joueurs");
    connect(playerComboBox, QOverload<int>::of(&QComboBox::activated), [=](int index){
        m_player = index + 1;
    });

    // Créer un widget central
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(startButton);
    mainLayout->addWidget(themeComboBox);
    mainLayout->addWidget(playerComboBox);
    mainLayout->addWidget(difficultyGroupBox);
    // Définir le widget central
    setCentralWidget(centralWidget);
}



MainWindow::~MainWindow()
{
    delete ui;
}
