#pragma once
#include <string>
using namespace std;

// Zieladresse des Servers
constexpr auto SERVERIP = "127.0.0.1";  // Konstante für den IP-Adresse
constexpr int SERVERPORT = 5586;		// Konstante für den Server-Port - zentraler Ort fuer die Port-Nummer

class Socket;

class TelefonClient
{
private:
	Socket* client_sock;
public:
	bool verbinden(string server, int port);
	bool abmelden();
	bool menu();

	TelefonClient(void);
	~TelefonClient(void);
};

