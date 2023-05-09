#ifndef CARDBUTTON_H
#define CARDBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>
#include <QPixmap>

class CardButton : public QPushButton
{
    Q_OBJECT

public:
    CardButton(const QPixmap& frontImage, const QPixmap& backImage, QWidget *parent = nullptr);

    void flip();

private:
    bool m_isFlipped;
    QPixmap m_frontImage;
    QPixmap m_backImage;
    QPropertyAnimation m_animation;

private slots:
    void onAnimationFinished();
};

#endif // CARDBUTTON_H
