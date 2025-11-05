#include <iostream>
#include "List.h"
#include "Telefonbuch.h"
#include "Eintrag.h"

using namespace std;

// 2.2 Aufgabe
Telefonbuch::Telefonbuch()
	: Telefonbuch(10)
{
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
	telefonbuchEintraege.~list();
}

string Telefonbuch::nrSuche(string such)
{
	for (Eintrag*& elem : telefonbuchEintraege)
	{
		if (elem == nullptr) continue;

		if (elem->getName() == such)
			return elem->getNr();
	}

	return "UNKNOWN";
}

list<Eintrag*>& Telefonbuch::getTelefonbuchEintraege()
{
	return telefonbuchEintraege;
}

void Telefonbuch::sortierenNachNamen()
{
	if (telefonbuchEintraege.size() < 2) return;

	auto it = next(telefonbuchEintraege.begin()); // zweites Element
	while (it != telefonbuchEintraege.end())
	{
		auto current = it++;  // current = zu verschiebender Knoten, it = nächste Position

		// Finde Position in [begin, current) für current
		auto pos = telefonbuchEintraege.begin();
		while (pos != current && (*pos)->getName() <= (*current)->getName())
		{
			pos++;
		}

		// Wenn pos != current, dann splice current vor pos
		if (pos != current) {
			// 1. Element an der Position current herausnehmen (liefert Iterator auf das nächste Element)
			Eintrag* element = *current;
			current = telefonbuchEintraege.erase(current);

			// 2. Element vor pos wieder einfügen
			telefonbuchEintraege.insert(pos, element);

		}
	}
}


void Telefonbuch::toString()
{
	cout << "-----Telefonbucheintraege--------" << endl;

	for (Eintrag*& elem : telefonbuchEintraege)
	{
		std::cout << elem->getName() << " " << elem->getNr() << std::endl;
	}
	std::cout << std::endl;
}

void Telefonbuch::eintragLoeschen(string loesch)
{
	std::list<Eintrag*> toDelete;
	for (Eintrag*& elem : telefonbuchEintraege)
	{
		if (elem->getName() == loesch)
			toDelete.push_back(elem);
	}

	for (Eintrag*& elem : toDelete)
	{
		if (elem == nullptr) continue;
		telefonbuchEintraege.remove(elem);
	}
}


void Telefonbuch::eintragEinfuegen(Eintrag* einf)
{
	if (anzahlEintraege >= maxAnzahlEintraege)
		return;

	bool alreadyExists = gibtEintrag(einf->getName());
	if (alreadyExists)
	{
		delete einf;
		return;
	}

	telefonbuchEintraege.push_back(einf);
	anzahlEintraege++;

	sortierenNachNamen();
}

bool Telefonbuch::gibtEintrag(string name)
{
	return (nrSuche(name) != "UNKNOWN");
}