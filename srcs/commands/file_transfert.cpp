#include "irc.hpp"
#define SEND true
#define NOSEND false

bool wait_receiver(user &client) {
    int timeout = 10;  // timeout en secondes
    time_t base = time(NULL);
    char buffer[1024];

    while (true) {
        if (time(NULL) - base >= timeout)
            return NOSEND;

        ssize_t bytesRead = recv(client.getfd(), buffer, sizeof(buffer), 0);

        if (bytesRead < 1)
            continue;

        buffer[bytesRead] = '\0';
        std::vector<std::string> argument = splitArgs(buffer);

        std::cout << "RECEPTION" << std::endl;
        for (size_t i = 0; i < argument.size(); i++)
            std::cout << "[" + std::string(argument[i]) + "]" << std::endl;
        std::cout << "----------------" << std::endl;

        // Vous pouvez ajuster la logique ici en fonction des données reçues.

        memset(buffer, 0, sizeof(buffer));
        return SEND;
    }

    return NOSEND;
}
