
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QList>
#include <QPixmap>
#include <QToolButton>
#include <QLabel>
#include <QPushButton>
#include "cardbutton.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void startGame();
    void updateTime();
    void checkWin();
    void restartGame();
    void showWinningText();
private:
    Ui::MainWindow *ui;
    QRadioButton *m_easyRadioButton; // Ajouter une variable membre pour stocker un pointeur vers le bouton radio "Easy"
    QRadioButton *m_mediumRadioButton;
    QRadioButton *m_hardRadioButton;
    QList<QPixmap> m_cardImages;
    QTimer* m_timer;
    QLabel* m_labelTime;
    int m_seconds;
    int m_compteur_paires[4];
    QLabel* m_score;
    QLabel* m_scoreText[4];
    QLabel* winningText;
    QLabel* pos_joueur;
    QPushButton* m_restartButton;
    QList<CardButton*> m_cardButtons; // Variable membre pour stocker les cartes
    int m_theme;
    int m_player;
    int m_posplayer;
};

#endif // MAINWINDOW_H
