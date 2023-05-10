
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QList>
#include <QPixmap>
#include <QToolButton>

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

private:
    Ui::MainWindow *ui;
    QRadioButton *m_easyRadioButton; // Ajouter une variable membre pour stocker un pointeur vers le bouton radio "Easy"
    QRadioButton *m_mediumRadioButton;
    QRadioButton *m_hardRadioButton;
    QList<QPixmap> m_cardImages;
    QTimer* m_timer;

};

#endif // MAINWINDOW_H
