#include <iostream>
#include <string>
#include "..\Socket\Socket.hpp"
#include "TelefonbuchServer.h"
using namespace std;

TelefonbuchServer::TelefonbuchServer(int port)
{
	// 1) ServerSocket() - erzeugt einen Serversocket
	// ToDo

	daten->toString();
}

TelefonbuchServer::~TelefonbuchServer(void)
{
	delete server;
	delete daten;
}

void TelefonbuchServer::start()
{
	string anfrageName = "";
	string antwort;
	// ToDo

		// 3) accept() - erzeugt einen ArbeitsSocket (workSocket), wenn ein Client eine Verbindung anfragt
		//    Der Aufruf von accept() blockiert solange, bis ein Client Verbindung aufnimmt

		// ToDo

	cout << "Client verbunden!" << endl;

	while (anfrageName != "???")
	{
		// 5b) Kommunikation mit read() write()
		// ToDo

	}

	// 7) ArbeitsSocket abmelden
	// ToDo

// 8) ServerSocket abmelden
// ToDo
}