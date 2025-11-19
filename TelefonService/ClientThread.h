#include "..\Socket\Socket.hpp"
#include "Telefonbuch.h"
#include "Thread.h"
#include <shared_mutex>
#include <string>

static std::shared_mutex telMutex_s;

class ClientThread : public Thread {
private:
    Socket* client;
    Telefonbuch* daten;

    // Hilfsfunktion für Parsing
    void parseCommand(const std::string& input, std::string& cmd, std::string& arg1, std::string& arg2);

public:
    ClientThread(Socket* c, Telefonbuch* d)
        : client(c), daten(d) {}

    void run() override;
};
