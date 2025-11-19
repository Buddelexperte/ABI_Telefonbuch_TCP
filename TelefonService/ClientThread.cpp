#include "ClientThread.h"
#include "Eintrag.h"
#include "Telefonbuch.h"
#include <iosfwd>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <sstream>

void ClientThread::parseCommand(const std::string& input, std::string& cmd, std::string& arg1, std::string& arg2)
{
    // Beispiel-Input:
    // GET Anton
    // CREATE Anton;123
    // DELETE Anton

    cmd.clear();
    arg1.clear();
    arg2.clear();

    std::stringstream ss(input); // Einlesen des Strings wie eine Nutzer "cin" Eingabe
    ss >> cmd;                 // liest den ersten Token (z.B. "GET")

    if (cmd == "GET" || cmd == "DELETE")
    {
        ss >> arg1;
    }
    else if (cmd == "CREATE")
    {
        ss >> arg1;            // enthält "Anton;123"

        size_t pos = arg1.find(';');
        if (pos != std::string::npos)
        {
            arg2 = arg1.substr(pos + 1);   // Nummer extrahieren
            arg1 = arg1.substr(0, pos);    // Name extrahieren
        }
    }
}

void ClientThread::run()
{
    std::string anfrage;

    while (!stopRequestedFlag())
    {
        while (!client->dataAvailable()) {
            if (stopRequestedFlag()) return;
        }

        anfrage = client->readLine();
        if (anfrage == "EXIT" || anfrage == "\0") break;

        std::string cmd, arg1, arg2;
        parseCommand(anfrage, cmd, arg1, arg2);

        std::cout << "\nAnfrage erhalten:\n[" << cmd << "]";
        if (!arg1.empty())
            std::cout << " {Arg1: " << arg1 << "}";
        if (!arg2.empty())
            std::cout << " {Arg2: " << arg2 << "}";
        std::cout << std::endl;

        if (cmd == "GET")
        {
            std::shared_lock<std::shared_mutex> lock(telMutex_s);  // mehrere Leser
            std::string res = daten->nrSuche(arg1);
            client->write(res + "\n");
        }
        else if (cmd == "CREATE")
        {
            std::unique_lock<std::shared_mutex> lock(telMutex_s);  // exklusiv

            Eintrag* entry = new Eintrag(arg1, arg2);
            daten->eintragEinfuegen(entry);
            client->write("Versucht\n");
        }
        else if (cmd == "DELETE")
        {
            std::unique_lock<std::shared_mutex> lock(telMutex_s);  // exklusiv

            daten->eintragLoeschen(arg1);
            client->write("Versucht\n");
        }
        else
        {
            client->write("UNKNOWN COMMAND\n");
        }
    }

    client->close();
    delete client;
}
