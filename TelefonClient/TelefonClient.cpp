#include <string>
#include <iostream>
#include "..\Socket\Socket.hpp"
#include "TelefonClient.h"
using namespace std;

bool TelefonClient::menu(){

	return 0;
}

bool TelefonClient::verbinden(string server, int port){

	client_sock = new Socket(server, port);

	string text="", antwort="";
	cout<<"Warte auf Serververbindung"<<endl;

	while (!client_sock->connect())
	{}

	cout<<"\nVerbunden mit dem Server"<<endl;

	do{
		cout << "Name eingeben: - um die Telefonnummer abzurufen\n>> " << flush;
		cin >> text;
		
		client_sock->write(text);

		antwort = client_sock->readLine();

		cout << "Telefonnummer von " << text << " lautet: " <<  antwort << endl;
		cout << endl;
	}while(!text.empty() && text != "EXIT");

	return true;
}

bool TelefonClient::abmelden()
{
	client_sock->close();
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
