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
    bool getIsFlipped();
    QPixmap getFront();
    QPropertyAnimation m_animation;

private:
    bool m_isFlipped;
    QPixmap m_frontImage;
    QPixmap m_backImage;

public slots:
    void onAnimationFinished();
};

#endif // CARDBUTTON_H
