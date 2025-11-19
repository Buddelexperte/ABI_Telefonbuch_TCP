#pragma once
#include <string>
using namespace std;

class Socket;

class TelefonClient
{
private:
	Socket* client_sock = nullptr;
	std::string clientReadMultiLine();

public:
	bool verbinden(string server, int port);
	bool abmelden();
	bool menu();

	TelefonClient(void);
	~TelefonClient(void);
};

