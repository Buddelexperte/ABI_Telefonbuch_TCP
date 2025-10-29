#include <string>
#include <iostream>
#include "..\Socket\Socket.hpp"
#include "TelefonClient.h"
using namespace std;

bool TelefonClient::menu(){

	return 0;
}

bool TelefonClient::verbinden(string server, int port){

	// 2) Socket() - erzeugt einen Clientsocket
	// ToDo
	string text="", antwort="";
	cout<<"Warte auf Serververbindung"<<endl;

	// 4) connect() - liefert true, wenn er einen Verbindung zu Server gefunden hat
	// ToDo
	cout<<"\nVerbunden mit dem Server"<<endl;

	do{
		cout << "Name eingeben: - um die Telefonnummer abzurufen" << endl;
		cin >> text;

		// 5a) Kommunikation mit read() write()
		// ToDo

		cout << "Telefonnummer von " << text << " lautet: " <<  antwort << endl;
		cout << endl;
	}while(text != "???");

	return true;
}

bool TelefonClient::abmelden()
{
	// 6) Client abmelden
	// ToDo
	return true;
}

TelefonClient::TelefonClient(void)
{
	// ToDo
}


TelefonClient::~TelefonClient(void)
{
	// ToDo
}
