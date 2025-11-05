#pragma once
#include <string>
#include "List.h"
using namespace std;

class Eintrag;

// 2.2 Aufgabe
class Telefonbuch
{
private:
	int maxAnzahlEintraege;
	list<Eintrag*> telefonbuchEintraege; 
	int anzahlEintraege;
	

public:
	void eintragEinfuegen(Eintrag*);
	void eintragLoeschen(string);
	bool gibtEintrag(string);
	string nrSuche(string);
	list<Eintrag*>& getTelefonbuchEintraege();
	void sortierenNachNamen();
	void toString();
	Telefonbuch();
	Telefonbuch(int);
	~Telefonbuch();
};