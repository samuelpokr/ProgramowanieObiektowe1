#pragma once
class Wielomian {
	double* wspolczynnik;
	int stopien;
	const char* AnalizujJednomian(const char* napis);
	void AnalizujJednomiany(const char* napis);
public:
	Wielomian(const char* napis);
	~Wielomian();
	void Pokaz();
};

char* UsunOdstepy(const char* napis);
int OkreslStopien(const char* napis);
double* PrzydzielPamiec(int stopien);