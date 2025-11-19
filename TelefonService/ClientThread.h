#include "..\Socket\Socket.hpp"
#include "Telefonbuch.h"
#include "Thread.h"
#include <string>

class ClientThread : public Thread {
private:
    Socket* client;
    Telefonbuch* daten;

public:
    ClientThread(Socket* c, Telefonbuch* d)
        : client(c), daten(d) {}

    void run() override {
        string anfrage;

        while (!stopRequestedFlag())
        {
            while (!client->dataAvailable()) {
                if (stopRequestedFlag()) return;
            }

            anfrage = client->readLine();
            if (anfrage == "EXIT" || anfrage == "\0") break;

            string res = daten->nrSuche(anfrage);
            client->write(res);
        }

        client->close();
        delete client;
    }
};
