#include <QtGui>
#include <QWidget>
#include "rysunek.h"

Rysunek::Rysunek(QWidget *parent) : QWidget(parent)
{
    setBackgroundRole(QPalette::Window);
    setAutoFillBackground(true);
    this->rysik = QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    przegrana = false;
    wygrana = false;
}

QSize Rysunek::minimumSizeHint() const
{
    return QSize(400, 400);
}

void Rysunek::Rysuj(Ksztalt Ksztalt)
{
    this->ksztalt = Ksztalt;
    update();
}

void Rysunek::paintEvent(QPaintEvent * /*event */)
{
    QRect rect(0, 0, 20, 20);
    QPainter painter(this);
    painter.setPen(rysik);
    switch(ksztalt){
        case pnoga:
            painter.drawLine(180, 230, 200, 250);
            ksztalt = lnoga;
        case lnoga:
            painter.drawLine(180, 230, 160, 250);
            ksztalt = lreka;
        case lreka:
            painter.drawLine(180, 190, 160, 210);
            ksztalt = preka;
        case preka:
            painter.drawLine(180, 190, 200, 210);
            ksztalt = cialo;
        case cialo:
            painter.drawLine(180, 190, 180, 230);
            ksztalt = glowa;
        case glowa:
            painter.translate(170, 170);
            painter.drawEllipse(rect);
            painter.resetTransform();
            ksztalt = szubienica;
        case szubienica:
            painter.drawLine(180, 170, 180, 120);
            painter.drawLine(180, 120, 80, 120);
            painter.drawLine(80, 120, 80, 300);
            break;
        case podstawa:
            break;
    }
    if(przegrana){
        painter.drawText(10, 30, "KONIEC GRY");
    }
    if(wygrana){
        painter.drawText(10, 30, "GRATULACJE!");
    }
    painter.translate(70, 300);
    rect.adjust(0, 0, 200, 20);
    painter.drawRect(rect);
    painter.resetTransform();
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
