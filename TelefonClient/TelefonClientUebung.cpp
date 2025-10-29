#include <iostream>
#include "TelefonClient.h"
using namespace std;

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

