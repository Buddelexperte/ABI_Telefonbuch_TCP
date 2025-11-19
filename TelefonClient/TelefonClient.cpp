#include "..\Socket\Socket.hpp"
#include "TelefonClient.h"
#include <iosfwd>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

bool TelefonClient::menu()
{

	return 0;
}

std::string TelefonClient::clientReadMultiLine()
{
	std::string response;

	response = client_sock->readLine();
	const int numResLines = stoi(response);

	response.clear();
	for (int i = 0; i < numResLines; i++)
	{
		response += client_sock->readLine();
		if (i + 1 < numResLines) response += '\n';
	}

	return response;
}

bool TelefonClient::verbinden(string server, int port)
{
	client_sock = new Socket(server, port);

	cout<< "Warte auf Serververbindung"<<endl;

	while (!client_sock->connect())
	{
		// Warten
	}

	cout<< "\nVerbunden mit dem Server"<<endl;

	// Befehle anzeigen
	client_sock->write("HELP");
	std::cout << clientReadMultiLine() << "\n\n" << std::endl;

	std::string input = "";
	do{
		cout << ">> " << flush;
		std::getline(cin, input);

		if (input.empty())
		{
			continue;
		}

		client_sock->write(input + '\n');

		cout << clientReadMultiLine() << '\n' << std::endl;

	}while(true);

	return true;
}

bool TelefonClient::abmelden()
{
	client_sock->close();
	return true;
}

TelefonClient::TelefonClient(void)
{
}


TelefonClient::~TelefonClient(void)
{	
	if (client_sock)
	{
		client_sock->close();
		delete client_sock;
	}
}
