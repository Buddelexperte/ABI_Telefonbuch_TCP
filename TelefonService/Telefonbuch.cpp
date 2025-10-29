#include <iostream>
#include "List.h"
#include "Telefonbuch.h"
#include "Eintrag.h"

using namespace std;

// 2.2 Aufgabe
Telefonbuch::Telefonbuch()
{
	anzahlEintraege = 3;
	maxAnzahlEintraege = 10;

	// Standardeinträge
	Eintrag* tmp0 = new Eintrag("Betty", "123");
	eintragEinfuegen(tmp0);
	Eintrag* tmp1 = new Eintrag("Anton", "456");
	eintragEinfuegen(tmp1);
	Eintrag* tmp2 = new Eintrag("Cesar", "789");
	eintragEinfuegen(tmp2);

}

Telefonbuch::Telefonbuch(int anzahl)
{
	maxAnzahlEintraege = anzahl;
	anzahlEintraege = 0;

	// Standardeinträge
	Eintrag* tmp0 = new Eintrag("Betty", "123");
	eintragEinfuegen(tmp0);
	Eintrag* tmp1 = new Eintrag("Anton", "456");
	eintragEinfuegen(tmp1);
	Eintrag* tmp2 = new Eintrag("Cesar", "789");
	eintragEinfuegen(tmp2);
}

Telefonbuch::~Telefonbuch()
{
	telefonbuchEintraege.~List();
}

string Telefonbuch::nrSuche(string such)
{
	// ToDo

	return "UNKNOWN";
}

List<Eintrag*>& Telefonbuch::getTelefonbuchEintraege()
{
	return telefonbuchEintraege;
}

void Telefonbuch::sortierenNachNamen()
{
	// ToDo
	// 
		// Hinweis >> Die add(index: int, obj : T) Methode funktioniert etwas anders als der Ringtausch!
		// Die Methode fügt das Objekt obj vom Typ T an der Position index in die Liste ein.Alle nachfolgenden Objekte werden um eine Position verschoben.
		//	Beispiel:
		//           11; 12; 13; 14;
		//           11; 12; 55; 13; 14;		
}

void Telefonbuch::toString()
{
	cout << "-----Telefonbucheintraege--------" << endl;
	// ToDo
}


void Telefonbuch::eintragLoeschen(string loesch)
{
	// ToDo
}


void Telefonbuch::eintragEinfuegen(Eintrag* einf)
{
	// ToDo für Aufgabe 1 notwendig!
}




