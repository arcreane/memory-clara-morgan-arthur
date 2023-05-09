#include "cardbutton.h"

CardButton::CardButton(const QPixmap& frontImage, const QPixmap& backImage, QWidget *parent)
    : QPushButton(parent)
    , m_isFlipped(false)
    , m_frontImage(frontImage)
    , m_backImage(backImage)
{
    setFixedSize(74, 107);
    setStyleSheet("background-color: blue;"); // Set background color to blue for testing purposes
    setIcon(m_backImage);
    setIconSize(QSize(74, 107));

    m_animation.setTargetObject(this);
    m_animation.setPropertyName("rotationY");
    m_animation.setDuration(500);
    m_animation.setStartValue(0);
    m_animation.setEndValue(180);
    connect(&m_animation, &QPropertyAnimation::finished, this, &CardButton::onAnimationFinished);
}

void CardButton::flip()
{
    if(m_isFlipped)
    {
        m_animation.setEndValue(180);
        m_animation.setKeyValueAt(0.5, 180);
        m_animation.setKeyValueAt(0.6, 0);
        m_animation.setStartValue(0);
        m_animation.start();
    }
    else
    {
        m_animation.setEndValue(0);
        m_animation.setKeyValueAt(0.5, 0);
        m_animation.setKeyValueAt(0.6, 180);
        m_animation.setStartValue(180);
        m_animation.start();
    }

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

