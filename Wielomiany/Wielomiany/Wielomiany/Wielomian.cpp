#include <iostream>
#include "Wielomian.h"
using namespace std;

char* UsunOdstepy(const char* napis) {
    char* napis2;
    int y = 0, dlugosc = strlen(napis);
    napis2 = new char[dlugosc + 1];
    for (int i = 0; napis[i]; i++)
        if (napis[i] != ' ')
            napis2[y++] = napis[i];
    napis2[y] = 0;
    return napis2;
}

int OkreslStopien(const char* napis) {
    int maksStopien = -1; // Przyjmujemy, ¿e dla wielomianu zerowego stopien wynosi -1
    int stopien = 0;
    int i = 0;
    while (napis[i]) {
        if (napis[i] == 'x') {
            if (napis[++i] == '^') {
                char* koniecNapisu;
                stopien = strtol(&napis[++i], &koniecNapisu, 10);
                i = koniecNapisu - napis;
            }
            else {
                stopien = 1;
                i++;
            }
            if (stopien > maksStopien)
                maksStopien = stopien;
        }
        else
            i++;
    }
    return maksStopien;
}

double* PrzydzielPamiec(int stopien) {
    double* tab = new double[stopien + 1];
    for (int i = 0; i <= stopien; i++)
        tab[i] = 0.0f;
    return tab;
}

const char* Wielomian::AnalizujJednomian(const char* napis) {
    int wykladnik = 0;
    int znak = 1;
    double wspol = 1;

    if (*napis == '+')
        napis++;
    if (*napis == '-') {
        napis++;
        znak = -1;
    }
    if (*napis != 'x')
        wspol = strtod(napis, (char**)&napis);
    if (*napis++ == 'x') {
        if (*napis++ == '^')
            wykladnik = strtol(napis, (char**)&napis, 10);
        else
            wykladnik = 1;
    }
    wspolczynnik[wykladnik] = znak * wspol;

    return napis;
}

void Wielomian::AnalizujJednomiany(const char* napis) {
    while (*napis)
        napis = AnalizujJednomian(napis);
}

Wielomian::Wielomian(const char* napis) {
    char* bezOdstepow = UsunOdstepy(napis);
    stopien = OkreslStopien(bezOdstepow);
    if (stopien >= 0) {
        wspolczynnik = PrzydzielPamiec(stopien);
        AnalizujJednomiany(bezOdstepow);
    }
    delete[] bezOdstepow;
}

Wielomian::~Wielomian() {
    delete[] wspolczynnik;
}

void Wielomian::PokazJednomianBezZnaku(int st) {
    /*if (!(st > 0 && (wspolczynnik[st] == 1 || wspolczynnik[st] == -1))) {
        if (wspolczynnik[st] > 0)
            cout << wspolczynnik[st];
        else
            cout << -wspolczynnik[st];
    }*/
}

void Wielomian::Pokaz() {
    std::cout << wspolczynnik[2] << std::endl;
    /*if (stopien < 0)
        cout << 0;
    else {
        if (wspolczynnik[stopien] < 0)
            cout << '-';
        PokazJednomianBezZnaku(stopien);
        for (int i = stopien - 1; i >= 0; i--) {
            if (wspolczynnik[i] != 0) {
                if (wspolczynnik[i] < 0)
                    cout << " - ";
                else
                    cout << " + ";
                PokazJednomianBezZnaku(i);
            }
        }
    }*/
}