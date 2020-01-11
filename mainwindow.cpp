#include "rysunek.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <QLabel>
#include <QLayout>

MainWindow::MainWindow()
{
    rysunek = new Rysunek;
    slowo = "hangman";
    DOOMCOUNT = 0;

    poleuzytkownika = new QLabel(tr("Wpisz literke: "));
    rozwiazanie = new QLabel(tr("Rozwiazanie: "));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(rysunek, 0, 0, 1, 4);             //widget z utworzona przeze mnie klasa
    mainLayout->addWidget(rozwiazanie, 2, 0, Qt::AlignLeft);
    mainLayout->addWidget(poleuzytkownika, 3, 0, Qt::AlignLeft);

    mainLayout->addWidget(&literka, 3, 1, Qt::AlignLeft);       //pole tekstowe dla uzytkownika
    literka.setMaxLength(1);
    literka.setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
    literka.setMaximumWidth(20);    //estetyka
    setLayout(mainLayout);

    potwierdz = new QPushButton("potwierdz", this);
    mainLayout->addWidget(potwierdz, 3, 2, Qt::AlignLeft);
    connect(potwierdz, SIGNAL(clicked()), this, SLOT(potwierdzliterke()));

    reset = new QPushButton("reset", this);
    mainLayout->addWidget(reset, 2, 2, Qt::AlignRight);
    connect(reset, SIGNAL(clicked()), this, SLOT(powtorz()));

    wpisz = new QPushButton("wlasne slowo", this);
    mainLayout->addWidget(wpisz, 3, 3, Qt::AlignRight);
    connect(wpisz, SIGNAL(clicked()), this, SLOT(wlasneslowo()));

    mainLayout->addWidget(&wlasne, 2, 4, Qt::AlignRight);       //pole tekstowe dla uzytkownika
    wlasne.setMaxLength(7);
    wlasne.hide();

    wlasneostrzezenie = new QLabel(tr("Musi miec 7 znakow! (dozwolone spacje)"));
    mainLayout->addWidget(wlasneostrzezenie, 2, 3, Qt::AlignRight);
    wlasneostrzezenie->hide();

    potwierdzwlasne = new QPushButton("potwierdz", this);
    mainLayout->addWidget(potwierdzwlasne, 3, 4, Qt::AlignRight);
    connect(potwierdzwlasne, SIGNAL(clicked()), this, SLOT(potwierdzwlasnehandle()));
    potwierdzwlasne->hide();

    QBoxLayout *secondary = new QHBoxLayout;                            //layout wewnatrz ktorego znajduja sie pojedyncze literki
    mainLayout->addLayout(secondary, 2, 1, Qt::AlignAbsolute);
    for(unsigned i = 0; i < 7; i++){
        secondary->addWidget(&odpowiedz[i]);
        odpowiedz[i].setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
        odpowiedz[i].setMinimumWidth(20);               //estetyka
        odpowiedz[i].setAlignment(Qt::AlignCenter);     //estetyka
        odpowiedz[i].setReadOnly(1);                    //nieedytowalne przez uzytkownika, ale przez program tak
        odpowiedz[i].setText("_");
    }
    setWindowTitle(tr("Wisielec"));
}

MainWindow::~MainWindow()
{
    delete rysunek;
    delete potwierdz;
    delete reset;
    delete poleuzytkownika;
    delete rozwiazanie;
    delete wlasneostrzezenie;
    delete potwierdzwlasne;
}

void MainWindow::potwierdzliterke(){
    odp = literka.text();
    match = false;
    index = 0;
    while(index < 7){           //w przypadku gdy rozwazono juz wszystkie przypadki index zawsze == 7
        if(slowo.contains(odp, Qt::CaseSensitive) && match == false){   //podwojny warunek wymagany w celu unikniecia niesk. petli
            index = slowo.indexOf(odp, index);
            while(index <= 7){
                if(slowo[index] == odp) odpowiedz[index].setText(odp);  //wyswietlanie literki na widgecie
                index++;
            }
            match = true;   //match == true oznacza ze przy nastepnej petli przejdziemy do else
            rysunek->wygrana = true;    //zakladamy mozliwosc zwyciestwa
            for(unsigned i = 0; i < 7; i++){
                QString temp = odpowiedz[i].text();
                if(temp == "_") rysunek->wygrana = false;
            }
            if(rysunek->wygrana){
                literka.setReadOnly(1);
                potwierdz->setEnabled(false);
                rysunek->Rysuj(rysunek->ksztalt);
            }
        }else index = 7;
    }
    if(!match){         //dopiero tutaj rozwazamy przypadek zlej literki
        DOOMCOUNT++;
        if(DOOMCOUNT == 7){
            literka.setReadOnly(1);
            potwierdz->setEnabled(false);
            rysunek->przegrana = true;
        }
        rysunek->ksztalt = static_cast<Rysunek::Ksztalt>(DOOMCOUNT);
        rysunek->Rysuj(rysunek->ksztalt);
    }
    literka.setText("");
}

void MainWindow::powtorz(){
    literka.setText("");
    for(unsigned i = 0; i < 7; i++){
        odpowiedz[i].setText("_");
    }
    DOOMCOUNT = 0;
    rysunek->ksztalt = static_cast<Rysunek::Ksztalt>(DOOMCOUNT);
    rysunek->przegrana = false;
    rysunek->wygrana = false;
    rysunek->Rysuj(rysunek->ksztalt);
    literka.setReadOnly(0);
    potwierdz->setEnabled(1);
}

void MainWindow::wlasneslowo(){
    wlasne.show();
    potwierdzwlasne->show();
    wlasneostrzezenie->show();
}

void MainWindow::potwierdzwlasnehandle(){
    bool ok = true;
    QString temp;
    temp = wlasne.text();

    for(unsigned i = 0; i < 7; i++){
        if(temp[i] == nullptr) ok = false;
    }
    if(ok){             //dopoki warunek nie zostanie spelniony program nie wymieni slowa
        slowo = wlasne.text();
        powtorz();
        wlasne.hide();
        potwierdzwlasne->hide();
        wlasneostrzezenie->hide();
    }
}
