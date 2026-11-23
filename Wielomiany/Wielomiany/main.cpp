#include <iostream>

typedef struct {
    float* wspolczynnik;
    int stopien;
} Wielomian;

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
    int maksStopien = 0;
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

float* PrzydzielPamiec(int stopien) {
    float* tab = new float[stopien + 1];
    for (int i = 0; i <= stopien; i++)
        tab[i] = 0.0f;
    return tab;
}

const char* AnalizujJednomian(const char* napis, Wielomian* w) {
    int wykladnik = 0;
    int znak = 1;
    double wspolczynnik = 1;

    if (*napis == '+')
        napis++;
    if (*napis == '-') {
        napis++;
        znak = -1;
    }
    if (*napis != 'x')
        wspolczynnik = strtod(napis, (char**)&napis);
    if (*napis++ == 'x') {
        if (*napis++ == '^')
            wykladnik = strtol(napis, (char**)&napis, 10);
        else
            wykladnik = 1;
    }
    w->wspolczynnik[wykladnik] = znak * wspolczynnik;
    
    return napis;
}

void AnalizujJednomiany(const char* napis, Wielomian* w) {
    while (*napis)
        napis = AnalizujJednomian(napis, w);
}

Wielomian Analizuj(const char* napis) {
    Wielomian w;
    char* bezOdstepow = UsunOdstepy(napis);
    w.stopien = OkreslStopien(bezOdstepow);
    w.wspolczynnik = PrzydzielPamiec(w.stopien);
    AnalizujJednomiany(bezOdstepow, &w);
    delete[] bezOdstepow;
    return w;
}
/*
void Pokaz(Wielomian w) {
    int wykl = w.stopien;
    while (w.wspolczynnik[wykl] == 0)
        wykl--;
    std::cout << w.wspolczynnik[w.stopien];
}
*/
int main() {
    const char* napis = "2x^3 - x^2 + 2x - 7.5";
    Wielomian w = Analizuj(napis);
    std::cout << w.wspolczynnik[2] << std::endl;

    return 0;
}