#ifndef RYSUNEK_H
#define RYSUNEK_H

#include <QWidget>
#include <QPen>
#include <QPainter>

class Rysunek : public QWidget
{
    Q_OBJECT

public:
    enum Ksztalt { podstawa, szubienica, glowa, cialo, preka, lreka, lnoga, pnoga };
    Ksztalt ksztalt;
    bool przegrana, wygrana;

    Rysunek(QWidget *parent = 0);

    QSize minimumSizeHint() const;                  //funkcja biblioteki
    void paintEvent(QPaintEvent * /*event */);      //tez funkcja biblioteki

public slots:
    void Rysuj(Ksztalt ksztalt);

private:
    QPen rysik;
};

#endif
