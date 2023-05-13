#include "cardbutton.h"
#include <QUrl>
#include <QDebug>

CardButton::CardButton(const QPixmap& frontImage, const QPixmap& backImage, QWidget *parent)
    : QPushButton(parent)
    , m_isFlipped(false)
    , m_frontImage(frontImage)
    , m_backImage(backImage)
{
    setFixedSize(74, 107);
    setIcon(m_backImage);
    setIconSize(QSize(74, 107));

    m_animation.setTargetObject(this);
    m_animation.setStartValue(0);
    m_animation.setEndValue(180);
    connect(&m_animation, &QPropertyAnimation::finished, this, &CardButton::onAnimationFinished);
}

void CardButton::flip()
{
    m_animation.start();
    m_isFlipped = !m_isFlipped;
}

void CardButton::onAnimationFinished()
{
    if(m_isFlipped)
    {
        setIcon(m_frontImage);
    }
    else
    {
        setIcon(m_backImage);
    }
}

bool CardButton::getIsFlipped()
{
    return (m_isFlipped);
}

QPixmap CardButton::getFront()
{
    return (m_frontImage);
}

