#include "TelefonClient.h"
#include <iostream>

using namespace std;

#define SERVERPORT 54321
#define SERVERIP "127.0.0.1"

int main()
{
	// Mehr sollte in der main() nicht stehen!

	TelefonClient tc;
	cout << "------------CLIENT--------------" << endl;
	if (tc.verbinden(SERVERIP, SERVERPORT) == false)
		cout << "Server nicht gefunden!" << endl;

	if (tc.abmelden() == false)
		cout << "Nicht abgemeldet!" << endl;

	return 0;
}

