#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class QLabel;
class Rysunek;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();                  //postaralem sie usunac wszystkie zmienne wskaznikowe

private slots:
    void potwierdzliterke();        //w tym slocie znajduje sie caly kod zwiazany z weryfikacja i zwracaniem wyniku podanej literki
    void powtorz();                 //czysci wszystkie zmienne, rysuje obrazek od poczatku
    void wlasneslowo();             //pokazuje ukryte widgety
    void potwierdzwlasnehandle();   //weryfikuje czy nowe slowo ma 7 znakow i czy moze zostac potwierdzone, ukrywa widgety

private:
    Rysunek *rysunek;   //obiekt klasy, po przypisaniu ma dostep do wszystkich metod i zmiennych poza jedna prywatna
    QLabel *poleuzytkownika, *rozwiazanie, *wlasneostrzezenie;
    QLineEdit literka, odpowiedz[7], wlasne;
    QPushButton *potwierdz, *reset, *wpisz, *potwierdzwlasne;
    QString slowo, odp;
    int index, DOOMCOUNT;
    bool match;
};
#endif
