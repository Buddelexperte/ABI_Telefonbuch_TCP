#include "../Socket/ServerSocket.hpp"
#include "..\Socket\Socket.hpp"
#include "ClientThread.h"
#include "Telefonbuch.h"
#include "TelefonbuchServer.h"
#include <iostream>
#include <new>

using namespace std;

TelefonbuchServer::TelefonbuchServer(int port)
{
	daten = new Telefonbuch;
	server = new ServerSocket(port);

	daten->toString();
}

TelefonbuchServer::~TelefonbuchServer(void)
{
    if (server)
    {
        server->close();
    }

	delete server;
	delete daten;
}

void TelefonbuchServer::start()
{
    while (true)
    {
        Socket* client = server->accept();  // blockiert nur hier
        cout << "Client verbunden!" << endl;

        // Start des Worker-Threads
        ClientThread* worker = new ClientThread(client, daten);
        worker->start();  // führt intern run() im neuen Thread aus
    }
}
