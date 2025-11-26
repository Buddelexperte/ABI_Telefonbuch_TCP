#include "TelefonbuchServer.h"
#include <iostream>

using namespace std;
#define SERVERPORT 54321
#define SERVERIP "10.35.70.86"


int main()
{
	// Mehr sollte in der main() nicht stehen!

	TelefonbuchServer* srv = new TelefonbuchServer(SERVERPORT);
	cout << "------------SERVER--------------" << endl;
	srv->start();


	delete srv;
	return 0;
}