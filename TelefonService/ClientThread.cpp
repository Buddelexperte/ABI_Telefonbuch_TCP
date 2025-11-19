#include "ClientThread.h"
#include "Eintrag.h"
#include "Telefonbuch.h"
#include <cctype>
#include <iostream>
#include <list>
#include <mutex>
#include <shared_mutex>
#include <sstream>
#include <string>

void ClientThread::parseCommand(const std::string& input, std::string& cmd, std::string& arg1, std::string& arg2)
{
    cmd.clear();
    arg1.clear();
    arg2.clear();

    // Trim leading/trailing spaces
    std::string trimmed = input;
    trimmed.erase(0, trimmed.find_first_not_of(" \t"));
    trimmed.erase(trimmed.find_last_not_of(" \t") + 1);

    // Find the first whitespace → everything before = command
    size_t spacePos = trimmed.find(' ');
    for (char& c : trimmed)
    {
        c = toupper(c);
    }
    if (spacePos == std::string::npos) {
        cmd = trimmed;     // Just the command
        return;            // No args
    }

    cmd = trimmed.substr(0, spacePos);

    // Everything after first space = full argument string (with whitespace!)
    std::string args = trimmed.substr(spacePos + 1);

    // Split at semicolon
    size_t semicolonPos = args.find(';');
    if (semicolonPos == std::string::npos) {
        // Only one argument
        arg1 = args;
    }
    else {
        arg1 = args.substr(0, semicolonPos);
        arg2 = args.substr(semicolonPos + 1);
    }
}

void ClientThread::sendResult(std::string res)
{
    size_t numLines = std::count(res.begin(), res.end(), '\n');

    client->write(std::to_string(numLines) + '\n');
    client->write(res);
}

void ClientThread::run()
{
    std::string anfrage;

    while (!stopRequestedFlag())
    {
        while (!client->dataAvailable())
        {
            if (stopRequestedFlag())
            {
                client->close();
                delete client;
                return;
            }
        }

        anfrage = client->readLine();

        std::string cmd, arg1, arg2;
        parseCommand(anfrage, cmd, arg1, arg2);
        std::cout << "\nAnfrage erhalten:\n[" << cmd << "]";
        if (!arg1.empty())
            std::cout << " {Arg1: " << arg1 << "}";
        if (!arg2.empty())
            std::cout << " {Arg2: " << arg2 << "}";
        std::cout << std::endl;

        if (cmd == "EXIT" || cmd == "") break;


        std::string result = "";

        if (cmd == "HELP")
        {
            std::shared_lock<std::shared_mutex> lock(telMutex_s);  // mehrere Leser

            result += "Verfügbare Befehle:\n";
            result += "- HELP                     - Listet alle Befehle auf.\n";
            result += "- LIST                     - Listet alle Einträge im Telefonbuch auf.\n";
            result += "- GET <Name>               - Sucht die Telefonnummer für den angegebenen Namen.\n";
            result += "- CREATE <Name>;<Nummer>   - Erstellt einen neuen Eintrag mit dem angegebenen Namen und der Nummer.\n";
            result += "- DELETE <Name>            - Löscht den Eintrag mit dem angegebenen Namen.\n";
        }
        else if (cmd == "LIST")
        {
            std::shared_lock<std::shared_mutex> lock(telMutex_s);  // mehrere Leser
            std::list<Eintrag*> entries = daten->getTelefonbuchEintraege();
            

            for (Eintrag* entry : entries)
            {
                if (!entry) continue;
                result += "[" + entry->getName() + "]\t\t" + entry->getNr() + '\n';
            }
        }
        else if (cmd == "GET")
        {
            std::shared_lock<std::shared_mutex> lock(telMutex_s);  // mehrere Leser
            result = daten->nrSuche(arg1) + '\n';

        }
        else if (cmd == "CREATE")
        {
            std::unique_lock<std::shared_mutex> lock(telMutex_s);  // exklusiv

            Eintrag* entry = new Eintrag(arg1, arg2);
            daten->eintragEinfuegen(entry);
            result = "Versucht " + arg1 + " mit der Nummer " + arg2 + " zu erstellen!\n";
        }
        else if (cmd == "DELETE")
        {
            std::unique_lock<std::shared_mutex> lock(telMutex_s);  // exklusiv

            daten->eintragLoeschen(arg1);
            result = "Versucht " + arg1 + " zu entfernen!\n";
        }
        else
        {
            result = "UNKNOWN COMMAND\n";
        }

        sendResult(result);
    }

    client->close();
    delete client;
}
