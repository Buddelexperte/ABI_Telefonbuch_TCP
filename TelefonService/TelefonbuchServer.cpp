#include <iostream>
#include <string>
#include "..\Socket\Socket.hpp"
#include "TelefonbuchServer.h"
using namespace std;

TelefonbuchServer::TelefonbuchServer(int port)
	: daten(new Telefonbuch)
{
	server = new ServerSocket(port);

	daten->toString();
}

TelefonbuchServer::~TelefonbuchServer(void)
{
	delete server;
	delete daten;
}

void TelefonbuchServer::start()
{
	string anfrage = "Name";
	string antwort;

	Socket* work = server->accept();

	cout << "Client verbunden!" << endl;

	while (!anfrage.empty() && anfrage != "EXIT")
	{
		while(!work->dataAvailable()){}

		anfrage = work->readLine();

		std::cout << anfrage;

		if (anfrage == "\0" || anfrage == "EXIT") break;

		string res = daten->nrSuche(anfrage);

		work->write(res);
	}

	work->close();

	server->close();
}